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

//#include <Config/Config.hpp>
//#include <Config/Version.hpp>
//#include <Editor/Version.hpp>
//#include <Event/Reactive/Reactive.hpp>
//#include <Event/Version.hpp>
//#include <FileSystem/FileSystem.hpp>
//#include <FileSystem/Version.hpp>
//#include <Logging/Logging.hpp>
//#include <Logging/Version.hpp>
//#include <Runtime/Runtime.hpp>
//#include <Runtime/Application.hpp>
//#include <Runtime/Version.hpp>
//#include <Common/Version.hpp>
//
//#include <string>
//#include <cassert>
//#include <iostream>
//#include <span>
//
//struct TerminationEvent {
//};
//
//inline static bool capture_event(const TerminationEvent &evt)
//{
//    return false;
//}
//
//class MyApp final : public HeaderTech::Runtime::Application {
//public:
//    inline explicit MyApp(const HeaderTech::Runtime::RuntimeContextPtr &context) noexcept
//            : HeaderTech::Runtime::Application(context)
//    {
//        (void) Bind<TerminationEvent>(this, 0U);
//        //    Bind<TerminationEvent>(*this, 0);
//        (void) Bind<TerminationEvent>(capture_event, 0U);
//        (void) Bind<TerminationEvent>([](const TerminationEvent &evt) { return false; }, 0U);
//
//        (void) Dispatch<TerminationEvent, 0>();
//        m_log->Critical(SOURCE_LOCATION, "Critical");
//        m_log->Exception(SOURCE_LOCATION, "Exception");
//        m_log->Error(SOURCE_LOCATION, "Error");
//        m_log->Warning(SOURCE_LOCATION, "Warning");
//        m_log->Information(SOURCE_LOCATION, "Information");
//        m_log->Debug(SOURCE_LOCATION, "Debug");
//        m_log->Trace(SOURCE_LOCATION, "Trace");
//        m_log->Verbose(SOURCE_LOCATION, "Verbose");
//    }
//
//    bool OnEvent(const TerminationEvent &evt) noexcept
//    {
//        m_log->Information(SOURCE_LOCATION, "Shutdown called");
//        Terminate();
//        return false;
//    }
//};
//
//using Instance = HeaderTech::Runtime::Instance::ApplicationInstance<MyApp>;
//
//int main(int argc, const char **argv)
//{
//    assert(HeaderTech::Editor::ValidateVersion(HeaderTech::Editor::HeaderVersion));
//    assert(HeaderTech::Common::ValidateVersion(HeaderTech::Common::HeaderVersion));
//    assert(HeaderTech::Config::ValidateVersion(HeaderTech::Config::HeaderVersion));
//    assert(HeaderTech::FileSystem::ValidateVersion(HeaderTech::FileSystem::HeaderVersion));
//    assert(HeaderTech::Logging::ValidateVersion(HeaderTech::Logging::HeaderVersion));
//    assert(HeaderTech::Runtime::ValidateVersion(HeaderTech::Runtime::HeaderVersion));
//    assert(HeaderTech::Event::ValidateVersion(HeaderTech::Event::HeaderVersion));
//
//    std::span<const char *> args(argv, argc);
//
//    auto context = HeaderTech::Runtime::RuntimeContext::MakeRuntimeContext(
//            "Editor",
//            HeaderTech::Editor::VersionString,
//            args
//    );
//
//    auto instance = HeaderTech::Runtime::Instance::make_instance<MyApp>(context);
//
//    return instance.Launch();
//}

#define HEADERTECH_EVENT_IMPLEMENTATION 1

#include <Editor/Version.hpp>
#include <Core/HeaderTech.hpp>
#include <Core/Events/Window/WindowPositionEvent.hpp>
#include <Core/Events/Input/KeyInputEvent.hpp>

#include <iostream>

#include <GLFW/glfw3.h>

struct ExampleEvent {

};

using WindowPositionEvent = HeaderTech::Core::Events::Window::WindowPositionEvent;
using KeyInputEvent = HeaderTech::Core::Events::Input::KeyInputEvent;

class Application final : public HeaderTech::Core::Runtime::Runtime {
public:
    explicit Application()
            : HeaderTech::Core::Runtime::Runtime(),
              m_window(nullptr)
    {
        Bind<ExampleEvent, 0>(
                [](const ExampleEvent &evt) {
                    std::cout << "Handle Example Event From Lambda\n";
                    return true;
                }
        );
        Bind<ExampleEvent, 0>(this);
        m_window.Bind<KeyInputEvent, 0>(this);
        Bind<ExampleEvent, 0>(*this);

        Dispatch<ExampleEvent, 0>();

        m_window.Bind<WindowPositionEvent, 0>(
                [](const WindowPositionEvent &evt) {
                    std::cout << "Handle WindowPositionEvent Event From Lambda " << evt.x << ", " << evt.y << "\n";
                    return true;
                }
        );
    }

    ~Application() noexcept override
    {
        std::cout << "application destroyed\n";
    }

    bool OnEvent(const ExampleEvent &evt)
    {
        std::cout << "Handle Example Event From Class\n";
        return true;
    }

    bool OnEvent(const ExampleEvent &evt) const
    {
        std::cout << "Handle Example Event From Class Const\n";
        return true;
    }

    bool OnEvent(const KeyInputEvent &evt) const
    {
        std::cout
                << "Handle Key Input ("
                << evt.key
                << ","
                << evt.scanCode
                << ","
                << evt.mods
                << ","
                << evt.action
                << ")\n";
        return true;
    }

protected:
    void ConfigureArguments(argparse::ArgumentParser &parser) noexcept override
    {
        (void) parser.add_argument("-e", "--example")
                     .help("an example argument")
                     .action(
                             [](const std::string &value) {
                                 return value;
                             }
                     );
    }

    void OnConfigure(argparse::ArgumentParser &parser) noexcept override
    {}

    void OnLaunch() noexcept override
    {}

    void OnShutdown() noexcept override
    {}

    void OnTick() noexcept override
    {
        m_window.Tick();
        if (!m_window.IsOpen()) { Shutdown(); }
    }

private:
    HeaderTech::Core::Common::Window m_window;
};

int main(int argc, const char **argv)
{
    std::span<const char *> args(argv, static_cast<std::span<const char *>::size_type>(argc));
    return HeaderTech::entry_point<Application>("Editor", HeaderTech::Editor::VersionString, args);
}
