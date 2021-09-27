//
// Created by 凌宇 on 2021/9/21.
//

#ifndef KAKAKV_EVENTLISTENER_H
#define KAKAKV_EVENTLISTENER_H

#include <common/eventBus/Event.h>
#include <memory>
namespace kakakv {
    namespace common {
        class EventListener {
        public:
            virtual ~EventListener() {

            }

            virtual void onEvent(std::shared_ptr<const Event> event) = 0;
        };
    }
}


#endif //KAKAKV_EVENTLISTENER_H
