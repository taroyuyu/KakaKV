//
// Created by 凌宇 on 2021/9/27.
//

#include <net/Channel.h>

namespace kakakv {
    namespace net {
        Channel::Channel(std::shared_ptr<Decoder> decoder,std::shared_ptr<Encoder> encoder):
        mDecoder(decoder),mEncoder(encoder),openStatus(false){
        }
        Channel::~Channel() {
        }

        bool Channel::isOpen()const{
            return this->openStatus;
        }
    }
}