//
// Created by taroyuyu on 2018/1/3.
//

#ifndef KAKAKV_CIRCLEBUFFER_H
#define KAKAKV_CIRCLEBUFFER_H

#include <common/net/buffer/Buffer.h>
#include <mutex>

namespace kakakv {
    namespace common {
        namespace net {
            class CircleBuffer:public Buffer{
            public:
                CircleBuffer(size_t initialCapacity);

                ~CircleBuffer();

                void append(const void *buffer, const size_t bufferLength)override;

                size_t retrive(const void *buffer, const size_t bufferCapacity)override;

                /**
                 * 查看缓冲区最前面的内容,但不会删除
                 * @param buffer
                 * @param bufferLength
                 * @return
                 */
                size_t head(const void *buffer, const size_t bufferLength)override;

                size_t getUsed()override;

                bool check()override;

            private:
                struct Node {
                    Node() : next(nullptr), previous(nullptr) {

                    }

                    struct Node *next;
                    struct Node *previous;
#define NodeContentSize 2
                    u_int8_t content[NodeContentSize];
                };

                struct Cursor {
                    struct Node *node;
                    size_t offset;
                } mReadCursor, mWriteCursor;
                size_t mCapacity;
                size_t mUsed;
                std::mutex bufferMutex;

                bool checkCircle();

            };

        }
    }
}
#endif //KAKAKV_CIRCLEBUFFER_H

