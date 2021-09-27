//
// Created by 凌宇 on 2021/9/21.
//

#ifndef KAKAKV_NODEBUILDER_H
#define KAKAKV_NODEBUILDER_H

#include <memory>
#include <server/Node.h>
#include <cluster/NodeEndpoint.h>
#include <vector>
#include <net/Connector.h>
#include <server/NodeContext.h>
namespace kakakv{
    namespace server{
        class NodeBuilder {
        public:
            NodeBuilder(cluster::NodeEndpoint endpoint);
            NodeBuilder(std::vector<cluster::NodeEndpoint> endpoints,cluster::NodeId selfId);
            NodeBuilder & setConnector(std::shared_ptr<net::Connector> connector);
            std::unique_ptr<Node> build();
        private:
            std::shared_ptr<NodeContext> buildContext();
            cluster::NodeId selfId;//当前节点的Id
            std::shared_ptr<net::Connector> mConnector;
        };
    }
}

#endif //KAKAKV_NODEBUILDER_H
