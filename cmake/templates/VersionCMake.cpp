//
// Created by rogan2 on 3/04/2021.
//

#include "@NAME@/Version.hpp"

#include <cstring>

namespace HeaderTech {
    namespace @NAME@ {
        const static @NAME@Version CompiledVersion{
            .major = @MAJOR@,
            .minor = @MINOR@,
            .patch = @PATCH@,
            .build = @BUILD_NUMBER@,
            .tweak = "@TWEAK@",
            .config = "@CONFIG@",
            .timestamp = @BUILD_TIMESTAMP@,
        };

        const @NAME@Version &CompileVersion()
        { return CompiledVersion; }

        bool ValidateVersion(const @NAME@Version &headerVersion)
        {
            return headerVersion.major == CompiledVersion.major &&
                   headerVersion.minor == CompiledVersion.minor &&
                   headerVersion.patch == CompiledVersion.patch &&
                   headerVersion.build == CompiledVersion.build &&
                   headerVersion.timestamp == CompiledVersion.timestamp &&
                   std::strcmp(headerVersion.tweak, CompiledVersion.tweak) == 0 &&
                   std::strcmp(headerVersion.config, CompiledVersion.config) == 0;
        }
    }
}