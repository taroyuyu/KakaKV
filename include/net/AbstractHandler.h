//
// Created by 凌宇 on 2021/9/28.
//

#ifndef KAKAKV_ABSTRACTHANDLER_H
#define KAKAKV_ABSTRACTHANDLER_H

#include <memory>
#include <net/Message.h>
namespace kakakv {
    namespace net {

        class Channel;

        class AbstractHandler {
        public:
            virtual ~AbstractHandler() = 0;
        protected:
            virtual void channelRead(std::weak_ptr<const Channel> channel,std::shared_ptr<Message> message);
            virtual void channelWrite(std::weak_ptr<const Channel> channel,std::shared_ptr<Message> message);
            virtual void channelActive(std::weak_ptr<const Channel> channel);
        };
    }
}


#endif //KAKAKV_ABSTRACTHANDLER_H
