//
// Created by 凌宇 on 2021/9/30.
//

#include <task/IOService.h>

namespace kakakv {
    namespace task {
        IOService::IOService(unsigned int threadPoolSize):mThreadPoolSize(threadPoolSize){
        }
        IOService::~IOService(){
        }
    }
}