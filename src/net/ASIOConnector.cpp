//
// Created by 凌宇 on 2021/9/26.
//

#include <net/ASIOConnector.h>
#include <boost/asio.hpp>
namespace kakakv {
    namespace net {
        ASIOConnector::ASIOConnector(std::string listenIP,unsigned short listenPort):
        ip(listenIP),port(listenPort){
        }

        void ASIOConnector::initialize()throw(char*){
            // 1. 创建端口
            if (!(1 <= this->port <= 65535))
                throw "Invalid Port";
            boost::system::error_code ec;
            boost::asio::ip::address ip_address = boost::asio::ip::address_v4::any();
            if (this->ip != "0.0.0.0"){
                ip_address = boost::asio::ip::address::from_string(this->ip,ec);
                if (ec.value() != 0) {
                    throw "Invalid IP Address:"+ec.message();
                }
            }
            boost::asio::ip::tcp::endpoint endpoint(ip_address, this->port);
            // 2. 创建asio::io_service
            boost::asio::io_service ioService;
            // 3. 创建acceptor
            auto protocol = boost::asio::ip::tcp::v4();
            boost::asio::ip::tcp::acceptor acceptor(ioService);
            // 4. 打开acceptor
            acceptor.open(protocol, ec);
            if (ec.value() != 0) {
                throw "open socket failed:"+ec.message();
            }
            // 5. 将端口绑定到acceptor
            acceptor.bind(endpoint, ec);
            if (ec.value() != 0) {
                throw "Failed to bind the acceptor socket,message:"+ec.message();
            }
            // 6. 开始侦听
            const int BACKLOG_SIZE = 30;
            acceptor.listen(BACKLOG_SIZE);
            // 7. 等待客户端链接
            boost::asio::ip::tcp::socket clientSocket(ioService);
            acceptor.accept(clientSocket);

            // 创建缓冲区
            std::unique_ptr<char[]> buf(new char[1024]);
            auto input_buf = boost::asio::buffer(static_cast<void*>(buf.get()), 1024);
        }
    }
}