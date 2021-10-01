//
// Created by 凌宇 on 2021/9/30.
//

#ifndef KAKAKV_SETCOMMAND_H
#define KAKAKV_SETCOMMAND_H

#include <string>
#include <service/command/Command.h>
namespace kakakv {
    namespace service {
        namespace command {
            class SetCommand:public Command{
            public:
                SetCommand(std::string requestId,std::string key,std::string value):requestId(requestId),key(key),value(value){

                }
                std::string getRequestId()const{
                    return this->requestId;
                }
                std::string getKey()const{
                    return this->key;
                }
                std::string getValue()const{
                    return this->value;
                }
                std::string toBytes()const override;
            private:
                const std::string requestId;
                const std::string key;
                const std::string value;
            };
        }
    }
}


#endif //KAKAKV_SETCOMMAND_H
