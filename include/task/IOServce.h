//
// Created by 凌宇 on 2021/9/27.
//

#ifndef KAKAKV_IOSERVCE_H
#define KAKAKV_IOSERVCE_H

#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <mutex>
namespace kakakv {
    namespace task {
        class IOServce : private std::enable_shared_from_this<IOServce> {
        public:
            IOServce(unsigned int threadPoolSize = 3);

            void start();

            void shutdownGracefully();

            void post(std::function<void(std::shared_ptr<IOServce>)> task);

            void dispatch(std::function<void(std::shared_ptr<IOServce>)> task);

        private:
            void workThreadHandler();
            std::mutex mStartMutex;
            std::atomic<bool> mStart;
            const boost::asio::ip::tcp::endpoint endpoint;
            std::shared_ptr<boost::asio::io_service> mIOService;
            const unsigned int mThreadPoolSize;
            std::shared_ptr<boost::thread_group> mIOThreadGroup;
            std::unique_ptr<boost::asio::io_service::work> mWork;
        };
    }
}


#endif //KAKAKV_IOSERVCE_H
