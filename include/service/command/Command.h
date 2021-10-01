//
// Created by 凌宇 on 2021/10/1.
//

#ifndef KAKAKV_COMMAND_H
#define KAKAKV_COMMAND_H

#include <string>

namespace kakakv {
    namespace service {
        namespace command {
            class Command {
            public:
                virtual ~Command() = 0;
                virtual std::string toBytes()const = 0;
            };
        }
    }
}


#endif //KAKAKV_COMMAND_H
