//
// Created by 凌宇 on 2021/9/21.
//

#ifndef KAKAKV_ENDPOINT_H
#define KAKAKV_ENDPOINT_H
#include <string>
namespace kakakv{
    namespace net{
        class Endpoint {
        public:
            Endpoint(std::string host,unsigned int port):host(host),port(port){
            }
            std::string host;
            unsigned int port;
        };
    }
}


#endif //KAKAKV_ENDPOINT_H
