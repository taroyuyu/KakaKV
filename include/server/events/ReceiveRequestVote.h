//
// Created by 凌宇 on 2021/9/25.
//

#ifndef KAKAKV_RECEIVEREQUESTVOTE_H
#define KAKAKV_RECEIVEREQUESTVOTE_H

#include <common/eventBus/Event.h>
#include <typeinfo>
namespace kakakv {
    namespace server {
        namespace event {
            class ReceiveRequestVote:public common::Event{
            public:
                static std::string eventType(){
                    return "kakakv::server::event::ReceiveRequestVote";
                }
                std::string getEventType()const override{
                    return this->getEventType();
                }
            };
        }
    }
}


#endif //KAKAKV_RECEIVEREQUESTVOTE_H
