//
// Created by 凌宇 on 2021/9/20.
//

#ifndef KAKAKV_CANDIDATE_H
#define KAKAKV_CANDIDATE_H

#include <role/Role.h>
#include <cluster/NodeId.h>
#include <task//ElectionTimeout.h>
#include <iostream>
namespace kakakv {
    namespace role {
        class Candidate:public Role{
            friend std::ostream & operator<<(std::ostream & cout,Candidate & candidate);
        public:
            Candidate(unsigned long long term,std::shared_ptr<task::ElectionTimeout> electionTimeout,const unsigned int votesCount = 1): Role(term),votesCount(votesCount),electionTimeout(electionTimeout){

            }
            unsigned int getVotesCount(){
                return this->votesCount;
            }
            /**
             * 取消选举超时定时器
             */
            void cancelTimeoutOrTask()override;
        private:
            const unsigned int votesCount;
            const std::shared_ptr<task::ElectionTimeout> electionTimeout;
        };
        std::ostream & operator<<(std::ostream & cout,Candidate & candidate);
    }
}


#endif //KAKAKV_CANDIDATE_H
