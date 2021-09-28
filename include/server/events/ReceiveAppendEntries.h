//
// Created by 凌宇 on 2021/9/25.
//

#ifndef KAKAKV_SERVER_RECEIVEAPPENDENTRIES_H
#define KAKAKV_SERVER_RECEIVEAPPENDENTRIES_H

#include <common/eventBus/Event.h>
#include <typeinfo>
#include <message/AppendEntries.h>
namespace kakakv {
    namespace server {
        namespace event {
            class ReceiveAppendEntries : public common::Event {
            public:
                ReceiveAppendEntries(std::shared_ptr<message::AppendEntries> appendEntriesMessage):
                payload(appendEntriesMessage){
                }
                static std::string eventType(){
                    return "kakakv::server::event::ReceiveAppendEntries";
                }
                std::string getEventType()const override{
                    return this->getEventType();
                }
                std::shared_ptr<const message::AppendEntries> appendEntriesMessage()const{
                    return this->payload;
                }
            private:
                const std::shared_ptr<const message::AppendEntries> payload;
            };
        }
    }
}


#endif //KAKAKV_SERVER_RECEIVEAPPENDENTRIES_H
