//
// Created by rogan2 on 20/11/2020.
//

#ifndef HEADERTECH_BASERENDERCONTEXTAPI_H
#define HEADERTECH_BASERENDERCONTEXTAPI_H

#include <api/BaseWindowApi.h>

namespace HeaderTech::Render::Api {
    class RenderContextApi {
    public:
        inline explicit RenderContextApi(HeaderTech::Window::Api::WindowApi *api) noexcept: m_api(api)
        {}

        inline virtual ~RenderContextApi() noexcept = default;

        inline void MakeCurrent() noexcept
        { m_api->MakeCurrent(); }

    protected:
        HeaderTech::Window::Api::WindowApi *m_api;
    };
}

#endif //HEADERTECH_BASERENDERCONTEXTAPI_H
