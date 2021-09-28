//
// Created by 凌宇 on 2021/9/21.
//

#include <server/NodeBuilder.h>

namespace kakakv {
    namespace server {
        NodeBuilder::NodeBuilder(cluster::NodeEndpoint endpoint): NodeBuilder({endpoint},endpoint.nodeId){

        }
        NodeBuilder::NodeBuilder(std::vector<cluster::NodeEndpoint> endpoints,cluster::NodeId selfId): selfId(selfId){

        }
        NodeBuilder & NodeBuilder::setConnector(std::shared_ptr<net::ASIOConnector> connector){
            this->mConnector = connector;
            return *this;
        }
        std::unique_ptr<Node> NodeBuilder::build(){

        }

        std::shared_ptr<NodeContext> NodeBuilder::buildContext(){
            net::Endpoint endpoint("127.0.1",8080);
            cluster::NodeGroup group({this->selfId,endpoint});
            auto context = std::shared_ptr<NodeContext>(new NodeContext(this->selfId,group));
            context->setConnector(this->mConnector);
            return context;
        }
    }
}