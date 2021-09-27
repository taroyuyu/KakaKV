//
// Created by 凌宇 on 2021/9/20.
//

#ifndef KAKAKV_NODEID_H
#define KAKAKV_NODEID_H
#include <string>
#include <ostream>
namespace kakakv {
    namespace cluster {
        class NodeId{
            friend std::ostream & operator<<(std::ostream & cout,const NodeId & nodeId);
        public:
            explicit NodeId(std::string value)throw():value(value){
            }
            operator std::string()const throw();
            bool operator<(const NodeId  right)const;
            bool operator!=(const NodeId  right)const;
            bool operator==(const NodeId  right)const;
        private:
            std::string value;
        };
        extern const NodeId NULLNodeId;
        std::ostream & operator<<(std::ostream & cout,const NodeId & nodeId);
    }
}
#endif //KAKAKV_NODEID_H
