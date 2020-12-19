//
// Created by rogan2 on 19/12/2020.
//

#ifndef HEADERTECH_PROFILERTYPES_H
#define HEADERTECH_PROFILERTYPES_H

#include <phmap.h>
#include <nlohmann/json.hpp>

#include <queue>
#include <string>

namespace HeaderTech::Profiler::Types {
    namespace detail {
        using CpuProfileHash = std::uint64_t;

        struct CpuProfileHashing {
            [[nodiscard]] inline size_t _hash(const std::uint64_t &val) const noexcept
            { return val; }

            inline size_t operator()(const std::uint64_t &val) const noexcept
            { return _hash(val); }
        };

        struct CpuProfileEqualTo {
            inline bool operator()(const std::uint64_t &lhs, const std::uint64_t &rhs) const
            { return lhs == rhs; }
        };
    }

    enum ScopedProfilerFlags : std::uint8_t {
        ScopedProfilerFlags_None,
        ScopedProfilerFlags_Aggregate,
        ScopedProfilerFlags_Recursive
    };

    NLOHMANN_JSON_SERIALIZE_ENUM(ScopedProfilerFlags, {
        { ScopedProfilerFlags_None, "none" },
        { ScopedProfilerFlags_Aggregate, "aggregate" },
        { ScopedProfilerFlags_Recursive, "recursive" },
    })

    using CpuProfileHash = detail::CpuProfileHash;
    using CpuProfileChildrenList = phmap::flat_hash_set<
            CpuProfileHash,
            detail::CpuProfileHashing,
            detail::CpuProfileEqualTo
    >;

    struct CpuProfile {
        std::string name;
        std::string function;
        int line;
        std::string file;
        ScopedProfilerFlags flags;

        std::uint32_t call_count;
        std::uint32_t recursion_count;
        std::uint32_t max_recursion_count;
        double start;
        double end;
        double delta;
        double total_delta;

        CpuProfileHash parent;
        CpuProfileChildrenList children;


        NLOHMANN_DEFINE_TYPE_INTRUSIVE(
                CpuProfile,
                name,
                function,
                line,
                file,
                flags,
                call_count,
                max_recursion_count,
                start,
                end,
                delta,
                total_delta,
                parent,
                children
        )
    };

    using CpuProfileMap = phmap::parallel_flat_hash_map<
            CpuProfileHash,
            CpuProfile,
            detail::CpuProfileHashing,
            detail::CpuProfileEqualTo
    >;
    using CpuProfileHashQueue = std::deque<CpuProfileHash>;
}

#endif //HEADERTECH_PROFILERTYPES_H
