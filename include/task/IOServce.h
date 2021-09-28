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
//        private:
            std::shared_ptr<boost::asio::io_service> mIOService;
            std::shared_ptr<boost::thread_group> mIOThreadGroup;
            void shutdownGracefully();
        };
    }
}


#endif //KAKAKV_IOSERVCE_H
