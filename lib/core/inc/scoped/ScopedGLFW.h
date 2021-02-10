//
// Created by rogan2 on 12/11/2020.
//

#ifndef HEADERTECH_SCOPEDGLFW_H
#define HEADERTECH_SCOPEDGLFW_H

#define GLFW_INCLUDE_NONE 1

#include <exception>
#include <GLFW/glfw3.h>
#include <LoggingIncludes.h>

namespace HeaderTech::Core::Scoped {
    static inline void glfw_error_callback(int code, const char *description)
    {
        auto log = HeaderTech::Logging::get_or_make_logger_async("GLFW");
        SPDLOG_LOGGER_ERROR(log, "({}) {}", code, description);
    }


    class ScopedGlfw final {
    public:
        inline ScopedGlfw() : m_log(HeaderTech::Logging::make_logger_async<ScopedGlfw>())
        {
            glfwSetErrorCallback(&glfw_error_callback);
            if (glfwInit() == GLFW_FALSE) {
                SPDLOG_LOGGER_ERROR(m_log, "GLFW Failed to Initialised");
                throw std::exception("Failed to Initialise GLFW");
            }
            SPDLOG_LOGGER_INFO(m_log, "GLFW Initialised");
        }

        inline ~ScopedGlfw() noexcept
        {
            glfwTerminate();
            SPDLOG_LOGGER_INFO(m_log, "GLFW Terminated");
        }

    private:
        HeaderTech::Logging::Logger m_log;
    };
}

#endif //HEADERTECH_SCOPEDGLFW_H
