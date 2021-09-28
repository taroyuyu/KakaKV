//
// Created by 凌宇 on 2021/9/20.
//

#ifndef KAKAKV_NODEENDPOINT_H
#define KAKAKV_NODEENDPOINT_H

#include <cluster/NodeId.h>
#include <net/core/Endpoint.h>
namespace kakakv {
    namespace cluster {
        class NodeEndpoint {
        public:
            NodeEndpoint(NodeId nodeId,net::Endpoint endpoint):nodeId(nodeId), endpoint(endpoint){
            }

            NodeId nodeId;
            net::Endpoint endpoint;
        };
    }
}


#endif //KAKAKV_NODEENDPOINT_H
