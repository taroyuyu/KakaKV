//
// Created by 凌宇 on 2021/9/20.
//

#ifndef KAKAKV_ROLE_H
#define KAKAKV_ROLE_H

namespace kakakv{
    namespace role{
        class Role {
        public:
            virtual ~Role() = 0;
            unsigned long long getTerm()const{
                return this->term;
            }
            virtual void cancelTimeoutOrTask() = 0;
        protected:
            Role(unsigned long long term):term(term){
            }
            Role(const Role &) = delete;
            const unsigned long long term;
        };
    }
}


#endif //KAKAKV_ROLE_H
