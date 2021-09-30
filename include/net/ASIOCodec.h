//
// Created by 凌宇 on 2021/9/29.
//

#ifndef KAKAKV_ASIOCODEC_H
#define KAKAKV_ASIOCODEC_H
#include <net/core/Encoder.h>
#include <net/core/Decoder.h>
namespace kakakv {
    namespace net {
        class ASIOCodec:public Encoder,public Decoder{
            /**
             * @description 将消息封装成字节流
             * @param message 待封装的消息
             * @param outputBuffer 输出缓冲区
             */
            void
            encapsulateMessageToByteStream(const ::google::protobuf::Message &message,std::shared_ptr<common::net::Buffer> outputBuffer) const override;
            /**
             * 尝试从输入缓冲区中提取消息
             * @param inputBuffer 输入缓冲区
             * @param message 指向消息的指针
             * @return true表示成功提取到一条消息;false表示缓冲区中不存在一条完整的消息，即未提取到
             */
            bool
            tryToretriveMessage(std::shared_ptr<common::net::Buffer>inputBuffer,std::shared_ptr<::google::protobuf::Message> message) const;
        };
    }
}
#endif //KAKAKV_ASIOCODEC_H
