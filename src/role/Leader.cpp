//
// Created by 凌宇 on 2021/9/20.
//

#include <role/Leader.h>
namespace kakakv {
    namespace role {
        void Leader::cancelTimeoutOrTask(){

        }

        std::ostream & operator<<(std::ostream & cout,Leader & leader){
            cout<<"Leader{term="<<leader.term<<"}";
            return cout;
        }
    }
}