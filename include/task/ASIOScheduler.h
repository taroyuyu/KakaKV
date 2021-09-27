//
// Created by 凌宇 on 2021/9/21.
//

#ifndef KAKAKV_ASIOSCHEDULER_H
#define KAKAKV_ASIOSCHEDULER_H

#include <task/Scheduler.h>
#include <boost/asio.hpp>
namespace kakakv {
    namespace task {

        class ASIOScheduler : public Scheduler {
        public:
            std::shared_ptr<LogReplicationTask> scheduleLogReplicationTask(Runnable task)override;
            std::shared_ptr<ElectionTimeout> scheduleElectionTimeout(Runnable task)override;
        private:

            /**
             * 最小选举超时时间
             */
            const unsigned int minElectionTimeout;
            /**
             * 最大选举超时时间
             */
            const unsigned int maxElectionTimeout;
            /**
             * 初次日志复制延迟时间
             */
            const unsigned int logReplicationDelay;
            /**
             * 日志复制间隔
             */
            const unsigned int logReplicationInterval;


            std::shared_ptr<boost::asio::io_service> timerIOService;// 定时器处理线程
        };
    }
}


#endif //KAKAKV_ASIOSCHEDULER_H
