//
// Created by 凌宇 on 2021/9/20.
//

#ifndef KAKAKV_NODE_H
#define KAKAKV_NODE_H

#include <memory>
#include <log/LogComponent.h>
#include <server/NodeContext.h>
#include <role/Role.h>
#include <message/RequestVote.h>
#include <message/RequestVoteResponse.h>
#include <message/AppendEntries.h>
#include <message/AppendEntriesResponse.h>
#include <memory>
#include <common/eventBus/EventListener.h>
namespace kakakv {
    namespace server {
        class StateMachine;
        class Node:protected common::EventListener{
        public:
            Node(std::shared_ptr<NodeContext> context);
            class InterruptedException{
            };
            void start();
            void stop()throw(InterruptedException);
            void registerStateMachine(std::shared_ptr<StateMachine> stateMachine);
        protected:
            void onElectionTimeout();
            void onReceiveRequestVote(std::shared_ptr<message::RequestVote> request);
            void onReceiveRequestVoteResponse(std::shared_ptr<message::RequestVoteResponse> response);
            void onReceiveAppendEntries(std::shared_ptr<message::AppendEntries> request);
            void onReceiveAppendEntriesResult(std::shared_ptr<message::AppendEntriesResponse> response);
            /**
             * 变更角色：统一角色变更的代码，以及在角色变化时同步到NodeStore中
             * @param newRole
             */
            void changeToRole(std::shared_ptr<role::Role> newRole);
            void doProcessElectionTimeout();
            std::shared_ptr<message::RequestVoteResponse> doProcessRequestVote(const std::shared_ptr<message::RequestVote> request);
            void doProcessRequestVoteResponse(const std::shared_ptr<message::RequestVoteResponse> reponse);
            std::shared_ptr<message::AppendEntriesResponse> doProcessAppendEntries(const std::shared_ptr<message::AppendEntries> appendEntriesMessage);
            void doProcessAppendEntriesResult(const std::shared_ptr<message::AppendEntriesResponse> response);
            void becomeFollower(unsigned long long term,cluster::NodeId votedFor,cluster::NodeId leaderId,bool scheduleElectionTimeout);
            void replicateLog();
            void doReplicateLog();
            void doReplicateLog(const std::shared_ptr<cluster::GroupMember>  groupMember);
            bool appendEntries(const std::shared_ptr<message::AppendEntries> appendEntriesMessage);
            void registerToEventBus();
            void unregisterToEventBus();
            void onEvent(std::shared_ptr<const common::Event> event)override;
            std::shared_ptr<task::ElectionTimeout> scheduleElectionTimeOut();
            std::shared_ptr<task::LogReplicationTask> scheduleLogReplicationTask();
            void advanceCommitIndex();
        private:
            std::unique_ptr<log::LogComponent> logger;//日志组件
            std::shared_ptr<NodeContext> context;//核心组件上下文
            std::atomic<bool> started;//是否已经启动
            std::shared_ptr<role::Role> role;//当前的角色及相关信息
            std::shared_ptr<StateMachine> stateMachine;//状态机
        };
    }
}


#endif //KAKAKV_NODE_H
