//
// Created by 凌宇 on 2021/9/25.
//

#ifndef KAKAKV_EVENT_RECEIVEAPPENDENTRIESRESULT_H
#define KAKAKV_EVENT_RECEIVEAPPENDENTRIESRESULT_H

#include <common/eventBus/Event.h>
#include <typeinfo>
#include <message/AppendEntries.h>
#include <message/AppendEntriesResponse.h>
namespace kakakv {
    namespace server {
        namespace event {
            class ReceiveAppendEntriesResult : public common::Event {
            public:
                ReceiveAppendEntriesResult(std::shared_ptr<const message::AppendEntriesResponse> appendEntriesResponseMessage):
                mAppendEntriesResponseMessage(appendEntriesResponseMessage){
                }
                static std::string eventType(){
                    return "kakakv::server::event::ReceiveAppendEntriesResult";
                }
                std::string getEventType()const override{
                    return this->getEventType();
                }

            private:
                const std::shared_ptr<const message::AppendEntries> mAppendEntriesMessage;
                const std::shared_ptr<const message::AppendEntriesResponse> mAppendEntriesResponseMessage;
            };
        }
    }
}


#endif //KAKAKV_EVENT_RECEIVEAPPENDENTRIESRESULT_H
