//
// Created by 凌宇 on 2021/9/21.
//

#ifndef KAKAKV_NODESTORE_H
#define KAKAKV_NODESTORE_H

#include <cluster/NodeId.h>

namespace kakakv{
    namespace server{
        class NodeStore {
        public:
            NodeStore() = default;
            virtual ~NodeStore(){
            };
            virtual unsigned long long getTerm()throw() = 0;
            virtual void setTerm(unsigned long long term)throw() = 0;
            virtual cluster::NodeId getVotedFor()throw() = 0;
            virtual void setVotedFor(const cluster::NodeId votedFor)throw() = 0;
            virtual void close() = 0;
        };
    }
}


#endif //KAKAKV_NODESTORE_H
