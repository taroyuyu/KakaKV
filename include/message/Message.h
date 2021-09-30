//
// Created by 凌宇 on 2021/9/21.
//

#ifndef KAKAKV_MESSAGE_H
#define KAKAKV_MESSAGE_H

#include <net/core/Message.h>

namespace kakakv{
    namespace message{
    class Message:public net::Message{
        public:
            Message(const unsigned long long term):term(term){
            }
            virtual ~Message() = 0;
            const unsigned long long term;//选举term
        };
    }
}


#endif //KAKAKV_MESSAGE_H
