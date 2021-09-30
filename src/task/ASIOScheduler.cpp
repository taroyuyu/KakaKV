//
// Created by 凌宇 on 2021/9/21.
//

#include <task/ASIOScheduler.h>
#include <functional>

namespace kakakv {
    namespace task {
        namespace ASIOSchedulerImpl {
            class ElectionTimeoutImpl : public ElectionTimeout {
                friend ASIOScheduler;
            public:
                ElectionTimeoutImpl(std::shared_ptr<boost::asio::deadline_timer> timerTask, Scheduler::Runnable task);

                void cancel() override;

            private:
                static void handler(const boost::system::error_code &ec,
                                    std::shared_ptr<ElectionTimeoutImpl> electionTimeoutTask);

                std::weak_ptr<boost::asio::deadline_timer> mTimerTask;
                Scheduler::Runnable mTask;
                std::atomic<bool> isCancel;
                std::atomic<bool> isDone;
            };

            ElectionTimeoutImpl::ElectionTimeoutImpl(std::shared_ptr<boost::asio::deadline_timer> timerTask,
                                                     Scheduler::Runnable task)
                    : mTimerTask(timerTask), mTask(task), isCancel(false), isDone(false) {
            }

            void ElectionTimeoutImpl::cancel() {
                this->isCancel.store(false);
                auto timerTask = this->mTimerTask.lock();
                if (!timerTask)
                    return;
                boost::system::error_code ec;
                timerTask->cancel(ec);
                if (ec) {
                    // 任务删除失败
                }
            }

            void ElectionTimeoutImpl::handler(const boost::system::error_code &ec,
                                              std::shared_ptr<ElectionTimeoutImpl> electionTimeoutTask) {
                if (false == electionTimeoutTask->isCancel.load()) {
                    return;
                }
                if (ec) {
                    return;
                }
                electionTimeoutTask->isDone.store(true);
                if (electionTimeoutTask->mTask) {
                    electionTimeoutTask->mTask();
                }
            }

            class LogReplicationTaskImpl : public LogReplicationTask {
                friend ASIOScheduler;
            public:
                LogReplicationTaskImpl(std::shared_ptr<boost::asio::deadline_timer> timerTask, Scheduler::Runnable task,
                                       const unsigned int logReplicationInterval);

                void cancel() override;

            private:
                static void handler(const boost::system::error_code &ec,
                                    std::shared_ptr<LogReplicationTaskImpl> electionTimeoutTask);

                std::weak_ptr<boost::asio::deadline_timer> mTimerTask;
                Scheduler::Runnable mTask;
                const unsigned int logReplicationInterval;
                std::atomic<bool> isCancel;
                std::atomic<int> mCount;
            };

            LogReplicationTaskImpl::LogReplicationTaskImpl(std::shared_ptr<boost::asio::deadline_timer> timerTask,
                                                           Scheduler::Runnable task,
                                                           const unsigned int logReplicationInterval)
                    : mTimerTask(timerTask), mTask(task), logReplicationInterval(logReplicationInterval),
                      isCancel(false), mCount(0) {

            }

            void LogReplicationTaskImpl::cancel() {
                this->isCancel.store(false);
                auto timerTask = this->mTimerTask.lock();
                if (!timerTask)
                    return;
                boost::system::error_code ec;
                timerTask->cancel(ec);
                if (ec) {
                    // 任务删除失败
                }
            }

            void LogReplicationTaskImpl::handler(const boost::system::error_code &ec,
                                                 std::shared_ptr<LogReplicationTaskImpl> electionTimeoutTask) {
                if (false == electionTimeoutTask->isCancel.load()) {
                    return;
                }
                if (ec) {
                    return;
                }
                electionTimeoutTask->mCount += 1;
                if (electionTimeoutTask->mTask) {
                    electionTimeoutTask->mTask();
                }
                // 重新发起定时时间
                auto timetTask = electionTimeoutTask->mTimerTask.lock();
                if (!timetTask) {

                }
                timetTask->expires_from_now(
                        boost::posix_time::milliseconds(electionTimeoutTask->logReplicationInterval));
                // 5. 将定时任务提交给定时器线程
                timetTask->async_wait(
                        std::bind(&ASIOSchedulerImpl::LogReplicationTaskImpl::handler, std::placeholders::_1,
                                  electionTimeoutTask));
            }
        }

        ASIOScheduler::ASIOScheduler(std::shared_ptr<ASIOIOService> ioService, const unsigned int minElectionTimeout,
                                     const unsigned int maxElectionTimeout, const unsigned int logReplicationDelay,
                                     const unsigned int logReplicationInterval) :
                timerIOService(ioService), minElectionTimeout(minElectionTimeout),
                maxElectionTimeout(maxElectionTimeout), logReplicationDelay(logReplicationDelay),
                logReplicationInterval(logReplicationInterval) {

        }

        std::shared_ptr<LogReplicationTask> ASIOScheduler::scheduleLogReplicationTask(Runnable task) {
            if (!this-timerIOService->mStart.load()){
                return nullptr;
            }
            // 1. 创建定时任务
            auto timerTask = std::make_shared<boost::asio::deadline_timer>(*(this->timerIOService->mIOService));
            // 2. 创建LogReplicationTaskImpl对象
            auto logReplicationTaskTimeout = std::make_shared<ASIOSchedulerImpl::LogReplicationTaskImpl>(timerTask,
                                                                                                         task,
                                                                                                         this->logReplicationInterval);
            // 3. 设置定时任务
            timerTask->expires_from_now(
                    boost::posix_time::milliseconds(this->logReplicationDelay + this->logReplicationInterval));
            // 5. 将定时任务提交给定时器线程
            timerTask->async_wait(std::bind(&ASIOSchedulerImpl::LogReplicationTaskImpl::handler, std::placeholders::_1,
                                            logReplicationTaskTimeout));
            // 6. 返回ElectionTimeoutImpl对象
            return logReplicationTaskTimeout;
        }

        std::shared_ptr<ElectionTimeout> ASIOScheduler::scheduleElectionTimeout(Runnable task) {
            if (!this-timerIOService->mStart.load()){
                return nullptr;
            }
            // 1. 创建定时任务
            auto timerTask = std::make_shared<boost::asio::deadline_timer>(*(this->timerIOService->mIOService));
            // 2. 创建ElectionTimeoutImpl对象
            auto electionTimeout = std::make_shared<ASIOSchedulerImpl::ElectionTimeoutImpl>(timerTask, task);
            // 3. 生成随机超时时间
            // TODO: 生成随机超时时间
            int timeout = (this->maxElectionTimeout - this->minElectionTimeout) / 2;
            // 4. 设置定时任务
            timerTask->expires_from_now(boost::posix_time::milliseconds(timeout));
            // 5. 将定时任务提交给定时器线程
            timerTask->async_wait(std::bind(&ASIOSchedulerImpl::ElectionTimeoutImpl::handler, std::placeholders::_1,
                                            electionTimeout));
            // 6. 返回ElectionTimeoutImpl对象
            return electionTimeout;
        }
    }
}