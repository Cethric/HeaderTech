//
// Created by rogan2 on 11/11/2020.
//

#ifndef HEADERTECH_PROFILEDISPATCHER_H
#define HEADERTECH_PROFILEDISPATCHER_H

#include <httplib.h>
#include <atomic>
#include <mutex>
#include <condition_variable>
#include <deque>

namespace HeaderTech::Profiler {
    namespace details {
        class ProfileTimingMark {
        public:
            inline ProfileTimingMark(std::string name) noexcept;

            inline void RegisterChild(ProfileTimingMark *mark) noexcept;

            inline void Finish(double delta) noexcept;

            inline std::string Write() const noexcept;

            inline bool operator==(const ProfileTimingMark &other) noexcept;

        private:
            std::string m_name;
            double m_delta;
            std::vector<ProfileTimingMark *> m_children;
        };
    }

    class ProfileDispatcher {
    public:
        ProfileDispatcher();

        ~ProfileDispatcher();

        void WaitForEvent(httplib::DataSink *sink);

        inline details::ProfileTimingMark *BeginProfileMark(const std::string &name);

        inline void EndProfileMark(const details::ProfileTimingMark &mark);

    private:
        std::mutex m_mutex;
        std::condition_variable m_condition;

        std::atomic_int m_nextId;
        std::atomic_int m_currentId;
        std::string m_message;

        std::deque<details::ProfileTimingMark *> m_timingMarks;
    };
}

#endif //HEADERTECH_PROFILEDISPATCHER_H
