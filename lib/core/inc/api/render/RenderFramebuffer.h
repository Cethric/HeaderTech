//
// Created by rogan2 on 22/12/2020.
//

#ifndef HEADERTECH_RENDERFRAMEBUFFER_H
#define HEADERTECH_RENDERFRAMEBUFFER_H

namespace HeaderTech::Core::Api::Render {
    class RenderFramebuffer {
    public:
        inline RenderFramebuffer(int width, int height) noexcept;

        inline virtual ~RenderFramebuffer() noexcept;

        inline void Resize(int width, int height);

        inline void Build();

        inline void Destroy() noexcept;

        inline virtual void Lock() noexcept;

        inline virtual void Unlock() noexcept;

    protected:
        inline virtual void OnBuild() = 0;

        inline virtual void OnDestroy() noexcept = 0;

    private:
        inline void WillBuild();

        inline void WillDestroy() noexcept;

    protected:
        int m_width;
        int m_height;
        bool m_isBuilt;
        bool m_isLocked;

    };
}

#endif //HEADERTECH_RENDERFRAMEBUFFER_H
