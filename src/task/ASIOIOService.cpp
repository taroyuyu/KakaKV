//
// Created by 凌宇 on 2021/9/27.
//

#include <task/ASIOIOService.h>

namespace kakakv {
    namespace task {
        ASIOIOService::ASIOIOService(unsigned int threadPoolSize) :
                IOService(threadPoolSize),
                mIOService(nullptr), mIOThreadGroup(nullptr) {
        }

        void ASIOIOService::start() {
            // 1. 检查标识
            if (this->mStart.load()) {
                return;
            } else {
                std::lock_guard<std::mutex> lock(this->mStartMutex);
                // 2. 设置标识
                this->mStart.store(true);
            }
            // 3. 创建IOService
            this->mIOService = std::make_shared<boost::asio::io_service>();
            // 4. 创建Work
            this->mWork = std::make_unique<boost::asio::io_service::work>(*this->mIOService);
            // 5. 创建线程池
            this->mIOThreadGroup = std::make_shared<boost::thread_group>();
            for (unsigned int i = 0; i < this->mThreadPoolSize; ++i) {
                this->mIOThreadGroup->create_thread(boost::bind(&ASIOIOService::workThreadHandler, this));
            }
        }

        void ASIOIOService::shutdownGracefully() {
            //1. 检查标识
            if (!this->mStart.load()) {
                return;
            } else {
                //2. 设置标识
                std::lock_guard<std::mutex> lock(this->mStartMutex);
                this->mStart.store(false);
            }
            //3. 关闭线程池
            this->mWork.reset();
            this->mIOService->stop();
            this->mIOThreadGroup->join_all();
        }

        void ASIOIOService::workThreadHandler() {
            while (this->mStart.load() && this->mWork) {
                try {
                    boost::system::error_code ec;
                    this->mIOService->run();
                    if (ec) {
                    }
                } catch (std::exception &exception) {
                } catch (...) {
                }
            }
        }

        void ASIOIOService::post(std::function<void(std::shared_ptr<IOService>)> task) {
            this->mIOService->post([this, task]() {
                task(this->shared_from_this());
            });
        }

        void ASIOIOService::dispatch(std::function<void(std::shared_ptr<IOService>)> task) {
            this->mIOService->dispatch([this, task]() {
                task(this->shared_from_this());
            });
        }
    }
}