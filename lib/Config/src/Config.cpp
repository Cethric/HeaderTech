//
// Created by Blake Rogan on 21/04/2021.
//

#include "Config/Config.hpp"

#include <Config/Version.hpp>

#include <fstream>

#include <argparse/argparse.hpp>
#include <nlohmann/json.hpp>

HeaderTech_Config_Export HeaderTech::Config::Config::Config(
        const std::string_view &name,
        const std::string_view &version,
        int argc,
        const char **argv
) noexcept: m_searchPaths()
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

    try {
        parser.parse_args(argc, argv);
    } catch (const std::runtime_error &err) {
        std::cout << err.what() << std::endl;
        std::cout << parser << std::endl;
        std::exit(0);
    }

    auto paths = parser.get<std::vector<std::string>>("--search-path");
    m_searchPaths.swap(paths);

    if (auto config = parser.present<nlohmann::json>("--config")) {
        std::cout << "Config: " << config->front().value<std::string>("name", "NULL") << std::endl;
    }
}

HeaderTech_Config_Export const std::vector<std::string> &HeaderTech::Config::Config::SearchPaths() const noexcept
{ return m_searchPaths; }
