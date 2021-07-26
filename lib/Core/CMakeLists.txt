cmake_minimum_required(VERSION 3.19)
project(Core VERSION 0.0.1.0 DESCRIPTION "HeaderTech Core library" HOMEPAGE_URL "https://cehtric.github.io" LANGUAGES CXX C)

set(
        Core_SRC
        # Runtime
        src/Runtime/Runtime.cpp
        src/Runtime/RuntimeInstance.cpp

        # Event
        src/Event/EventDispatcher.cpp
        src/Event/EventQueue.cpp
        src/Event/EventHandler.cpp

        # Common
        src/Common/Window.cpp
)

set(
        Core_INC
        # Core
        inc/Core/HeaderTech.hpp

        # Runtime
        inc/Core/Runtime/Runtime.hpp
        inc/Core/Runtime/RuntimeInstance.hpp

        # Event
        inc/Core/Event.hpp
        inc/Core/Event/EventDispatcher.hpp
        inc/Core/Event/impl/EventDispatcher.inl
        inc/Core/Event/Event.hpp
        inc/Core/Event/impl/Event.inl
        inc/Core/Event/EventQueue.hpp
        inc/Core/Event/impl/EventQueue.inl
        inc/Core/Event/EventHandler.hpp
        inc/Core/Event/impl/EventHandler.inl
        inc/Core/Event/EventHandlerQueue.hpp
        inc/Core/Event/impl/EventHandlerQueue.inl

        # Common
        inc/Core/Common/Window.hpp

        # Events
        inc/Core/Events/Window/WindowPositionEvent.hpp
        inc/Core/Events/Window/WindowSizeEvent.hpp
        inc/Core/Events/Window/FramebufferSizeEvent.hpp
        inc/Core/Events/Window/WindowContentScaleEvent.hpp
        inc/Core/Events/Window/WindowIconifyEvent.hpp
        inc/Core/Events/Window/WindowMaximiseEvent.hpp
        inc/Core/Events/Window/WindowFocusEvent.hpp
        inc/Core/Events/Window/WindowRefreshEvent.hpp
        inc/Core/Events/Input/KeyInputEvent.hpp inc/Core/Events/Input/CharacterInputEvent.hpp inc/Core/Events/Input/MouseButtonEvent.hpp inc/Core/Events/Input/CursorPositionEvent.hpp inc/Core/Events/Input/CursorEnterEvent.hpp inc/Core/Events/Input/ScrollEvent.hpp inc/Core/Events/Input/FileDropEvent.hpp)

add_library(Core SHARED ${Core_SRC} ${Core_INC})
target_include_directories(
        Core
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/inc/>
        $<INSTALL_INTERFACE:include/>
)

#target_link_libraries(Core PRIVATE Common)
target_link_libraries(Core PUBLIC physfs::physfs json::json argparse::argparse glfw::glfw3 hashmap::hashmap ctti::ctti)

ConfigureLibrary(Core 0 0 1 "+dev")

target_precompile_headers(Core PUBLIC $<BUILD_INTERFACE:<Core/Version.hpp>> $<BUILD_INTERFACE:<Core/Exports.h>>)

if (BUILD_TESTING)
    add_subdirectory(test)
endif (BUILD_TESTING)
