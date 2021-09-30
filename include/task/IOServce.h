//
// Created by 凌宇 on 2021/9/27.
//

#ifndef KAKAKV_IOSERVCE_H
#define KAKAKV_IOSERVCE_H

#include <boost/asio.hpp>
#include <boost/thread.hpp>
namespace kakakv {
    namespace task {
        class IOServce {
        public:
            IOServce(std::shared_ptr<boost::asio::io_service> ioService,std::shared_ptr<boost::thread_group> ioThreadGroup);
            void start();
            void shutdownGracefully();
//        private:
            std::shared_ptr<boost::asio::io_service> mIOService;
        private:
            std::atomic<bool> mStart;
            const boost::asio::ip::tcp::endpoint endpoint;
//            const unsigned int mThreadPoolSize;
            std::shared_ptr<boost::thread_group> mIOThreadGroup;
            std::unique_ptr<boost::asio::io_service::work> mWork;
        };
    }
}


#endif //KAKAKV_IOSERVCE_H
