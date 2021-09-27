//
// Created by 凌宇 on 2021/9/20.
//

#ifndef KAKAKV_GROUPMEMBER_H
#define KAKAKV_GROUPMEMBER_H

#include <cluster/NodeEndpoint.h>
#include <cluster/ReplicatingState.h>
#include <memory>
namespace kakakv {
    namespace cluster {
        class GroupMember {
        public:
            GroupMember(NodeEndpoint endpoint): GroupMember(endpoint, nullptr){
            }
            GroupMember(NodeEndpoint endpoint,std::shared_ptr<ReplicatingState> replicatingState):
            endpoint(endpoint),replicatingState(replicatingState){
            }
            NodeEndpoint endpoint;
            std::shared_ptr<ReplicatingState> replicatingState;
        };
    }
}


#endif //KAKAKV_GROUPMEMBER_H
