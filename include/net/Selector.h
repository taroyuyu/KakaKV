//
// Created by 凌宇 on 2021/9/27.
//

#ifndef KAKAKV_SELECTOR_H
#define KAKAKV_SELECTOR_H

#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <memory>
#include <set>
namespace kakakv {
    namespace net {

        class ASIOChannel;

        class Selector{
        public:
            class Listener{
            public:
                virtual ~Listener() = 0;
                virtual void onReceiveConnect(std::shared_ptr<ASIOChannel> channel) = 0;
            };
            Selector(boost::asio::ip::tcp::endpoint listenEndpoint);
            void addListener(std::weak_ptr<Listener> listener);
            void removeListener(std::weak_ptr<Listener> listener);
            void start();
            void shutdownGracefully();
        private:
            void waitForAccept();
            std::atomic<bool> mStart;
            const boost::asio::ip::tcp::endpoint endpoint;
            std::shared_ptr<boost::asio::io_service> mIOService;
            std::shared_ptr<boost::thread_group> mIOThreadGroup;
            std::unique_ptr<boost::asio::ip::tcp::acceptor> mAcceptor;

            std::set<std::weak_ptr<Listener>,std::owner_less<std::weak_ptr<Listener>>> mListenerSet;
        };
    }
}


#endif //KAKAKV_SELECTOR_H
