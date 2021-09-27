//
// Created by 凌宇 on 2021/9/21.
//

#include <task/LogReplicationTask.h>

namespace kakakv {
    namespace task {
        LogReplicationTask::~LogReplicationTask(){
            this->cancel();
        }
    }
}