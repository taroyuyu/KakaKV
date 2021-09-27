//
// Created by 凌宇 on 2021/9/21.
//

#ifndef KAKAKV_TASK_ELECTIONTIMEOUT_H
#define KAKAKV_TASK_ELECTIONTIMEOUT_H

namespace kakakv {
    namespace task {
        class ElectionTimeout{
        public:
            virtual ~ElectionTimeout() = 0;
            virtual void cancel() = 0;
        };
    }
}


#endif //KAKAKV_TASK_ELECTIONTIMEOUT_H
