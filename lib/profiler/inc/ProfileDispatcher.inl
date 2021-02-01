//
// Created by rogan2 on 11/11/2020.
//

#ifndef HEADERTECH_PROFILEDISPATCHER_INL
#define HEADERTECH_PROFILEDISPATCHER_INL

#include <ProfileDispatcher.h>

#include <utility>

namespace HeaderTech::Profiler {
    ProfileDispatcher::ProfileDispatcher() : m_mutex(), m_condition(), m_nextId(0), m_currentId(-1), m_message()
    {}

    inline void ProfileDispatcher::WaitForEvent(httplib::DataSink *sink)
    {
        std::unique_lock<std::mutex> lock(m_mutex);
        int id = m_nextId;
        if (m_condition.wait_for(lock, std::chrono::milliseconds(500), [&] { return m_currentId == id; })) {
            if (sink->is_writable()) {
                sink->write(m_message.data(), m_message.size());
            }
        }
    }

    void ProfileDispatcher::ProcessCpuProfiles(const Types::CpuProfileMap &profiles) noexcept
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        m_currentId = m_nextId++;
        std::stringstream ss;
        ss << "id: " << m_currentId << "\n";
        ss << "event: " << "cpu_profile" << "\n";
        ss << "retry: " << 0 << "\n";
        ss << "data: ";
        ss << nlohmann::json(profiles).dump();
        ss << "\n\n";
        m_message = ss.str();
        m_condition.notify_all();
    }
}

#endif //HEADERTECH_PROFILEDISPATCHER_INL
