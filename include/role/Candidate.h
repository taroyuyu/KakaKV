//
// Created by 凌宇 on 2021/9/20.
//

#ifndef KAKAKV_CANDIDATE_H
#define KAKAKV_CANDIDATE_H

#include <role/Role.h>
#include <cluster/NodeId.h>
#include <vote/ElectionTimeout.h>
#include <iostream>
namespace kakakv {
    namespace role {
        class Candidate:public Role{
            friend std::ostream & operator<<(std::ostream & cout,Candidate & candidate);
        public:
            Candidate(unsigned long long term,vote::ElectionTimeout electionTimeout,const unsigned int votesCount = 1): Role(term),votesCount(votesCount),electionTimeout(electionTimeout){

            }
            unsigned int getVotesCount(){
                return this->votesCount;
            }
            void cancelTimeoutOrTask()override;
        private:
            const unsigned int votesCount;
            const vote::ElectionTimeout electionTimeout;
        };
        std::ostream & operator<<(std::ostream & cout,Candidate & candidate);
    }
}


#endif //KAKAKV_CANDIDATE_H
