//
// Created by 凌宇 on 2021/9/27.
//

#ifndef KAKAKV_SELECTOR_H
#define KAKAKV_SELECTOR_H

#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <memory>
namespace kakakv {
    namespace net {
        class Selector{
        public:
            void shutdownGracefully();
        private:
            std::shared_ptr<boost::asio::io_service> mIOService;
            std::shared_ptr<boost::thread_group> mIOThreadGroup;
        };
    }
}


#endif //KAKAKV_SELECTOR_H
