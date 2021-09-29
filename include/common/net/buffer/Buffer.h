//
// Created by taroyuyu on 2018/2/24.
//

#ifndef KAKAKV_BUFFER_H
#define KAKAKV_BUFFER_H

#include <cstdio>

namespace kakakv {
    namespace common {
        namespace net {
            class Buffer {
            public:
                virtual ~Buffer() = 0;
                /**
                 * 向Buffer中追加数据
                 * @param buffer
                 * @param bufferLength
                 */
                virtual void append(const void *buffer, const size_t bufferLength) = 0;
                /**
                 * 向Buffer中接收数据
                 * @param buffer
                 * @param bufferCapacity
                 * @return
                 */
                virtual size_t retrive(const void *buffer, const size_t bufferCapacity) = 0;

                /**
                 * 查看缓冲区最前面的内容,但不会删除
                 * @param buffer
                 * @param bufferLength
                 * @return
                 */
                virtual size_t head(const void *buffer, const size_t bufferLength) = 0;

                virtual size_t getUsed() = 0;
            };
        }
    }
}
#endif //KAKAKV_BUFFER_H
