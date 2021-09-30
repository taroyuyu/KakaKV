//
// Created by 凌宇 on 2021/9/30.
//

#ifndef KAKAKV_FAILURE_H
#define KAKAKV_FAILURE_H

#include <string>

namespace kakakv {
    namespace service {
        namespace command {
            class Failure {
            public:
                Failure(int errorCode,std::string message):errorCode(errorCode),message(message){
                }
                int getErrorCode()const{
                    return this->errorCode;
                }
                std::string getMessage()const{
                    return this->message;
                }
            private:
                const int errorCode;
                const std::string message;
            };
        }
    }
}


#endif //KAKAKV_FAILURE_H
