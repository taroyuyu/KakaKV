//
// Created by 凌宇 on 2021/9/25.
//

#ifndef KAKAKV_SERVER_EVENT_ELECTIONTIMEOUT_H
#define KAKAKV_SERVER_EVENT_ELECTIONTIMEOUT_H

#include <common/eventBus/Event.h>
#include <typeinfo>

namespace kakakv {
    namespace server {
        namespace event {
            class ElectionTimeout:public common::Event{
            public:
                static std::string eventType(){
                    return "kakakv::server::event::ElectionTimeout";
                }
                std::string getEventType()const override{
                    return this->getEventType();
                }
            };
        }
    }
}

#endif //KAKAKV_SERVER_EVENT_ELECTIONTIMEOUT_H
