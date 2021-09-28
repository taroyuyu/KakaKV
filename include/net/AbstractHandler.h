//
// Created by 凌宇 on 2021/9/28.
//

#ifndef KAKAKV_ABSTRACTHANDLER_H
#define KAKAKV_ABSTRACTHANDLER_H

#include <common/eventBus/EventBus.h>
#include <memory>

namespace kakakv {
    namespace net {

        class Channel;

        class AbstractHandler {
        public:
            AbstractHandler(std::shared_ptr<common::EventBus> eventBus);
            virtual ~AbstractHandler() = 0;
        protected:
            void channelActive(std::weak_ptr<Channel> channel);
            std::shared_ptr<common::EventBus> mEventBus;
            std::weak_ptr<Channel> mChannel;
        };
    }
}


#endif //KAKAKV_ABSTRACTHANDLER_H
