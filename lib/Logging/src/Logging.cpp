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

#include "Logging/Logging.hpp"

#include <spdlog/spdlog.h>
#include <spdlog/cfg/env.h>

#include <spdlog/sinks/stdout_color_sinks.h>

#ifndef __EMSCRIPTEN__

#include <spdlog/async.h>

#endif// !defined(EMSCRIPTEN)

#include <Logging/RotatingSink.hpp>
#include <Logging/RotatingSink.inl>

#include <utility>
#include <string>
#include <memory>


static inline std::shared_ptr<spdlog::sinks::dup_filter_sink_mt> CreateSinks(
        const HeaderTech::Config::ConfigPtr &config,
        const HeaderTech::FileSystem::FileSystemPtr &fileSystem
)
{
    auto dup_sink = std::make_shared<spdlog::sinks::dup_filter_sink_mt>(std::chrono::seconds(5));
    dup_sink->add_sink(std::make_shared<spdlog::sinks::stdout_color_sink_mt>());
    dup_sink->add_sink(std::make_shared<HeaderTech::Logging::RotatingSinkMT>(config, fileSystem));

    return dup_sink;
}

HeaderTech_Logging_Export HeaderTech::Logging::Logging::Logging(
        const HeaderTech::Config::ConfigPtr &config,
        const HeaderTech::FileSystem::FileSystemPtr &fileSystem
) noexcept: std::enable_shared_from_this<Logging>(),
            m_sink(CreateSinks(config, fileSystem))
{
    spdlog::cfg::load_env_levels();
#ifndef __EMSCRIPTEN__
    spdlog::init_thread_pool(8192, 16);
#endif// __EMSCRIPTEN__
    spdlog::set_default_logger(CreateLogger("console"));
    spdlog::info("Logging Initialised");
}

HeaderTech_Logging_Export HeaderTech::Logging::Logging::~Logging() noexcept
{
    spdlog::shutdown();
}

HeaderTech_Logging_Export HeaderTech::Logging::Logger HeaderTech::Logging::Logging::CreateLogger(
        const std::string_view &name
) noexcept
{
#ifdef __EMSCRIPTEN__
    auto logger = std::make_shared<spdlog::logger>(std::string(name.data()), m_sink);
#else
    auto pool   = spdlog::thread_pool();
    auto logger = std::make_shared<spdlog::async_logger>(
            std::string(name.data()),
            m_sink,
            std::move(pool),
            spdlog::async_overflow_policy::block
    );
#endif// __EMSCRIPTEN__
    spdlog::initialize_logger(logger);
    return logger;
}

HeaderTech_Logging_Export HeaderTech::Logging::Logger HeaderTech::Logging::Logging::GetOrCreateLogger(
        const std::string_view &name
) noexcept
{
    if (auto logger = spdlog::get(name.data())) {
        return logger;
    }
    return CreateLogger(name);
}
