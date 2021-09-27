//
// Created by 凌宇 on 2021/9/25.
//

#ifndef KAKAKV_RECEIVEREQUESTVOTERESPONSE_H
#define KAKAKV_RECEIVEREQUESTVOTERESPONSE_H

#include <common/eventBus/Event.h>
#include <typeinfo>
namespace kakakv {
    namespace server {
        namespace event {
            class ReceiveRequestVoteResponse:public common::Event{
            public:
                static std::string eventType(){
                    return "kakakv::server::event::ReceiveRequestVoteResponse";
                }
                std::string getEventType()const override{
                    return this->getEventType();
                }
            };
        }
    }
}


#endif //KAKAKV_RECEIVEREQUESTVOTERESPONSE_H
