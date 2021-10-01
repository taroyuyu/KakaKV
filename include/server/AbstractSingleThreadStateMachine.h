//
// Created by 凌宇 on 2021/10/1.
//

#ifndef KAKAKV_ABSTRACTSINGLETHREADSTATEMACHINE_H
#define KAKAKV_ABSTRACTSINGLETHREADSTATEMACHINE_H

#include <server/StateMachine.h>
namespace kakakv {
    namespace task {
        class ASIOIOService;
    }
    namespace server {
        class AbstractSingleThreadStateMachine : public StateMachine {
        public:
            AbstractSingleThreadStateMachine();

            /**
             * 获取 lastApplied
             * @return
             */
            unsigned long long getLastApplied()const override;

            /**
             * 应用日志
             * @param context
             * @param index
             * @param commandBytes
             * @param firstLogIndex
             */
            void
            applyLog(std::shared_ptr<StateMachineContext> context, unsigned long long index, std::string commandBytes,
                     unsigned long long firstLogIndex) override;

            /**
             * 关闭状态机
             */
            void shutdown() override;

            void applyEntry(std::shared_ptr<log::LogEntry> entry) override;

        protected:
            virtual void applyCommand(std::string commandBytes) = 0;
        private:
            /**
             * @description: 应用日志
             * @执行线程：当前对象的TaskExecutor线程中
             * @param context
             * @param index
             * @param commandBytes
             */
            void doApplyLog(std::shared_ptr<StateMachineContext> context,int index,std::string commandBytes,unsigned long long firstLogIndex);
            std::shared_ptr<task::ASIOIOService> mTaskExecutor;
            volatile unsigned long long lastApplied;
        };
    }
}


#endif //KAKAKV_ABSTRACTSINGLETHREADSTATEMACHINE_H
