//
// Created by rogan2 on 10/12/2020.
//

#ifndef HEADERTECH_RENDERSURFACE_H
#define HEADERTECH_RENDERSURFACE_H

#include <RenderObject.h>

namespace HeaderTech::Render {
    class RenderSurface : public RenderObject {
    public:
        explicit RenderSurface(RenderContext *ctx) : RenderObject(ctx)
        {}

        void Render(double offset)
        {OnRender(offset);}

    protected:
        virtual void OnRender(double offset) = 0;
    };
}

#endif //HEADERTECH_RENDERSURFACE_H
