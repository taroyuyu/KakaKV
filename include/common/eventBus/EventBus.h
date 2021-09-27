//
// Created by 凌宇 on 2021/9/21.
//

#ifndef KAKAKV_EVENTBUS_H
#define KAKAKV_EVENTBUS_H

#include <memory>
#include <list>
#include <map>
#include <common/eventBus/EventListener.h>
#include <mutex>
namespace kakakv {
    namespace common {
        class EventBus {
        public:
            EventBus();
            ~EventBus();
            /**
             * 获取默认的EventBus
             * @return
             */
            static EventBus & getDefault();

            void registerEvent(std::string eventType,EventListener * eventListenrPtr);
            void unregister(EventListener * eventListenrPtr,std::string eventType);
            void unregister(EventListener * eventListenrPtr);
            void Post(std::shared_ptr<const Event> event);
        private:
            static EventBus * defaultEventBus;
            mutable std::mutex m_mutex;
            std::map<std::string,std::list<EventListener*>> m_listenerMap;
        };
    }
}


#endif //KAKAKV_EVENTBUS_H
