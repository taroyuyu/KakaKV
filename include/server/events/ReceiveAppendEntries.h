//
// Created by 凌宇 on 2021/9/25.
//

#ifndef KAKAKV_RECEIVEAPPENDENTRIES_H
#define KAKAKV_RECEIVEAPPENDENTRIES_H

#include <common/eventBus/Event.h>
#include <typeinfo>

namespace kakakv {
    namespace server {
        namespace event {
            class ReceiveAppendEntries : public common::Event {
            public:
                static std::string eventType(){
                    return "kakakv::server::event::ReceiveAppendEntries";
                }
                std::string getEventType()const override{
                    return this->getEventType();
                }
            };
        }
    }
}


#endif //KAKAKV_RECEIVEAPPENDENTRIES_H
