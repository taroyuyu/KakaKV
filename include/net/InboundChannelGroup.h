//
// Created by 凌宇 on 2021/9/27.
//

#ifndef KAKAKV_INBOUNDCHANNELGROUP_H
#define KAKAKV_INBOUNDCHANNELGROUP_H

#include <net/ASIOChannel.h>
#include <cluster/NodeId.h>
#include <list>
#include <memory>
namespace kakakv {
    namespace net {
        class InboundChannelGroup {
        public:
            // 增加连接入口
            void add(cluster::NodeId remoteId,std::shared_ptr<ASIOChannel> channel);
            // 移除连接
            void remove(std::shared_ptr<ASIOChannel> channel);
            // 关闭所有连接
            void closeAll();
        private:
            std::list<std::shared_ptr<ASIOChannel>> channels;
        };
    }
}


#endif //KAKAKV_INBOUNDCHANNELGROUP_H
