//
// Created by 凌宇 on 2021/9/20.
//

#include <message/RequestVoteResponse.h>

namespace kakakv {
    namespace message {
        std::ostream & operator<<(std::ostream & cout,const RequestVoteResponse & response){
            cout<<"RequestVoteResponse{voterId="<<response.voterId
                <<",term="<<response.term
                <<",voteGranted="<<response.voteGranted
                <<"}";
            return cout;
        }
    }
}