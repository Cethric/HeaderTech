//
// Created by Blake Rogan on 20/04/2021.
//

#include <Editor/Version.hpp>
#include <FileSystem/Version.hpp>
#include <FileSystem/FileSystem.hpp>
#include <Config/Version.hpp>
#include <Config/Config.hpp>
#include <Logging/Version.hpp>
#include <Logging/Logging.hpp>
#include <Runtime/Runtime.hpp>
#include <Runtime/Version.hpp>
#include <Event/Version.hpp>
#include <Event/Reactive/Reactive.hpp>

#include <cassert>
#include <iostream>

class Application final : public HeaderTech::Runtime::Runtime {
public:
    Application(int argc, const char **argv) noexcept:
            HeaderTech::Runtime::Runtime(
                    "Editor",
                    HeaderTech::Editor::VersionString,
                    argc,
                    argv
            ), m_log(Logging()->CreateLogger<Application>())
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

using namespace HeaderTech::Event::Reactive;

class ReactiveClass {
public:
    ReactiveClass() : m_exampleValue{false},
                      m_exampleValue2{10},
                      m_exampleValue3{"Hello"}
    {
        m_exampleValue2.Subscribe(
                [](ReactiveOperation op, int oldValue, int newValue) {
                    std::cout << "Ex2 Changed: (" << op << ") " << oldValue << " -> " << newValue << std::endl;
                }
        );
        m_exampleValue3.Subscribe(
                [](ReactiveOperation op, const std::string &oldValue, const std::string &newValue) {
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
                << (m_exampleValue || m_exampleValue2 > 0 && m_exampleValue2 <= 100 && m_exampleValue2 < 200)
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
    Reactive<bool>        m_exampleValue;
    Reactive<int>         m_exampleValue2;
    Reactive<std::string> m_exampleValue3;
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