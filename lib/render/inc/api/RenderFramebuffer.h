//
// Created by rogan2 on 22/12/2020.
//

#ifndef HEADERTECH_RENDERFRAMEBUFFER_H
#define HEADERTECH_RENDERFRAMEBUFFER_H

namespace HeaderTech::Render::Api {
    class RenderFramebuffer {
    public:
        inline RenderFramebuffer(int width, int height) noexcept;

        inline virtual ~RenderFramebuffer() noexcept;

        inline virtual void Resize(int width, int height);

        inline virtual void Build();

        inline virtual void Destroy() noexcept;

        inline virtual void Lock() noexcept;

        inline virtual void Unlock() noexcept;

    protected:
        int m_width;
        int m_height;
        bool m_isBuilt;
        bool m_isLocked;

    };
}

#endif //HEADERTECH_RENDERFRAMEBUFFER_H
