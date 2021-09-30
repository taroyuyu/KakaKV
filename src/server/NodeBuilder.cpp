//
// Created by 凌宇 on 2021/9/21.
//

#include <server/NodeBuilder.h>
#include <common/eventBus/EventBus.h>
#include <server/NodeContext.h>
#include <server/Node.h>
namespace kakakv {
    namespace server {
        NodeBuilder::NodeBuilder(cluster::NodeEndpoint endpoint): NodeBuilder({endpoint},endpoint.nodeId){

        }
        NodeBuilder::NodeBuilder(std::vector<cluster::NodeEndpoint> endpoints,cluster::NodeId selfId):
        group(endpoints,selfId),selfId(selfId),eventBus(std::make_shared<common::EventBus>()){

        }
        NodeBuilder & NodeBuilder::setConnector(std::shared_ptr<net::ASIOConnector> connector){
            this->mConnector = connector;
            return *this;
        }
        NodeBuilder & NodeBuilder::setScheduler(std::shared_ptr<task::Scheduler> scheduler){
            this->mScheduler = scheduler;
            return *this;
        }

        NodeBuilder & NodeBuilder::setTaskExecutor(std::shared_ptr<task::IOService> taskExecutor){
            this->mTaskExecutor = taskExecutor;
            return *this;
        }
        std::unique_ptr<Node> NodeBuilder::build(){
            return std::make_unique<Node>(this->buildContext());
        }

        std::shared_ptr<NodeContext> NodeBuilder::buildContext(){
            auto context = std::shared_ptr<NodeContext>(new NodeContext(this->selfId,this->group));
            context->setEventBus(this->eventBus);
            context->setScheduler(this->mScheduler);
            context->setConnector(this->mConnector);
            return context;
        }
    }
}