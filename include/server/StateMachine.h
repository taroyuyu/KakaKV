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
        class StateMachineContext;
        class StateMachine {
        public:
            virtual ~StateMachine() = 0;
            /**
             * 获取 lastApplied
             * @return
             */
            virtual unsigned long long getLastApplied() = 0;
            /**
             * 应用日志
             * @param context
             * @param index
             * @param commandBytes
             * @param firstLogIndex
             */
            virtual void applyLog(std::shared_ptr<StateMachineContext> context,unsigned long long index,std::string commandBytes,unsigned long long firstLogIndex) = 0;
            /**
             * 关闭状态机
             */
            virtual void shutdown() = 0;
            virtual void applyEntry(std::shared_ptr<log::LogEntry> entry) = 0;
        };
    }
}


#endif //KAKAKV_STATEMACHINE_H
