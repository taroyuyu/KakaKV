//
// Created by 凌宇 on 2021/9/21.
//

#include <server/MemoryNodeStore.h>

namespace kakakv{
    namespace server{
        unsigned long long MemoryNodeStore::getTerm()throw(){
            return this->term;
        }
        void MemoryNodeStore::setTerm(unsigned long long term)throw(){
            this->term = term;
        }
        cluster::NodeId MemoryNodeStore::getVotedFor()throw(){
            return this->votedFor;
        }
        void MemoryNodeStore::setVotedFor(const cluster::NodeId votedFor)throw(){
            this->votedFor = votedFor;
        }
        void MemoryNodeStore::close(){
        }
    }
}