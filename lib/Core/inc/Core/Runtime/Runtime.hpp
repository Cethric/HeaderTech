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

#ifndef HEADERTECH_RUNTIME_HPP
#define HEADERTECH_RUNTIME_HPP

#include <span>
#include <memory>
#include <concepts>
#include <type_traits>
#include <string_view>

#include <Core/Exports.h>
#include <Core/Event/EventDispatcher.hpp>

#include <argparse/argparse.hpp>

namespace HeaderTech::Core::Runtime {
    class RuntimeInstance;

    class HeaderTech_Core_Export Runtime : public HeaderTech::Core::Event::EventDispatcher {
    public:
        Runtime();

        virtual ~Runtime();

        [[nodiscard]] inline bool IsRunning() const noexcept
        { return m_running; }

        inline void Shutdown() noexcept
        { m_running = false; }

    protected:
        virtual void ConfigureArguments(argparse::ArgumentParser &parser) noexcept = 0;

        virtual void OnConfigure(argparse::ArgumentParser &parser) noexcept = 0;

        virtual void OnLaunch() noexcept = 0;

        virtual void OnShutdown() noexcept = 0;

        virtual void OnTick() noexcept = 0;

    private:
        int Launch() noexcept;

    private:
        bool m_running;

    private:
        friend class RuntimeInstance;
    };

    using RuntimePtr = std::shared_ptr<Runtime>;

    template<class RuntimeDerived>
    concept RuntimeBase = requires(RuntimeDerived app) {
        std::is_base_of_v<Runtime, RuntimeDerived>;
    };

}


#endif //HEADERTECH_RUNTIME_HPP
