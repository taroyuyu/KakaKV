//
// Created by 凌宇 on 2021/9/27.
//

#ifndef KAKAKV_CHANNEL_H
#define KAKAKV_CHANNEL_H

#include <net/core/AbstractHandler.h>
#include <net/core/Decoder.h>
#include <net/core/Encoder.h>
#include <functional>
#include <list>
namespace kakakv {
    namespace net {
        class Channel{
        public:
            Channel(std::shared_ptr<Decoder> decoder,std::shared_ptr<Encoder> encoder);
            virtual ~Channel() = 0;
            virtual void addHandler(std::shared_ptr<AbstractHandler> handler) = 0;
            virtual void removeHandler(std::shared_ptr<AbstractHandler> handler) = 0;
            virtual void writeMessage(std::shared_ptr<const Message> message) = 0;
            bool isOpen()const;
            // 关闭
            virtual void close() = 0;
            // 添加Close回掉函数
            virtual void addCloseCallback(std::function<void(std::shared_ptr<Channel> channel)> callback) = 0;
        protected:
            std::shared_ptr<Decoder> mDecoder;
            std::shared_ptr<Encoder> mEncoder;
            mutable bool openStatus;
            std::list<std::function<void(std::shared_ptr<Channel> channel)>> closeCallbackList;
        };
    }
}


#endif //KAKAKV_CHANNEL_H
