//
// Created by 凌宇 on 2021/9/25.
//

#ifndef KAKAKV_SERVER_RECEIVEREQUESTVOTERESPONSE_H
#define KAKAKV_SERVER_RECEIVEREQUESTVOTERESPONSE_H

#include <common/eventBus/Event.h>
#include <typeinfo>
#include <message/RequestVote.h>
#include <message/RequestVoteResponse.h>
namespace kakakv {
    namespace server {
        namespace event {
            class ReceiveRequestVoteResponse:public common::Event{
            public:
                ReceiveRequestVoteResponse(std::shared_ptr<const message::RequestVoteResponse> requestVoteResponseMessage):
                        mRequestVoteResponseMessage(requestVoteResponseMessage)
                {

                }
                static std::string eventType(){
                    return "kakakv::server::event::ReceiveRequestVoteResponse";
                }
                std::string getEventType()const override{
                    return this->getEventType();
                }
                std::shared_ptr<const message::RequestVoteResponse> requestVoteResponseMessage()const{
                    return this->mRequestVoteResponseMessage;
                }
            private:
                const std::shared_ptr<const message::RequestVoteResponse> mRequestVoteResponseMessage;
            };
        }
    }
}


#endif //KAKAKV_SERVER_RECEIVEREQUESTVOTERESPONSE_H
