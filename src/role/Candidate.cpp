//
// Created by 凌宇 on 2021/9/20.
//

#include <role/Candidate.h>

namespace kakakv {
    namespace role {
        void Candidate::cancelTimeoutOrTask(){

        }
        std::ostream & operator<<(std::ostream & cout,Candidate & candidate){
            cout<<"Candidate{term="<<candidate.term<<",votesCount="<<candidate.votesCount<<",electionTimeout="<<candidate.electionTimeout<<"}";
            return cout;
        }
    }
}