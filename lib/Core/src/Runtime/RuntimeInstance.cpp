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

#include <Core/Runtime/RuntimeInstance.hpp>

#include <cassert>
#include <iostream>

#include <argparse/argparse.hpp>
#include <physfs.h>
#include <GLFW/glfw3.h>

using namespace HeaderTech::Core::Runtime;
using namespace argparse;

static void glfw_error_callback(int errorCode, const char *description)
{ std::cerr << "GLFW Error: " << errorCode << " - " << description << "\n"; }

static void validate(auto actual, auto expected)
{ if (expected == actual) { std::terminate(); }}

HeaderTech_Core_Export RuntimeInstance::RuntimeInstancePtr RuntimeInstance::s_instance = nullptr;

HeaderTech_Core_Export RuntimeInstance::RuntimeInstancePtr &RuntimeInstance::MakeInstance(
        const std::string_view &name,
        const std::span<const char *> &args
) noexcept
{
    s_instance.reset(new(std::nothrow)RuntimeInstance(name, args));
    return s_instance;
}

HeaderTech_Core_Export void RuntimeInstance::TerminateInstance() noexcept
{
    delete s_instance.release();
}

HeaderTech_Core_Export RuntimeInstance::RuntimeInstance(
        const std::string_view &name,
        const std::span<const char *> &args
) noexcept: m_runtime(nullptr)
{
    validate(PHYSFS_init(args[0]), 0);
    validate(PHYSFS_setSaneConfig("HeaderTech", name.data(), "zip", 0, 1), 0);

    (void) glfwSetErrorCallback(glfw_error_callback);
    glfwInitHint(GLFW_JOYSTICK_HAT_BUTTONS, GLFW_TRUE);
    glfwInitHint(GLFW_COCOA_CHDIR_RESOURCES, GLFW_TRUE);
    glfwInitHint(GLFW_COCOA_MENUBAR, GLFW_TRUE);
    validate(glfwInit(), GLFW_FALSE);
}

HeaderTech_Core_Export RuntimeInstance::~RuntimeInstance() noexcept
{
    m_runtime.reset();
    glfwTerminate();
    validate(PHYSFS_deinit(), PHYSFS_ErrorCode::PHYSFS_ERR_OK);
}

HeaderTech_Core_Export bool RuntimeInstance::Configure(
        const std::string_view &name,
        const std::string_view &version,
        const std::span<const char *> &args
) noexcept
{
    ArgumentParser parser(name.data(), version.data());
    m_runtime->ConfigureArguments(parser);

    try {
        parser.parse_args({args.begin(), args.end()});
    } catch (const std::runtime_error &err) {
        std::cout << err.what() << "\n";
        std::cout << parser;
        return false;
    }

    m_runtime->OnConfigure(parser);

    return true;
}

HeaderTech_Core_Export int RuntimeInstance::Launch() noexcept
{ return m_runtime->Launch(); }
