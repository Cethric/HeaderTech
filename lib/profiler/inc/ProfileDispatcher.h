//
// Created by rogan2 on 11/11/2020.
//

#ifndef HEADERTECH_PROFILEDISPATCHER_H
#define HEADERTECH_PROFILEDISPATCHER_H

#include <httplib.h>
#include <atomic>
#include <mutex>
#include <condition_variable>
#include <ProfilerTypes.h>

namespace HeaderTech::Profiler {
    class ProfileDispatcher {
    public:
        ProfileDispatcher();

        ~ProfileDispatcher() = default;

        void WaitForEvent(httplib::DataSink *sink);

        inline void ProcessCpuProfiles(const Types::CpuProfileMap &profiles) noexcept;

    private:
        std::mutex m_mutex;
        std::condition_variable m_condition;

        std::atomic_int m_nextId;
        std::atomic_int m_currentId;
        std::string m_message;
    };
}
#endif //HEADERTECH_PROFILEDISPATCHER_H
