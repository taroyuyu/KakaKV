//
// Created by 凌宇 on 2021/9/21.
//

#include <cluster/NodeId.h>

namespace kakakv{
    namespace cluster{
        std::ostream & operator<<(std::ostream & cout,const NodeId & nodeId){
            cout<<nodeId.value;
        }
        cluster::NodeId::operator std::string()const throw(){
            return this->value;
        }
        bool NodeId::operator<(const cluster::NodeId right)const{
            return this->value < right.value;
        }
        bool cluster::NodeId::operator!=(const cluster::NodeId  right)const{
            return this->value != right.value;
        }
        bool NodeId::operator==(const NodeId  right)const{
            return !(*this != right);
        }
        extern const cluster::NodeId NULLNodeId{""};
    }
}