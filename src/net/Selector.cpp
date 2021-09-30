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

        Selector::Selector(boost::asio::ip::tcp::endpoint listenEndpoint) :
                endpoint(listenEndpoint), mIOService(std::make_shared<boost::asio::io_service>()),
                mIOThreadGroup(std::make_shared<boost::thread_group>()) {
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
            // 1. 启动线程池
            // 2. 创建acceptor
            auto protocol = boost::asio::ip::tcp::v4();
            this->mAcceptor = std::make_unique<boost::asio::ip::tcp::acceptor>(*this->mIOService);
            // 3. 打开acceptor
            boost::system::error_code ec;
            this->mAcceptor->open(protocol, ec);
            if (ec.value() != 0) {
                throw "open socket failed:" + ec.message();
            }
            this->mAcceptor->set_option(boost::asio::ip::tcp::acceptor::reuse_address(true));
            // 4. 将端口绑定到acceptor
            this->mAcceptor->bind(endpoint, ec);
            if (ec.value() != 0) {
                throw "Failed to bind the acceptor socket,message:" + ec.message();
            }
            // 5. 开始侦听
            this->mAcceptor->listen(boost::asio::socket_base::max_listen_connections);
            // 6. 等待客户端连接
            this->waitForAccept();
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
        }
    }
}
