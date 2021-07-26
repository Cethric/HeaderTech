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

#ifndef HEADERTECH_RUNTIMEINSTANCE_HPP
#define HEADERTECH_RUNTIMEINSTANCE_HPP

#include <span>
#include <memory>
#include <string_view>

#include <Core/Exports.h>
#include <Core/Runtime/Runtime.hpp>

namespace HeaderTech::Core::Runtime {
    class HeaderTech_Core_Export RuntimeInstance {
    public:
        using RuntimeInstancePtr = std::unique_ptr<RuntimeInstance>;
    private:
        static RuntimeInstancePtr s_instance;

    private:
        RuntimeInstance(
                const std::string_view &name,
                const std::span<const char *> &args
        ) noexcept;

    public:
        static RuntimeInstancePtr &MakeInstance(
                const std::string_view &name,
                const std::span<const char *> &args
        ) noexcept;

        static void TerminateInstance() noexcept;

        static inline const RuntimeInstancePtr &Instance() noexcept
        { return s_instance; }

    public:
        ~RuntimeInstance() noexcept;

        bool Configure(
                const std::string_view &name,
                const std::string_view &version,
                const std::span<const char *> &args
        ) noexcept;

        int Launch() noexcept;

        template<RuntimeBase Runtime>
        inline void RegisterRuntime() noexcept
        { m_runtime = std::make_shared<Runtime>(); }

        template<RuntimeBase RuntimeType>
        [[nodiscard]] inline std::shared_ptr<RuntimeType> Runtime() const noexcept
        { return std::static_pointer_cast<RuntimeType>(m_runtime); }

    private:
        RuntimePtr m_runtime;
    };
}


#endif //HEADERTECH_RUNTIMEINSTANCE_HPP
