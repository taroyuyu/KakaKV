//
// Created by 凌宇 on 2021/9/21.
//

#ifndef KAKAKV_TASKEXECUTOR_H
#define KAKAKV_TASKEXECUTOR_H

namespace kakakv{
    namespace task{
        class TaskExecutor {
        public:
            TaskExecutor() = default;
            class InterruptedException{
            };
            virtual void shutdown()throw(InterruptedException) = 0;

            virtual ~TaskExecutor(){
            }
        };
    }
}


#endif //KAKAKV_TASKEXECUTOR_H
