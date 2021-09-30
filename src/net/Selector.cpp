//
// Created by 凌宇 on 2021/9/27.
//

#include <net/Selector.h>
#include <net/ASIOCodec.h>
#include <net/ASIOChannel.h>
namespace kakakv {
    namespace net {
        Selector::Listener::~Listener() {
        }

        Selector::Selector(boost::asio::ip::tcp::endpoint listenEndpoint,unsigned int thread_pool_size) :
                endpoint(listenEndpoint), mIOService(std::make_shared<boost::asio::io_service>()),
                mIOThreadGroup(std::make_shared<boost::thread_group>()),mThreadPoolSize(thread_pool_size) {
            assert(thread_pool_size > 0);
        }

        void Selector::addListener(std::weak_ptr<Listener> listener) {
            auto it = this->mListenerSet.find(listener);
            if (it != this->mListenerSet.end()) {
                return;
            }
            this->mListenerSet.insert(listener);
        }

        void Selector::removeListener(std::weak_ptr<Listener> listener) {
            auto it = this->mListenerSet.find(listener);
            if (it == this->mListenerSet.end()) {
                return;
            }
            this->mListenerSet.erase(it);
        }

        void Selector::start() {
            // 1. 检查标识
            if (this->mStart.load()){
                return;
            }else{
                std::lock_guard<std::mutex> lock(this->mStartMutex);
                // 2. 设置标识
                this->mStart.store(true);
            }
            // 3. 创建acceptor
            auto protocol = boost::asio::ip::tcp::v4();
            this->mAcceptor = std::make_unique<boost::asio::ip::tcp::acceptor>(*this->mIOService);
            // 4. 打开acceptor
            boost::system::error_code ec;
            this->mAcceptor->open(protocol, ec);
            if (ec.value() != 0) {
                throw "open socket failed:" + ec.message();
            }
            this->mAcceptor->set_option(boost::asio::ip::tcp::acceptor::reuse_address(true));
            // 5. 将端口绑定到acceptor
            this->mAcceptor->bind(endpoint, ec);
            if (ec.value() != 0) {
                throw "Failed to bind the acceptor socket,message:" + ec.message();
            }
            // 6. 开始侦听
            this->mAcceptor->listen(boost::asio::socket_base::max_listen_connections);
            // 7. 等待客户端连接
            this->waitForAccept();
            // 8. 启动线程池
            this->mWork = std::make_unique<boost::asio::io_service::work>(*this->mIOService);
            for(unsigned int i = 0; i < this->mThreadPoolSize;++i){
                this->mIOThreadGroup->create_thread(boost::bind(&Selector::workThreadHandler,this));
            }
        }

        void Selector::workThreadHandler(){
            while(this->mStart.load()){
                try{
                    boost::system::error_code ec;
                    this->mIOService->run();
                    if (ec){
                    }
                }catch (std::exception &exception){
                }catch (...){
                }
            }
        }

        void Selector::waitForAccept() {
            //1. 创建Socket并将其封装成Channel
            auto codec = std::make_shared<ASIOCodec>();
            auto channel = std::make_shared<ASIOChannel>(std::make_unique<boost::asio::ip::tcp::socket>(*this->mIOService),codec,codec);
            //2. 等待客户端连接
            this->mAcceptor->async_accept(*channel->mSocket,[this,channel](const boost::system::error_code & ec){
                if (ec || !channel){
                    return;
                }
                if (this->mStart.load()){
                    //1. 通知Listener
                    for(auto listenWeakPtr : this->mListenerSet){
                        auto listener = listenWeakPtr.lock();
                        if (!listener){
                            continue;
                        }
                        listener->onReceiveConnect(channel);
                    }
                    //2. 等待新的客户端连接
                    this->waitForAccept();
                }else{
                    // 关闭连接
                    channel->mSocket->close();
                }
            });
        }

        void Selector::shutdownGracefully() {
            //1. 检查标识
            if (!this->mStart.load()){
                return;
            }else{
                //2. 设置标识
                std::lock_guard<std::mutex> lock(this->mStartMutex);
                this->mStart.store(false);
            }
            //3. 关闭
            this->mAcceptor->close();
            //4. 关闭线程池
            this->mWork.reset();
            this->mIOService->stop();
            this->mIOThreadGroup->join_all();
        }
    }
}
