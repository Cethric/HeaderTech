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

#ifndef HEADERTECH_APPLICATION_HPP
#define HEADERTECH_APPLICATION_HPP

#include <span>
#include <memory>
#include <concepts>
#include <type_traits>
#include <string_view>

#include <Logging/Logging.hpp>
#include <FileSystem/FileSystem.hpp>
#include <Config/Config.hpp>
#include <Event/EventProcessor.hpp>
#include <Common/Clock.hpp>
#include <Runtime/Exports.h>

namespace HeaderTech::Runtime {
    class HeaderTech_Runtime_Export Application
            : private std::enable_shared_from_this<Application>,
              public HeaderTech::Event::EventProcessor {
    public:
        Application(
                const std::string_view &name,
                const std::string_view &version,
                const std::span<const char *> &args,
                const HeaderTech::Common::ClockPtr &clock
        ) noexcept;

        ~Application() noexcept override;

        int Launch() noexcept;

        void Terminate() noexcept;

        [[nodiscard]] inline auto MainLoop() const noexcept
        { return this->SharedEventProcessor(); }

    protected:
        HeaderTech::Config::ConfigPtr         m_config;
        HeaderTech::FileSystem::FileSystemPtr m_fileSystem;
        HeaderTech::Logging::LoggingPtr       m_logging;
        HeaderTech::Logging::LogPtr           m_log;

    private:
        bool m_isRunning;
    };

    namespace Instance {
        template<class ApplicationType>
        concept DerivedApplication = std::is_base_of<Application, ApplicationType>::value;

        template<DerivedApplication ApplicationBase>
        class ApplicationInstance {
            using Application = ApplicationBase;
            using ApplicationPtr = std::shared_ptr<ApplicationBase>;

        public:
            inline explicit ApplicationInstance(
                    const std::span<const char *> &args,
                    const HeaderTech::Common::ClockPtr &clock
            ) :
                    m_application(std::make_shared<Application>(args, clock))
            {}

            inline auto Instance() const noexcept -> ApplicationPtr &
            { return m_application; }

            inline auto Launch() noexcept -> int
            { return m_application->Launch(); }

        private:
            ApplicationPtr m_application;
        };

        template<DerivedApplication ApplicationBase>
        inline static auto MakeInstance(
                const std::span<const char *> &args,
                const HeaderTech::Common::ClockPtr &clock
        ) noexcept -> ApplicationInstance<ApplicationBase>
        { return ApplicationInstance<ApplicationBase>(args, clock); }
    }
}


#endif //HEADERTECH_APPLICATION_HPP
