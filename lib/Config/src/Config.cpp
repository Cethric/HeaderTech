//
// Created by Blake Rogan on 21/04/2021.
//

#include "Config/Config.hpp"

#include <Config/Version.hpp>

#include <fstream>

#include <argparse/argparse.hpp>
#include <nlohmann/json.hpp>

namespace nlohmann {
    template<>
    struct adl_serializer<HeaderTech::Config::LoggingConfig> final {
        inline static void to_json(json &j, const HeaderTech::Config::LoggingConfig &cfg) noexcept
        {
            j = json{
                    {"name",  cfg.logName},
                    {"count", cfg.maxLogFiles},
                    {"size",  cfg.maxLogSize}
            };
        }

        inline static void from_json(const json &j, HeaderTech::Config::LoggingConfig &cfg) noexcept
        {
            j.at("name").get_to(cfg.logName);
            j.at("count").get_to(cfg.maxLogFiles);
            j.at("size").get_to(cfg.maxLogSize);
        }
    };
}

HeaderTech_Config_Export HeaderTech::Config::Config::Config(
        const std::string_view &name,
        const std::string_view &version,
        int argc,
        const char **argv
) noexcept
        : std::enable_shared_from_this<Config>(),
          m_searchPaths(),
          m_logConfig{
                  .logName="logs/output.log",
                  .maxLogFiles=4,
                  .maxLogSize=8192
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
                      std::ifstream  file(config_file);
                      nlohmann::json config_json;
                      if (file) {
                          file >> config_json;
                      }
                      return config_json;
                  }
          );

    parser.add_argument("--search-path")
          .append()
          .help("Add additional filesystem search paths")
          .default_value<std::vector<std::string>>({});

    parser.add_argument("--log-name")
          .help("The log file to output to")
          .default_value<std::string>("logs/output.log");

    parser.add_argument("--log-size")
          .help("The maximum size of a log file before rotating")
          .default_value<std::size_t>(8192)
          .action([](const std::string &value) { return std::stoll(value); });

    parser.add_argument("--log-count")
          .help("The log file to output to")
          .default_value<std::size_t>(4)
          .action([](const std::string &value) { return std::stoll(value); });

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
{ return m_searchPaths; }

HeaderTech_Config_Export const HeaderTech::Config::LoggingConfig &HeaderTech::Config::Config::LogConfig() const noexcept
{ return m_logConfig; }
