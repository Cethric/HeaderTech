/*==============================================================================
 = BSD 3-Clause License
 =
 = Copyright (c) 2021, Cethric
 = All rights reserved.
 =
 = Redistribution and use in source and binary forms, with or without
 = modification, are permitted provided that the following conditions are met:
 =
 = 1. Redistributions of source code must retain the above copyright notice, this
 =    list of conditions and the following disclaimer.
 =
 = 2. Redistributions in binary form must reproduce the above copyright notice,
 =    this list of conditions and the following disclaimer in the documentation
 =    and/or other materials provided with the distribution.
 =
 = 3. Neither the name of the copyright holder nor the names of its
 =    contributors may be used to endorse or promote products derived from
 =    this software without specific prior written permission.
 =
 = THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 = AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 = IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 = DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 = FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 = DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 = SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 = CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 = OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 = OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 =============================================================================*/

#include "Config/Config.hpp"

#include <Config/Version.hpp>

#include <fstream>
#include <string>

#include <argparse/argparse.hpp>
#include <nlohmann/json.hpp>

namespace nlohmann {
template<>
struct adl_serializer<HeaderTech::Config::LoggingConfig> final {
    inline static void to_json(json &j, const HeaderTech::Config::LoggingConfig &cfg) noexcept
    {
        j = json{
            { "name", cfg.logName },
            { "count", cfg.maxLogFiles },
            { "size", cfg.maxLogSize }
        };
    }

    inline static void from_json(const json &j, HeaderTech::Config::LoggingConfig &cfg) noexcept
    {
        j.at("name").get_to(cfg.logName);
        j.at("count").get_to(cfg.maxLogFiles);
        j.at("size").get_to(cfg.maxLogSize);
    }
};
}// namespace nlohmann

HeaderTech_Config_Export HeaderTech::Config::Config::Config(
    const std::string_view &name,
    const std::string_view &version,
    int argc,
    const char **argv) noexcept
    : std::enable_shared_from_this<Config>(),
      m_searchPaths(),
      m_logConfig{
    .logName     = "logs/output.log",
    .maxLogFiles = 4,
    .maxLogSize  = 8192
}
{
    argparse::ArgumentParser parser(name.data(), version.data());
    parser.add_description("");
    parser.add_epilog("");

    parser.add_argument("--config")
    .nargs(1)
    .help("An optional configuration file")
    .action(
    [](const std::string &config_file) noexcept {
        std::ifstream file(config_file);
        nlohmann::json config_json;
        if (file) {
            file >> config_json;
        }
        return config_json;
    });

    parser.add_argument("--search-path")
    .help("Add additional filesystem search paths")
    .default_value<std::vector<std::string>>({});

    parser.add_argument("--log-name")
    .help("The log file to output to")
    .default_value<std::string>("logs/output.log");

    parser.add_argument("--log-size")
    .help("The maximum size of a log file before rotating")
    .default_value<std::size_t>(8192)
    .action([](const std::string &value) {
        return std::stoll(value);
    });

    parser.add_argument("--log-count")
    .help("The log file to output to")
    .default_value<std::size_t>(4)
    .action([](const std::string &value) {
        return std::stoll(value);
    });

    try {
        parser.parse_args(argc, argv);
    } catch (const std::runtime_error &err) {
        std::cout << err.what() << std::endl;
        std::cout << parser << std::endl;
        std::exit(0);
    }

    auto paths = parser.get<std::vector<std::string>>("--search-path");
    m_searchPaths.swap(paths);

    m_logConfig.logName     = parser.get<std::string>("--log-name");
    m_logConfig.maxLogSize  = parser.get<std::size_t>("--log-size");
    m_logConfig.maxLogFiles = parser.get<std::size_t>("--log-count");

    if (auto config = parser.present<nlohmann::json>("--config")) {
        m_searchPaths = config->front().value<std::vector<std::string>>("searchPaths", m_searchPaths);
        m_logConfig   = config->front().value<HeaderTech::Config::LoggingConfig>("logging", m_logConfig);
    }
}

HeaderTech_Config_Export const std::vector<std::string> &HeaderTech::Config::Config::SearchPaths() const noexcept
{
    return m_searchPaths;
}

HeaderTech_Config_Export const HeaderTech::Config::LoggingConfig &HeaderTech::Config::Config::LogConfig() const noexcept
{
    return m_logConfig;
}
