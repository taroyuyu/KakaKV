//
// Created by 凌宇 on 2021/9/28.
//

#ifndef KAKAKV_RAFTMESSAGEHANDLER_H
#define KAKAKV_RAFTMESSAGEHANDLER_H

#include <net/core/AbstractHandler.h>
#include <common/eventBus/EventBus.h>

namespace kakakv {
    namespace server {
        class RaftMessageHandler : public net::AbstractHandler {
        public:
            RaftMessageHandler(std::shared_ptr<common::EventBus> eventBus);

            void channelRead(std::weak_ptr<const net::Channel> channel, std::shared_ptr<net::Message> message) override;

        private:
            const std::shared_ptr<common::EventBus> mEventBus;
        };
    }
}


#endif //KAKAKV_RAFTMESSAGEHANDLER_H
