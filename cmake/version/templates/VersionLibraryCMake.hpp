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

#ifndef HEADERTECH_@NAME@_VERSION_H
#define HEADERTECH_@NAME@_VERSION_H

#include <@NAME@/Exports.h>
#include <cstdint>

namespace HeaderTech::@NAME@ {
    struct Version {
        std::uint32_t major;
        std::uint32_t minor;
        std::uint32_t patch;
        std::uint32_t build;
        char          tweak[32];
        char          config[32];
        std::uint64_t timestamp;
    };

    HeaderTech_@NAME@_Export const Version &CompileVersion();

    HeaderTech_@NAME@_Export bool ValidateVersion(const Version &headerVersion);

    static const Version HeaderVersion{
            .major = @MAJOR@,
            .minor = @MINOR@,
            .patch = @PATCH@,
            .build = @BUILD_NUMBER@,
            .tweak = "@TWEAK@",
            .config = "@CONFIG@",
            .timestamp = @BUILD_TIMESTAMP@,
    };

    static const char* VersionString = "@MAJOR@.@MINOR@.@PATCH@@TWEAK@-build_@BUILD_NUMBER@";
}

#endif //HEADERTECH_@NAME@_VERSION_H
