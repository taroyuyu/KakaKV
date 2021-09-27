//
// Created by 凌宇 on 2021/9/20.
//

#ifndef KAKAKV_LEADER_H
#define KAKAKV_LEADER_H

#include <role/Role.h>
#include <task/LogReplicationTask.h>
#include <iostream>
namespace kakakv {
    namespace role {
        class Leader: public Role{
            friend std::ostream & operator<<(std::ostream & cout,Leader & leader);
        public:
            Leader(unsigned long long term,std::shared_ptr<task::LogReplicationTask> logReplicationTask): Role(term),logReplicationTask(logReplicationTask){
            }
            /**
             * 取消日志复制定时任务
             */
            void cancelTimeoutOrTask()override;
        private:
            const std::shared_ptr<task::LogReplicationTask> logReplicationTask;
        };
        std::ostream & operator<<(std::ostream & cout,Leader & leader);
    }
}


#endif //KAKAKV_LEADER_H
