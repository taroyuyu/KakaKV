//
// Created by 凌宇 on 2021/9/28.
//

#ifndef KAKAKV_ENCODER_H
#define KAKAKV_ENCODER_H

#include <common/net/buffer/Buffer.h>
#include <google/protobuf/message.h>
#include <memory>

namespace kakakv {
    namespace net {
        class Encoder {
        public:
            virtual ~Encoder() = 0;

            /**
             * @description 将消息封装成字节流
             * @param message 待封装的消息
             * @param outputBuffer 输出缓冲区
             */
            virtual void
            encapsulateMessageToByteStream(const ::google::protobuf::Message &message,
                                           std::shared_ptr<common::net::Buffer> outputBuffer) const = 0;
        };
    }
}


#endif //KAKAKV_ENCODER_H
