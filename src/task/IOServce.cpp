//
// Created by 凌宇 on 2021/9/27.
//

#include <task/IOServce.h>

namespace kakakv {
    namespace task {
        IOServce::IOServce(std::shared_ptr<boost::asio::io_service> ioService,std::shared_ptr<boost::thread_group> ioThreadGroup):
                mIOService(ioService),mIOThreadGroup(ioThreadGroup){
        }
    }
}