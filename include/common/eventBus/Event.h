//
// Created by 凌宇 on 2021/9/21.
//

#ifndef KAKAKV_EVENT_H
#define KAKAKV_EVENT_H

#include <string>
namespace kakakv {
    namespace common {
        class Event {
        public:
            virtual std::string getEventType()const = 0;
            virtual ~Event() = 0;

        };
    }
}


#endif //KAKAKV_EVENT_H
