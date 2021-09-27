//
// Created by 凌宇 on 2021/9/21.
//

#ifndef KAKAKV_SCHEDULER_H
#define KAKAKV_SCHEDULER_H

#include <task/LogReplicationTask.h>
#include <task/ElectionTimeout.h>
#include <memory>
#include <functional>
namespace kakakv {
    namespace task {
        class Scheduler {
        public:
            typedef std::function<void()> Runnable;
            class InterruptedException{
            };
            /**
             * 创建日志复制定时任务
             * @param task
             */
            virtual std::shared_ptr<LogReplicationTask> scheduleLogReplicationTask(Runnable task) = 0;
            /**
             * 创建选举超时器
             * @param task
             */
            virtual std::shared_ptr<ElectionTimeout> scheduleElectionTimeout(Runnable task) = 0;
            /**
             * 关闭定时器
             */
            virtual void stop()throw(InterruptedException) = 0;
            virtual ~Scheduler() = 0;
        };
    }
}


#endif //KAKAKV_SCHEDULER_H
