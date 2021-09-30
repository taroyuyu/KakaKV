//
// Created by 凌宇 on 2021/9/28.
//

#ifndef KAKAKV_DECODER_H
#define KAKAKV_DECODER_H

#include <common/net/buffer/Buffer.h>
#include <google/protobuf/message.h>
#include <memory>

namespace kakakv {
    namespace net {
        class Decoder {
        public:
            virtual ~Decoder() = 0;

            /**
             * 尝试从输入缓冲区中提取消息
             * @param inputBuffer 输入缓冲区
             * @param message 指向消息的指针
             * @return true表示成功提取到一条消息;false表示缓冲区中不存在一条完整的消息，即未提取到
             */
            virtual bool
            tryToretriveMessage(std::shared_ptr<common::net::Buffer> inputBuffer,
                                std::shared_ptr<::google::protobuf::Message> & message) const = 0;
        };
    }
}

#endif //KAKAKV_DECODER_H
