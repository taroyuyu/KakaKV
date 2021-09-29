//
// Created by 凌宇 on 2021/9/29.
//

#ifndef KAKAKV_ASIODECODER_H
#define KAKAKV_ASIODECODER_H

#include <net/core/Decoder.h>
#include <google/protobuf/message.h>
namespace kakakv {
    namespace net {
        class ASIODecoder:public Decoder{
            /**
             * 尝试从输入缓冲区中提取消息
             * @param inputBuffer 输入缓冲区
             * @param message 指向消息的指针
             * @return true表示成功提取到一条消息;false表示缓冲区中不存在一条完整的消息，即未提取到
             */
            bool
            tryToretriveMessage(::google::protobuf::Message **message) const;
        };
    }
}

#endif //KAKAKV_ASIODECODER_H
