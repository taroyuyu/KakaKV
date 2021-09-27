//
// Created by 凌宇 on 2021/9/20.
//

#include <message/AppendEntries.h>

namespace kakakv {
    namespace message {
        std::ostream & operator<<(std::ostream & cout,const AppendEntries & appendEntries){
            cout<<"AppendEntries{leaderId="<<appendEntries.leaderId
                <<",entryList.size="<<appendEntries.entryList.size()
                <<",leaderCommitIndex="<<appendEntries.leaderCommitIndex
                <<",prevLogIndex="<<appendEntries.prevLogIndex
                <<",prevLogTerm="<<appendEntries.prevLogTerm
                <<",term="<<appendEntries.term
                <<"}";
            return cout;
        }
    }
}