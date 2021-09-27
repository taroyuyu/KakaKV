//
// Created by 凌宇 on 2021/9/20.
//

#include <message/RequestVote.h>

namespace kakakv {
    namespace message {
        std::ostream & operator<<(std::ostream & cout,RequestVote & request){
            cout<<"RequestVote{candidateId="<<request.candidateId
                <<",lastLogIndex="<<request.lastLogIndex
                <<",lastLogTerm="<<request.lastLogTerm
                <<",term="<<request.term
                <<"}";
            return cout;
        }
    }
}