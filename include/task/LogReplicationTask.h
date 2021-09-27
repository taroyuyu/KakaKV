//
// Created by 凌宇 on 2021/9/21.
//

#ifndef KAKAKV_LOGREPLICATIONTASK_H
#define KAKAKV_LOGREPLICATIONTASK_H

namespace kakakv {
    namespace task {
        class LogReplicationTask {
        public:
            virtual ~LogReplicationTask() = 0;
            virtual void cancel() = 0;
        };
    }
}


#endif //KAKAKV_LOGREPLICATIONTASK_H
