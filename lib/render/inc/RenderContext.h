//
// Created by rogan2 on 19/11/2020.
//

#ifndef HEADERTECH_RENDERCONTEXT_H
#define HEADERTECH_RENDERCONTEXT_H

#include <api/RenderContextApi.h>

namespace HeaderTech::Render {

    class RenderContext {
    public:
        inline RenderContext(HeaderTech::Render::Api::RenderContextApi *api) : m_api(api)
        {}

        inline ~RenderContext()
        { delete m_api; }

        inline void MakeCurrent()
        { m_api->MakeCurrent(); }

    private:
        HeaderTech::Render::Api::RenderContextApi *m_api;
    };

}

#endif //HEADERTECH_RENDERCONTEXT_H
