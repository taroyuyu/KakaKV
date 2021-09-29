//
// Created by 凌宇 on 2021/9/29.
//

#ifndef KAKAKV_ASIOENCODER_H
#define KAKAKV_ASIOENCODER_H

#include <net/core/Encoder.h>
#include <google/protobuf/message.h>

namespace kakakv {
    namespace net {
        class ASIOEncoder : public Encoder {
        public:
            /**
             * @description 将消息封装成字节流
             * @param message 待封装的消息
             * @param outputBuffer 输出缓冲区
             */
            void
            encapsulateMessageToByteStream(const ::google::protobuf::Message &message) const;
        };
    }
}


#endif //KAKAKV_ASIOENCODER_H
