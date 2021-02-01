//
// Created by rogan2 on 22/12/2020.
//

#ifndef HEADERTECH_OPENGLDEBUGGUI_INL
#define HEADERTECH_OPENGLDEBUGGUI_INL

#include "OpenGLRenderContextApi.inl"

#include <imgui_internal.h>
#include <imgui_impl_glfw.h>
#include <ImGui_OpenGL3.h>

namespace HeaderTech::Render::Api::OpenGL {
    void OpenGLRenderContextApi::PrepareRenderDebugGUI() noexcept
    {
        ImGui::SetCurrentContext(m_debugGuiContext);

        ImGuiIO &io = ImGui::GetIO();
        (void) io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
        //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
        io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows
        //io.ConfigViewportsNoAutoMerge = true;
        //io.ConfigViewportsNoTaskBarIcon = true;

        // Setup Dear ImGui style
        ImGui::StyleColorsDark();
        //ImGui::StyleColorsClassic();

        // When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
        ImGuiStyle &style = ImGui::GetStyle();
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
            style.WindowRounding = 0.0f;
            style.Colors[ImGuiCol_WindowBg].w = 1.0f;
        }

        ImGui_ImplGlfw_InitForOpenGL(m_window->GetOwnedWindow(), false);
        ImGui_ImplOpenGL3_Init(&m_gl, "#version 410 core");
    }

    void OpenGLRenderContextApi::DestroyRenderDebugGUI() noexcept
    {
        ImGui_ImplOpenGL3_Shutdown(&m_gl);
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyPlatformWindows();
        ImGui::DestroyContext(m_debugGuiContext);
    }

    void OpenGLRenderContextApi::WillRenderDebugGUI() noexcept
    {
        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame(&m_gl);
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        static bool show_demo_window = true;
        static bool show_another_window = true;

        if (show_demo_window) {
            ImGui::ShowDemoWindow(&show_demo_window);
        }

        // 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
        {
            static float f = 0.0f;
            static int counter = 0;

            ImGui::Begin(
                    "Hello, world!");                          // Create a window called "Hello, world!" and append into it.

            ImGui::Text(
                    "This is some useful text.");               // Display some text (you can use a format strings too)
            ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
            ImGui::Checkbox("Another Window", &show_another_window);

            ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
//            ImGui::ColorEdit3("clear color", (float *) &clear_color); // Edit 3 floats representing a color

            if (ImGui::Button(
                    "Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
                counter++;
            ImGui::SameLine();
            ImGui::Text("counter = %d", counter);

            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate,
                        ImGui::GetIO().Framerate);
            ImGui::End();
        }

        // 3. Show another simple window.
        if (show_another_window) {
            ImGui::Begin("Another Window",
                         &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
            ImGui::Text("Hello from another window!");
            if (ImGui::Button("Close Me"))
                show_another_window = false;
            ImGui::End();
        }
    }

    void OpenGLRenderContextApi::DidRenderDebugGUI() noexcept
    {
        ImGuiIO &io = ImGui::GetIO();
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(m_window->GetOwnedWindow(), &display_w, &display_h);
        m_gl.Viewport(0, 0, display_w, display_h);
        m_gl.ClearColor(0, 0, 0, 1);
        m_gl.Clear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(&m_gl, ImGui::GetDrawData());

        // Update and Render additional Platform Windows
        // (Platform functions may change the current OpenGL context, so we save/restore it to make it easier to paste this code elsewhere.
        //  For this specific demo app we could also call glfwMakeContextCurrent(window) directly)
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
            GLFWwindow *backup_current_context = glfwGetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault(&m_gl, &m_gl);
            glfwMakeContextCurrent(backup_current_context);
        }

    }
}

#endif //HEADERTECH_OPENGLDEBUGGUI_INL
