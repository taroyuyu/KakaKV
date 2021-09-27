//
// Created by 凌宇 on 2021/9/20.
//

#include <role/Follower.h>

namespace kakakv{
    namespace role{
        void Follower::cancelTimeoutOrTask(){
            this->electionTimeout->cancel();
        }

        std::ostream & operator<<(std::ostream & cout,Follower & follower){
            cout<<"Follower{term="<<follower.term<<",leaderId="<<follower.leaderId<<",votedFor="<<follower.votedFor<<",electionTimeout="<<follower.electionTimeout<<"}";
            return cout;
        }
    }
}