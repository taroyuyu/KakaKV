//
// Created by 凌宇 on 2021/9/30.
//

#ifndef KAKAKV_GETCOMMAND_H
#define KAKAKV_GETCOMMAND_H
#include <string>
namespace kakakv{
    namespace service{
        namespace command{
            class GetCommand {
            public:
                GetCommand(std::string key):key(key){
                }
                std::string getKey(){
                    return this->key;
                }
            private:
                std::string key;
            };
        }
    }
}


#endif //KAKAKV_GETCOMMAND_H