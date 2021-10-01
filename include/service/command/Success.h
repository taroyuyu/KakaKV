//
// Created by 凌宇 on 2021/9/30.
//

#ifndef KAKAKV_SUCCESS_H
#define KAKAKV_SUCCESS_H
#include <service/command/Response.h>
namespace kakakv {
    namespace service {
        namespace command {
            class Success:public Response{
            public:
                Success(){
                }
            };

        }
    }
}


#endif //KAKAKV_SUCCESS_H
