//
// Created by rogan2 on 24/11/2020.
//

#ifndef HEADERTECH_IMGUISURFACE_H
#define HEADERTECH_IMGUISURFACE_H

#include <imgui.h>

namespace HeaderTech::UI {
    struct ImGuiComponent {

    };

    class ImGuiSurface {
    public:
        inline ImGuiSurface(ImFontAtlas *font_atlas) noexcept
                : m_context(ImGui::CreateContext(font_atlas))
        {
            ImGui::SetCurrentContext(m_context);
            ImGuiIO& io = ImGui::GetIO();
            io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
            io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
            io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
            ImGui::StyleColorsDark();

        }

        inline ~ImGuiSurface() noexcept
        { ImGui::DestroyContext(m_context); }

    private:
        ImGuiContext *m_context;
    };
}

#endif //HEADERTECH_IMGUISURFACE_H
