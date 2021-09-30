//
// Created by 凌宇 on 2021/9/30.
//

#ifndef KAKAKV_IOSERVICE_H
#define KAKAKV_IOSERVICE_H

#include <functional>

namespace kakakv {
    namespace task {
        class IOService {
        public:
            IOService(unsigned int threadPoolSize = 3);
            virtual ~IOService() = 0;
            virtual void start() = 0;

            virtual void shutdownGracefully() = 0;

            virtual void post(std::function<void(std::shared_ptr<IOService>)> task) = 0;

            virtual void dispatch(std::function<void(std::shared_ptr<IOService>)> task) = 0;
        protected:
            const unsigned int mThreadPoolSize;
        };
    }
}

#endif //KAKAKV_IOSERVICE_H
