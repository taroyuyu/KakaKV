//
// Created by 凌宇 on 2021/9/21.
//

#ifndef KAKAKV_NODEBUILDER_H
#define KAKAKV_NODEBUILDER_H

#include <memory>
#include <cluster/NodeGroup.h>
#include <vector>
namespace kakakv{
    namespace common {
        class EventBus;
    }
    namespace cluster{
        class NodeGroup;
    }
    namespace task {
        class Scheduler;
        class IOService;
    }
    namespace net{
        class ASIOConnector;
    }
    namespace server{
        class Node;
        class NodeContext;
        class NodeBuilder {
        public:
            NodeBuilder(cluster::NodeEndpoint endpoint);
            NodeBuilder(std::vector<cluster::NodeEndpoint> endpoints,cluster::NodeId selfId);
            NodeBuilder & setConnector(std::shared_ptr<net::ASIOConnector> connector);
            NodeBuilder & setScheduler(std::shared_ptr<task::Scheduler> scheduler);
            NodeBuilder & setTaskExecutor(std::shared_ptr<task::IOService> taskExecutor);
            std::unique_ptr<Node> build();
        private:
            std::shared_ptr<NodeContext> buildContext();
            const cluster::NodeGroup group;//集群成员
            const cluster::NodeId selfId;//当前节点的Id
            std::shared_ptr<common::EventBus> eventBus;//事件总线
            std::shared_ptr<task::Scheduler> mScheduler;//定时器
            std::shared_ptr<net::ASIOConnector> mConnector;//RPC连接器
            std::shared_ptr<task::IOService> mTaskExecutor;//主线程执行器
        };
    }
}

#endif //KAKAKV_NODEBUILDER_H
