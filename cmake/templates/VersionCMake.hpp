//
// Created by rogan2 on 3/04/2021.
//

#ifndef HEADERTECH_@NAME@_VERSION_H
#define HEADERTECH_@NAME@_VERSION_H

#include <cstdint>
#include <@NAME@/Exports.h>

namespace HeaderTech {
    namespace @NAME@ {
        struct @NAME@Version {
            std::uint32_t major;
            std::uint32_t minor;
            std::uint32_t patch;
            std::uint32_t build;
            char          tweak[32];
            char          config[32];
            std::uint64_t timestamp;
        };

        HeaderTech_@NAME@_Export const @NAME@Version &CompileVersion();

        HeaderTech_@NAME@_Export bool ValidateVersion(const @NAME@Version &headerVersion);

        static const @NAME@Version HeaderVersion{
                .major = @MAJOR@,
                .minor = @MINOR@,
                .patch = @PATCH@,
                .build = @BUILD_NUMBER@,
                .tweak = "@TWEAK@",
                .config = "@CONFIG@",
                .timestamp = @BUILD_TIMESTAMP@,
        };
    }
}


#endif //HEADERTECH_@NAME@_VERSION_H
