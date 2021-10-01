//
// Created by 凌宇 on 2021/10/1.
//

#ifndef KAKAKV_STATEMACHINE_H
#define KAKAKV_STATEMACHINE_H

#include <memory>

namespace kakakv {
    namespace log {
        class LogEntry;
    }
    namespace server {
        class StateMachine {
        public:
            virtual ~StateMachine() = 0;
            virtual void apply(std::shared_ptr<log::LogEntry> entry) = 0;
        };
    }
}


#endif //KAKAKV_STATEMACHINE_H
