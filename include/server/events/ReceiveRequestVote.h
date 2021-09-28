//
// Created by 凌宇 on 2021/9/25.
//

#ifndef KAKAKV_SERVER_RECEIVEREQUESTVOTE_H
#define KAKAKV_SERVER_RECEIVEREQUESTVOTE_H

#include <common/eventBus/Event.h>
#include <typeinfo>
#include <message/RequestVote.h>
namespace kakakv {
    namespace server {
        namespace event {
            class ReceiveRequestVote:public common::Event{
            public:
                ReceiveRequestVote(std::shared_ptr<const message::RequestVote> message):
                payload(message){

                }
                static std::string eventType(){
                    return "kakakv::server::event::ReceiveRequestVote";
                }
                std::string getEventType()const override{
                    return this->getEventType();
                }
                std::shared_ptr<const message::RequestVote> message()const{
                    return this->payload;
                }
            private:
                const std::shared_ptr<const message::RequestVote> payload;
            };
        }
    }
}


#endif //KAKAKV_SERVER_RECEIVEREQUESTVOTE_H
