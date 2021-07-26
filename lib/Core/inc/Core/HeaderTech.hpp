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

#ifndef HEADERTECH_HEADERTECH_HPP
#define HEADERTECH_HEADERTECH_HPP

#include <span>
#include <string_view>

#include <Core/Exports.h>

#include <Core/Event.hpp>

#include <Core/Runtime/Runtime.hpp>
#include <Core/Runtime/RuntimeInstance.hpp>

#include <Core/Common/Window.hpp>

namespace HeaderTech {
    namespace Impl {
        struct DestructOnDereference {
            inline explicit DestructOnDereference(auto &&instancePtr) noexcept
            : ptr(std::forward<decltype(instancePtr)>(instancePtr))
            {}

            DestructOnDereference(const auto &instancePtr) = delete;
            DestructOnDereference(const auto &&instancePtr) = delete;

            inline ~DestructOnDereference() noexcept
            { ptr->TerminateInstance(); }

        private:
            HeaderTech::Core::Runtime::RuntimeInstance::RuntimeInstancePtr &ptr;
        };
    }

    template<HeaderTech::Core::Runtime::RuntimeBase Runtime>
    static inline int entry_point(
            const std::string_view &name,
            const std::string_view &version,
            const std::span<const char *> &args
    )
    {
        auto                  &instance = HeaderTech::Core::Runtime::RuntimeInstance::MakeInstance(name, args);
        Impl::DestructOnDereference destructOnDereference(instance);
        instance->RegisterRuntime<Runtime>();
        if (instance->Configure(name, version, args)) {
            return instance->Launch();
        }
        return 0;
    }
}

#endif //HEADERTECH_HEADERTECH_HPP
