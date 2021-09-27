//
// Created by 凌宇 on 2021/9/20.
//

#ifndef KAKAKV_FOLLOWER_H
#define KAKAKV_FOLLOWER_H

#include <role/Role.h>
#include <cluster/NodeId.h>
#include <task//ElectionTimeout.h>
#include <iostream>
namespace kakakv {
    namespace role {
        class Follower: public Role{
            friend std::ostream & operator<<(std::ostream & cout,Follower & follower);
        public:
            Follower(unsigned long long term,cluster::NodeId votedFor,cluster::NodeId leaderId,std::shared_ptr<task::ElectionTimeout> electionTimeout): Role(term),votedFor(votedFor),leaderId(leaderId),electionTimeout(electionTimeout){
            }
            cluster::NodeId getVotedFor(){
                return this->votedFor;
            }
            cluster::NodeId getLeaderId(){
                return this->leaderId;
            }
            /**
             * 取消选举超时定时器
             */
            void cancelTimeoutOrTask()override;
        private:
            const cluster::NodeId votedFor;
            const cluster::NodeId leaderId;
            const std::shared_ptr<task::ElectionTimeout> electionTimeout;
        };
        std::ostream & operator<<(std::ostream & cout,Follower & follower);
    }
}


#endif //KAKAKV_FOLLOWER_H
