//
// Created by 凌宇 on 2021/9/27.
//

#ifndef KAKAKV_ASIOIOSERVICE_H
#define KAKAKV_ASIOIOSERVICE_H

#include <task/IOService.h>
#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <mutex>
namespace kakakv {
    namespace task {

        class ASIOScheduler;

        class ASIOIOService : public IOService,private std::enable_shared_from_this<ASIOIOService> {
            friend ASIOScheduler;
        public:
            ASIOIOService(unsigned int threadPoolSize = 3);

            void start()override;

            void shutdownGracefully()override;

            void post(std::function<void(std::shared_ptr<IOService>)> task)override;

            void dispatch(std::function<void(std::shared_ptr<IOService>)> task)override;

        private:
            void workThreadHandler();
            std::mutex mStartMutex;
            std::atomic<bool> mStart;
            const boost::asio::ip::tcp::endpoint endpoint;
            std::shared_ptr<boost::asio::io_service> mIOService;
            std::shared_ptr<boost::thread_group> mIOThreadGroup;
            std::unique_ptr<boost::asio::io_service::work> mWork;
        };
    }
}


#endif //KAKAKV_ASIOIOSERVICE_H
