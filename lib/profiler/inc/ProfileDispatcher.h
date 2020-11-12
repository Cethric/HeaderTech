//
// Created by rogan2 on 11/11/2020.
//

#ifndef HEADERTECH_PROFILEDISPATCHER_H
#define HEADERTECH_PROFILEDISPATCHER_H

#include <httplib.h>
#include <atomic>
#include <mutex>
#include <condition_variable>

namespace HeaderTech::Profiler {
    class ProfileDispatcher {
    public:
        ProfileDispatcher();

        ~ProfileDispatcher();

        void WaitForEvent(httplib::DataSink *sink);

        void PushProfile(const std::string &name, double delta);

    private:
        std::mutex m_mutex;
        std::condition_variable m_condition;

        std::atomic_int m_nextId;
        std::atomic_int m_currentId;
        std::string m_message;
    };
}

#endif //HEADERTECH_PROFILEDISPATCHER_H
