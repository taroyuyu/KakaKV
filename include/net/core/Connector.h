//
// Created by 凌宇 on 2021/9/20.
//

#ifndef KAKAKV_CONNECTOR_H
#define KAKAKV_CONNECTOR_H
#include <memory>
namespace kakakv{
    namespace net{
        class Connector {
        public:
            Connector() = default;
            virtual ~Connector() = 0;
            /**
             * 初始化
             */
            virtual void initialize()throw(char*) = 0;
            /**
             * 重置连接
             */
            virtual void resetChannels() = 0;
            /**
             * 关闭通信组件
             */
            virtual void close() = 0;
        };
    }
}


#endif //KAKAKV_CONNECTOR_H
