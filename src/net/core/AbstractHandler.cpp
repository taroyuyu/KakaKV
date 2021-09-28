//
// Created by 凌宇 on 2021/9/28.
//

#include <net/core/AbstractHandler.h>

namespace kakakv {
    namespace net {
        AbstractHandler::~AbstractHandler(){
        }

        void AbstractHandler::channelRead(std::weak_ptr<const Channel> channel,std::shared_ptr<Message> message){

        }

        void AbstractHandler::channelWrite(std::weak_ptr<const Channel> channel,std::shared_ptr<Message> message){

        }

        void AbstractHandler::channelActive(std::weak_ptr<const Channel> channel){

        }

        void AbstractHandler::channelClose(std::weak_ptr<const Channel> channel){

        }
    }
}