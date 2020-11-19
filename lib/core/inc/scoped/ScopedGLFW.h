//
// Created by rogan2 on 12/11/2020.
//

#ifndef HEADERTECH_SCOPEDGLFW_H
#define HEADERTECH_SCOPEDGLFW_H

#include <exception>
#include <GLFW/glfw3.h>
#include <Logging.h>

namespace HeaderTech::Core::Scoped {
    static inline void glfw_error_callback(int code, const char *description)
    {
        auto log = HeaderTech::Logging::get_or_make_logger_async("GLFW");
        log->error("({}) {}", code, description);
    }


    class ScopedGlfw final {
    public:
        inline ScopedGlfw() : m_log(HeaderTech::Logging::make_logger_async<ScopedGlfw>())
        {
            glfwSetErrorCallback(&glfw_error_callback);
            if (glfwInit() == GLFW_FALSE) {
                m_log->error("GLFW Failed to Initialised");
                throw std::exception("Failed to Initialise GLFW");
            }
            m_log->info("GLFW Initialised");
        }

        inline ~ScopedGlfw() noexcept
        {
            glfwTerminate();

            m_log->info("GLFW Terminated");
        }

    private:
        HeaderTech::Logging::Logger m_log;
    };
}

#endif //HEADERTECH_SCOPEDGLFW_H
