//
// Created by rogan2 on 11/11/2020.
//

#ifndef HEADERTECH_LOGDISPATCHER_H
#define HEADERTECH_LOGDISPATCHER_H

#include <httplib.h>
#include <atomic>
#include <mutex>
#include <condition_variable>
#include <Types.h>

namespace HeaderTech::Profiler {
    class LogDispatcher {
    public:
        LogDispatcher();

        ~LogDispatcher();

        void WaitForEvent(httplib::DataSink *sink);

        void PushMessage(const Message &message);

    private:
        std::mutex m_mutex;
        std::condition_variable m_condition;

        std::atomic_int m_nextId;
        std::atomic_int m_currentId;
        std::string m_message;

    };
}

#endif //HEADERTECH_LOGDISPATCHER_H
