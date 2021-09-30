//
// Created by 凌宇 on 2021/9/20.
//

#ifndef KAKAKV_NODECONTEXT_H
#define KAKAKV_NODECONTEXT_H

#include <cluster/NodeId.h>
#include <net/ASIOConnector.h>
#include <task/Scheduler.h>
#include <common/eventBus/EventBus.h>
#include <server/NodeStore.h>
#include <cluster/NodeGroup.h>
#include <log/LogComponent.h>
#include <boost/asio.hpp>
namespace kakakv{
    namespace server{
        class NodeBuilder;
        class Node;
        class NodeContext{
            friend NodeBuilder;
            friend Node;
        public:
            cluster::NodeId selfId()const{
                return this->mSelfId;
            }
            std::shared_ptr<net::ASIOConnector> connector()const{
                return this->mConnector;
            }
            std::shared_ptr<task::Scheduler> scheduler()const{
                return this->mScheduler;
            }
            std::shared_ptr<boost::asio::io_service> taskExecutor()const{
                return this->mTaskExecutor;
            }
            cluster::NodeGroup mGroup;//成员表
        private:
            NodeContext(cluster::NodeId selfId,cluster::NodeGroup group): mSelfId(selfId), mGroup(group){
            };
            void setSelfId(const cluster::NodeId selfId){
                this->mSelfId = selfId;
            }
            void setEventBus(std::shared_ptr<common::EventBus> eventBus){
                this->mEventBus = eventBus;
            }
            void setScheduler(std::shared_ptr<task::Scheduler> scheduler){
                this->mScheduler = scheduler;
            }
            void setConnector(std::shared_ptr<net::ASIOConnector> connector){
                this->mConnector = connector;
            }
            void setTaskExecutor(std::shared_ptr<boost::asio::io_service> taskExecutor){
                this->mTaskExecutor = taskExecutor;
            }
        private:
            cluster::NodeId mSelfId;
            std::shared_ptr<net::ASIOConnector> mConnector;
            std::shared_ptr<task::Scheduler> mScheduler;
            std::shared_ptr<common::EventBus> mEventBus;
            std::shared_ptr<boost::asio::io_service> mIOExecutor; // IO执行器
            std::shared_ptr<boost::asio::io_service> mTaskExecutor; // 任务执行器
            std::shared_ptr<NodeStore> mStore;// 部分角色状态数据存储
            std::shared_ptr<log::LogComponent> mLog;
        };
    }
}


#endif //KAKAKV_NODECONTEXT_H
