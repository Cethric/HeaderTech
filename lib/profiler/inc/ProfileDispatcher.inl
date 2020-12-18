//
// Created by rogan2 on 11/11/2020.
//

#ifndef HEADERTECH_PROFILEDISPATCHER_INL
#define HEADERTECH_PROFILEDISPATCHER_INL

#include <ProfileDispatcher.h>

#include <utility>

namespace HeaderTech::Profiler {
    namespace details {
        inline ProfileTimingMark::ProfileTimingMark(std::string name) noexcept
                : m_name(std::move(name)),
                  m_delta(0),
                  m_children()
        {}

        inline void ProfileTimingMark::RegisterChild(ProfileTimingMark *mark) noexcept
        { m_children.push_back(mark); }

        inline void ProfileTimingMark::Finish(double delta) noexcept
        { m_delta = delta; }

        inline std::string ProfileTimingMark::Write() const noexcept
        {
            std::stringstream ss;
            ss << "{";
            ss << R"("name": ")" << m_name << R"(",)";
            ss << R"("delta": )" << m_delta << R"(,)";
            ss << R"("children": [)";
            for (const auto &child : m_children) { ss << child->Write(); }
            ss << "]}";
            return ss.str();
        }

        bool ProfileTimingMark::operator==(const ProfileTimingMark &other) noexcept
        { return m_name == other.m_name; }
    }

    ProfileDispatcher::ProfileDispatcher() : m_nextId(0), m_currentId(-1), m_message(), m_mutex(), m_condition()
    {

    }

    ProfileDispatcher::~ProfileDispatcher()
    {

    }

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

    inline details::ProfileTimingMark *ProfileDispatcher::BeginProfileMark(const std::string &name)
    {
        auto next = new details::ProfileTimingMark(name);
        if (!m_timingMarks.empty()) {
            auto parent = m_timingMarks.front();
            parent->RegisterChild(next);
        }
        return m_timingMarks.emplace_front(next);
    }

    inline void ProfileDispatcher::EndProfileMark(const details::ProfileTimingMark &mark)
    {
        if (m_timingMarks.size() == 1) {
            std::lock_guard<std::mutex> lock(m_mutex);
            m_currentId = m_nextId++;
            std::stringstream ss;
            ss << "id: " << m_currentId << "\n";
            ss << "event: " << "message" << "\n";
            ss << "retry: " << 0 << "\n";
            ss << "data: ";
            ss << m_timingMarks.front()->Write();
            ss << "\n\n";
            m_message = ss.str();
            m_condition.notify_all();
        }
        delete m_timingMarks.front();
        m_timingMarks.pop_front();
    }
}

#endif //HEADERTECH_PROFILEDISPATCHER_INL
