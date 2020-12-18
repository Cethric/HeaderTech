//
// Created by rogan2 on 29/10/2020.
//

#ifndef HEADERTECH_LOGGER_H
#define HEADERTECH_LOGGER_H

#include <memory>
#include <string>

#include <spdlog/spdlog.h>

namespace HeaderTech::Logging {
    using Logger = std::shared_ptr<spdlog::logger>;

    static inline void create_sinks() noexcept;

    static inline void clear_sinks() noexcept;

    [[nodiscard]] inline Logger make_logger_async(const std::string &name);

    [[nodiscard]] inline Logger get_or_make_logger_async(const std::string &name);

    template<typename Name>
    [[nodiscard]] inline Logger make_logger_async();

    template<typename Name>
    [[nodiscard]] inline Logger get_or_make_logger_async();

    [[nodiscard]] inline Logger make_logger(const std::string &name);

    [[nodiscard]] inline Logger get_or_make_logger(const std::string &name);

    template<typename Name>
    [[nodiscard]] inline Logger make_logger();

    template<typename Name>
    [[nodiscard]] inline Logger get_or_make_logger();
}

#endif //HEADERTECH_LOGGER_H
