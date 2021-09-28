//
// Created by 凌宇 on 2021/9/28.
//

#include <net/AbstractHandler.h>

namespace kakakv {
    namespace net {
        AbstractHandler::AbstractHandler(std::shared_ptr<common::EventBus> eventBus):
        mEventBus(eventBus){

        }

        AbstractHandler::~AbstractHandler(){

        }

        void AbstractHandler::channelActive(std::weak_ptr<Channel> channel){
            this->mChannel = channel;
        }
    }
}