//
// Created by 凌宇 on 2021/9/20.
//

#ifndef KAKAKV_LEADER_H
#define KAKAKV_LEADER_H

#include <role/Role.h>
#include <iostream>
namespace kakakv {
    namespace role {
        class Leader: public Role{
            friend std::ostream & operator<<(std::ostream & cout,Leader & leader);
        public:
            Leader(unsigned long long term): Role(term){
            }
            void cancelTimeoutOrTask()override;
        };
        std::ostream & operator<<(std::ostream & cout,Leader & leader);
    }
}


#endif //KAKAKV_LEADER_H
