//
// Created by 凌宇 on 2021/9/20.
//

#ifndef KAKAKV_GENERALLOGENTRY_H
#define KAKAKV_GENERALLOGENTRY_H

#include <iostream>
#include <utility>
#include <log/LogEntry.h>
namespace kakakv {
    namespace log {
        class GeneralLogEntry : public LogEntry {
            friend std::ostream &operator<<(std::ostream &cout, GeneralLogEntry &entry);

        public:
            GeneralLogEntry(unsigned int index, unsigned int term, char *payload, unsigned long long payloadSize)
                    : LogEntry(index, term), payload(payload), payloadSize(payloadSize) {
            }

            std::pair<char *, unsigned long long> getPayload() {
                return std::make_pair(this->payload, this->payloadSize);
            }

        protected:
            /**
             * 日志的有效负载
             */
            char *payload;
            /**
             * 日志有效负载的长度
             */
            unsigned long long payloadSize;
        };

        std::ostream &operator<<(std::ostream &cout, GeneralLogEntry &entry);
    }
}

#endif //KAKAKV_GENERALLOGENTRY_H
