//
// Created by rogan2 on 10/12/2020.
//

#ifndef HEADERTECH_RENDEROBJECT_H
#define HEADERTECH_RENDEROBJECT_H

#include <RenderContext.h>

namespace HeaderTech::Render {
    class RenderObject {
    public:
        explicit RenderObject(RenderContext *ctx) : m_ctx(ctx)
        {}

        virtual ~RenderObject() = default;

    protected:
        virtual void OnSetup() = 0;

        virtual void OnTeardown() = 0;

    protected:
        RenderContext *m_ctx;
    };
}

#endif //HEADERTECH_RENDEROBJECT_H
