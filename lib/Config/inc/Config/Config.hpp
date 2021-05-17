//
// Created by Blake Rogan on 21/04/2021.
//

#ifndef HEADERTECH_CONFIG_HPP
#define HEADERTECH_CONFIG_HPP

#include <Config/Exports.h>

#include <string_view>
#include <string>
#include <vector>
#include <memory>

namespace HeaderTech::Config {
    struct LoggingConfig {
        std::string logName;
        std::size_t maxLogFiles;
        std::size_t maxLogSize;
    };

    class Config : public std::enable_shared_from_this<Config> {
    public:
        HeaderTech_Config_Export Config(
                const std::string_view &name,
                const std::string_view &version,
                int argc,
                const char **argv
        ) noexcept;

        [[nodiscard]] HeaderTech_Config_Export const std::vector<std::string> &SearchPaths() const noexcept;

        [[nodiscard]] HeaderTech_Config_Export const LoggingConfig &LogConfig() const noexcept;

    private:
        std::vector<std::string> m_searchPaths;
        LoggingConfig            m_logConfig;
    };

    using ConfigPtr = std::shared_ptr<Config>;
    using ConfigWeakPtr = std::weak_ptr<Config>;
}


#endif //HEADERTECH_CONFIG_HPP
