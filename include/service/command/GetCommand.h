//
// Created by 凌宇 on 2021/9/30.
//

#ifndef KAKAKV_GETCOMMAND_H
#define KAKAKV_GETCOMMAND_H
#include <string>
#include <service/command/Command.h>
namespace kakakv{
    namespace service{
        namespace command{
            class GetCommand:public Command{
            public:
                GetCommand(std::string key):key(key){
                }
                std::string getKey()const{
                    return this->key;
                }
                std::string toBytes()const override;
            private:
                std::string key;
            };
        }
    }
}


#endif //KAKAKV_GETCOMMAND_H
