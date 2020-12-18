//
// Created by rogan2 on 13/11/2020.
//

#ifndef HEADERTECH_FILEDROPEVENT_H
#define HEADERTECH_FILEDROPEVENT_H

#include <Event.h>
#include <utility>
#include <vector>
#include <string>

namespace HeaderTech::Window::Events {
    using FileDropVector = std::vector<std::string>;

    struct FileDropEvent {
        explicit inline FileDropEvent(FileDropVector files) noexcept: files(std::move(files))
        {}

        [[nodiscard]] inline HeaderTech::Events::EventPriority
        GetPriority() const noexcept // NOLINT(readability-convert-member-functions-to-static)
        { return HeaderTech::Events::MAX_EVENT_PRIORITY; }

        FileDropVector files;
    };
}

#endif //HEADERTECH_FILEDROPEVENT_H
