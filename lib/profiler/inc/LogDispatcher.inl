//
// Created by rogan2 on 11/11/2020.
//

#ifndef HEADERTECH_LOGDISPATCHER_INL
#define HEADERTECH_LOGDISPATCHER_INL

#include <LogDispatcher.h>

namespace HeaderTech::Profiler {
    LogDispatcher::LogDispatcher() : m_nextId(0), m_currentId(-1), m_message(), m_mutex(), m_condition()
    {

    }

    LogDispatcher::~LogDispatcher()
    {

    }

    void LogDispatcher::WaitForEvent(httplib::DataSink *sink)
    {
        std::unique_lock<std::mutex> lock(m_mutex);
        int id = m_nextId;
        if (m_condition.wait_for(lock, std::chrono::milliseconds(5), [&] { return m_currentId == id; })) {
            if (sink->is_writable()) {
                sink->write(m_message.data(), m_message.size());
            }
        }
    }

    void LogDispatcher::PushMessage(const Message &message)
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        m_currentId = m_nextId++;
        std::stringstream ss;
        ss << "id: " << m_currentId << "\n";
        ss << "event: " << "message" << "\n";
        ss << "retry: " << 10 << "\n";
        ss << "data: {";
        ss << R"("name": ")" << message.name << R"(",)";
        ss << R"("data": ")" << message.data << R"(",)";
        ss << R"("time": )" << message.time << R"(,)";
        ss << R"("thread": )" << message.thread << R"(,)";
        ss << R"("level": )" << message.level;
        ss << "}\n\n";
        m_message = ss.str();
        m_condition.notify_all();
    }
}

#endif //HEADERTECH_LOGDISPATCHER_INL
