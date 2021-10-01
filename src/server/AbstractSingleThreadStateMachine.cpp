//
// Created by 凌宇 on 2021/10/1.
//

#include <server/AbstractSingleThreadStateMachine.h>
#include <task/ASIOIOService.h>
namespace kakakv {
    namespace server {
        AbstractSingleThreadStateMachine::AbstractSingleThreadStateMachine():
                mTaskExecutor(std::make_shared<task::ASIOIOService>()),lastApplied(0){
        }
        /**
         * 获取 lastApplied
         * @return
         */
        unsigned long long AbstractSingleThreadStateMachine::getLastApplied()const{
            return this->lastApplied;
        }
        /**
         * 应用日志
         * @param context
         * @param index
         * @param commandBytes
         * @param firstLogIndex
         */
        void AbstractSingleThreadStateMachine::applyLog(std::shared_ptr<StateMachineContext> context,unsigned long long index,std::string commandBytes,unsigned long long firstLogIndex){
            this->mTaskExecutor->post([=](std::shared_ptr<task::IOService> ioService){
                if (!ioService) {
                    return;
                }
                this->doApplyLog(context,index,commandBytes,firstLogIndex);
            });
        }
        /**
         * 关闭状态机
         */
        void AbstractSingleThreadStateMachine::shutdown(){
            try {
                this->mTaskExecutor->shutdownGracefully();
            }catch (...){

            }
        }
        void AbstractSingleThreadStateMachine::applyEntry(std::shared_ptr<log::LogEntry> entry){

        }

        void AbstractSingleThreadStateMachine::doApplyLog(std::shared_ptr<StateMachineContext> context,int index,std::string commandBytes,unsigned long long firstLogIndex){
            // 忽略已经应用过的日志
            if (index <= lastApplied){
                return;
            }
            this->applyCommand(commandBytes);
            // 更新lastApplied
            this->lastApplied = index;
        }
    }
}