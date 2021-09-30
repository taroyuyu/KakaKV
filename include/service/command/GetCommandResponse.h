//
// Created by 凌宇 on 2021/9/30.
//

#ifndef KAKAKV_GETCOMMANDRESPONSE_H
#define KAKAKV_GETCOMMANDRESPONSE_H
#include <string>
namespace kakakv {
    namespace service {
        namespace command {
            class GetCommandResponse {
            public:
                GetCommandResponse(bool found,std::string value):found(found),value(value){
                }
                bool isFound()const{
                    return this->found;
                }
                std::string getValue()const{
                    return this->value;
                }
            private:
                const bool found;
                const std::string value;
            };
        }
    }
}


#endif //KAKAKV_GETCOMMANDRESPONSE_H
