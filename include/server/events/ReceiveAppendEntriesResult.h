//
// Created by 凌宇 on 2021/9/25.
//

#ifndef KAKAKV_RECEIVEAPPENDENTRIESRESULT_H
#define KAKAKV_RECEIVEAPPENDENTRIESRESULT_H

#include <common/eventBus/Event.h>
#include <typeinfo>

namespace kakakv {
    namespace server {
        namespace event {
            class ReceiveAppendEntriesResult : public common::Event {
            public:
                static std::string eventType(){
                    return "kakakv::server::event::ReceiveAppendEntriesResult";
                }
                std::string getEventType()const override{
                    return this->getEventType();
                }
            };
        }
    }
}


#endif //KAKAKV_RECEIVEAPPENDENTRIESRESULT_H
