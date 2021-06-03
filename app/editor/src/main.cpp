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

#include <Config/Config.hpp>
#include <Config/Version.hpp>
#include <Editor/Version.hpp>
#include <Event/Reactive/Reactive.hpp>
#include <Event/Version.hpp>
#include <FileSystem/FileSystem.hpp>
#include <FileSystem/Version.hpp>
#include <Logging/Logging.hpp>
#include <Logging/Version.hpp>
#include <Runtime/Runtime.hpp>
#include <Runtime/Version.hpp>

#include <string>
#include <cassert>
#include <iostream>

#include <spdlog/spdlog-inl.h>

class Application final : public HeaderTech::Runtime::Runtime {
public:
    Application(int argc, const char **argv) noexcept
            : HeaderTech::Runtime::Runtime(
            "Editor",
            HeaderTech::Editor::VersionString,
            argc,
            argv
    ),
              m_log(Logging()->CreateLogger<Application>())
    {
    }

protected:
    void VersionCheck() noexcept final
    {
        HeaderTech::Runtime::Runtime::VersionCheck();
        m_log->info("\tEditor {}", HeaderTech::Editor::VersionString);
        m_log->info("\tEvent {}", HeaderTech::Event::VersionString);
    }

    void OnMainLoopWillStart() noexcept final
    {
        m_log->info("OnMainLoopWillStart!");
        HeaderTech::Runtime::Runtime::OnMainLoopWillStart();
    }

    void OnMainLoopDidStart() noexcept final
    {
        m_log->info("OnMainLoopDidStart!");
        HeaderTech::Runtime::Runtime::OnMainLoopDidStart();
    }

    void OnMainLoopWillEnd() noexcept final
    {
        m_log->info("OnMainLoopWillEnd!");
        HeaderTech::Runtime::Runtime::OnMainLoopWillEnd();
    }

    void OnMainLoopDidEnd() noexcept final
    {
        m_log->info("OnMainLoopDidEnd!");
        HeaderTech::Runtime::Runtime::OnMainLoopDidEnd();
    }

    void OnMainLoopTick() noexcept final
    {
        m_log->info("OnMainLoopTick!");
        HeaderTech::Runtime::Runtime::OnMainLoopTick();

        StopRunning();
    }

private:
    HeaderTech::Logging::Logger m_log;
};

class ReactiveClass {
public:
    ReactiveClass() : m_exampleValue{false},
                      m_exampleValue2{10},
                      m_exampleValue3{"Hello"}
    {
        m_exampleValue2.Subscribe(
                [](HeaderTech::Event::Reactive::ReactiveOperation op, int oldValue, int newValue) {
                    std::cout << "Ex2 Changed: (" << op << ") " << oldValue << " -> " << newValue << std::endl;
                }
        );
        m_exampleValue3.Subscribe(
                [](
                        HeaderTech::Event::Reactive::ReactiveOperation op,
                        const std::string &oldValue,
                        const std::string &newValue
                ) {
                    std::cout << "Ex3 Changed: (" << op << ") " << oldValue << " -> " << newValue << std::endl;
                }
        );

        m_exampleValue = true;

        if (m_exampleValue) {
            m_exampleValue = false;
        }

        if (m_exampleValue2 > 8) {
            m_exampleValue2++;
            m_exampleValue2--;
            ++m_exampleValue2;
            --m_exampleValue2;
        }
        std::cout << m_exampleValue2 << std::endl;

        std::cout
                << ((m_exampleValue || m_exampleValue2) > 0 && m_exampleValue2 <= 100 && m_exampleValue2 < 200)
                << std::endl;

        m_exampleValue2 = 30;

        m_exampleValue2 += 10;
        m_exampleValue2 -= 10;
        m_exampleValue2 *= 10;
        m_exampleValue2 /= 10;

        m_exampleValue3 = "Hello, World!";

        std::string m_exampleValue4 = m_exampleValue3.substr(0, 5);

        std::cout << m_exampleValue << std::endl;
        std::cout << m_exampleValue2 << std::endl;
        std::cout << m_exampleValue3 << std::endl;
        std::cout << m_exampleValue4 << std::endl;

        std::cout << (20 + m_exampleValue2) << std::endl;
        std::cout << (m_exampleValue2 + 18) << std::endl;
        std::cout << (m_exampleValue2 + m_exampleValue2) << std::endl;
    }

private:
    HeaderTech::Event::Reactive::Reactive<bool>        m_exampleValue;
    HeaderTech::Event::Reactive::Reactive<int>         m_exampleValue2;
    HeaderTech::Event::Reactive::Reactive<std::string> m_exampleValue3;
};

int main(int argc, const char **argv)
{
    assert(HeaderTech::Editor::ValidateVersion(HeaderTech::Editor::HeaderVersion));
    assert(HeaderTech::Config::ValidateVersion(HeaderTech::Config::HeaderVersion));
    assert(HeaderTech::FileSystem::ValidateVersion(HeaderTech::FileSystem::HeaderVersion));
    assert(HeaderTech::Logging::ValidateVersion(HeaderTech::Logging::HeaderVersion));
    assert(HeaderTech::Runtime::ValidateVersion(HeaderTech::Runtime::HeaderVersion));
    assert(HeaderTech::Event::ValidateVersion(HeaderTech::Event::HeaderVersion));

    ReactiveClass example;

    Application application(argc, argv);

    return application.MainLoop();
}
