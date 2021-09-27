//
// Created by 凌宇 on 2021/9/26.
//

#ifndef KAKAKV_ASIOCONNECTOR_H
#define KAKAKV_ASIOCONNECTOR_H

#include <net/Connector.h>
#include <string>
#include <boost/asio.hpp>
namespace kakakv{
    namespace net{
        class ASIOConnector:public net::Connector{
        public:
            ASIOConnector(std::string listenIP = "0.0.0.0",unsigned short listenPort = 6000);
            void initialize()throw(char*)override;
        private:
            const std::string ip;
            const unsigned short port;
        };
    }
}


#endif //KAKAKV_ASIOCONNECTOR_H
