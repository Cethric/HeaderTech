//
// Created by rogan2 on 11/11/2020.
//

#ifndef HEADERTECH_TYPES_H
#define HEADERTECH_TYPES_H

#include <string>

namespace HeaderTech::Profiler {
    struct Message {
        std::string name;
        std::string data;
        std::uint64_t time;
        std::uint64_t thread;
        std::uint16_t level;
    };
}

#endif //HEADERTECH_TYPES_H
