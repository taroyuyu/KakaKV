//
// Created by 凌宇 on 2021/9/20.
//

#ifndef KAKAKV_NODEGROUP_H
#define KAKAKV_NODEGROUP_H

#include <cluster/NodeId.h>
#include <map>
#include <cluster/NodeEndpoint.h>
#include <vector>
#include <cluster/GroupMember.h>
namespace kakakv {
    namespace cluster {
        class NodeGroup {
        public:
            class EndpointsEmptyException{

            };
            NodeGroup(NodeEndpoint endpoint)throw(EndpointsEmptyException): NodeGroup({endpoint},endpoint.nodeId){

            }
            NodeGroup(std::vector<NodeEndpoint> endpoints,NodeId selfId)throw(EndpointsEmptyException): mSelfId(selfId){
                // 从节点列表中构建成员映射表
                if (endpoints.size() <= 0){
                    throw EndpointsEmptyException();
                }
                for(auto endpoint : endpoints){
                    this->memberMap.insert({endpoint.nodeId,std::make_shared<GroupMember>(endpoint)});
                }
            }
            std::shared_ptr<GroupMember> findMember(const NodeId nodeId){
                auto memeberIt = this->memberMap.find(nodeId);
                if (memeberIt != this->memberMap.end())
                    return memeberIt->second;
                else
                    return nullptr;
            }
            std::vector<std::shared_ptr<GroupMember>> listReplicationTarget(){
                std::vector<std::shared_ptr<GroupMember>> result;
                for (auto item : this->memberMap){
                    if (item.first != this->mSelfId){
                        result.push_back(item.second);
                    }
                }
                return result;
            }
        private:
            const NodeId mSelfId; // 当前节点Id
            std::map<NodeId,std::shared_ptr<GroupMember>> memberMap;// 成员表
        };
    }
}


#endif //KAKAKV_NODEGROUP_H
