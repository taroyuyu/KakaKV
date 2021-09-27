//
// Created by 凌宇 on 2021/9/21.
//

#ifndef KAKAKV_MEMORYNODESTORE_H
#define KAKAKV_MEMORYNODESTORE_H

#include <server/NodeStore.h>

namespace kakakv{
    namespace server{
        class MemoryNodeStore:public NodeStore{
        public:
            MemoryNodeStore():term(0),votedFor(cluster::NULLNodeId){
            }
            MemoryNodeStore(unsigned long long term,cluster::NodeId votedFor):term(term),votedFor(votedFor){
            }
            unsigned long long getTerm()throw()override;
            void setTerm(unsigned long long term)throw()override;
            cluster::NodeId getVotedFor()throw()override;
            void setVotedFor(const cluster::NodeId votedFor)throw()override;
            void close()override;
        private:
            unsigned long long term;
            cluster::NodeId votedFor;
        };
    }
}


#endif //KAKAKV_MEMORYNODESTORE_H
