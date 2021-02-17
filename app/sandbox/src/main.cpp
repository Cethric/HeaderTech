#include <Sandbox.h>

#include <glm/glm.hpp>
#include <glm/ext.hpp>

struct RenderComponent final {
};

struct TransformComponent final {
    glm::vec3 position;
    glm::quat orientation;
    HeaderTech::Core::ReactiveProperty<glm::vec3> vector;

    explicit inline TransformComponent(const glm::vec3 &position, const glm::quat &orientation) noexcept
            : position(position),
              orientation(orientation),
              vector({0, 0, 0}) {
        vector.RegisterChangeListener([](auto from, auto to) {
            SPDLOG_INFO("Change Vector: {} {} {}", to.x, to.y, to.z);
        });
    }
};

struct DebugGuiComponent final {
    const char *name;

    explicit inline DebugGuiComponent(const char *name) noexcept: name(name) {}
};

struct CameraComponent final {
    HeaderTech::Core::ReactiveProperty<bool> m_enabled;
    HeaderTech::Core::ReactiveProperty<int> m_count;
    HeaderTech::Core::ReactiveProperty<float> m_count2;

    explicit inline CameraComponent(bool enabled) noexcept: m_enabled(enabled), m_count(0), m_count2(0) {
        m_count.RegisterChangeListener([](auto from, auto to) {
            SPDLOG_INFO("Value changed: {} - {}", from, to);
        });
        m_count2.RegisterChangeListener([](auto from, auto to) {
            SPDLOG_INFO("Value changed 2: {} - {}", from, to);
        });
        m_count += 1;
        ++m_count;
        m_count++;
        m_count -= 1;
        m_count2 += 4;
        m_count %= 2;

        auto b1 = m_count == m_count;
        auto b2 = m_count == m_count2;
        SPDLOG_INFO("Bool result: {} {}", b1, b2);
    }
};

class RootScene final : public SceneGraph {
public:
    explicit RootScene(::Runtime *runtime, SceneManager *owner, SceneGraph *parent) noexcept:
            SceneGraph(
                    runtime,
                    owner,
                    parent,
                    HeaderTech::Logging::make_logger_async<RootScene>(),
                    {
                            .window_size = runtime->GetWindow().GetSize()
                    }
            ) {
        Entities()
                .AddEntity()
                .WithComponent<CameraComponent>(true)
                .WithComponent<TransformComponent>(glm::vec3{0, 0, 0}, glm::quat{1, 0, 0, 1})
                .WithComponent<DebugGuiComponent>("Camera");
        Entities()
                .AddEntity()
                .WithComponent<RenderComponent>()
                .WithComponent<TransformComponent>(glm::vec3{0, 0, 0}, glm::quat{1, 0, 0, 1})
                .WithComponent<DebugGuiComponent>("Example");
        Entities()
                .AddEntity()
                .WithComponent<RenderComponent>();
        Entities()
                .AddEntity()
                .WithComponent<RenderComponent>();
        Entities()
                .AddEntity()
                .WithComponent<RenderComponent>()
                .WithComponent<TransformComponent>(glm::vec3{0, 0, 0}, glm::quat{1, 0, 0, 1})
                .WithComponent<DebugGuiComponent>("Example 2");
        Entities()
                .AddEntity()
                .WithComponent<RenderComponent>();
        Entities()
                .AddEntity()
                .WithComponent<RenderComponent>()
                .WithComponent<TransformComponent>(glm::vec3{0, 0, 0}, glm::quat{1, 0, 0, 1})
                .WithComponent<DebugGuiComponent>("Example 3");
        Entities()
                .AddEntity()
                .WithComponent<RenderComponent>();
        Entities()
                .AddEntity()
                .WithComponent<RenderComponent>()
                .WithComponent<TransformComponent>(glm::vec3{0, 0, 0}, glm::quat{1, 0, 0, 1})
                .WithComponent<DebugGuiComponent>("Example 4");
        Entities()
                .AddEntity()
                .WithComponent<RenderComponent>()
                .WithComponent<DebugGuiComponent>("Example 5");

        this->Runtime()->Subscribe<HeaderTech::Window::Events::KeyEvent>(this);
    }

    void OnEvent(HeaderTech::Window::Events::KeyEvent *event) {
        if (event->action == HeaderTech::Window::Events::KeyAction_PRESSED && event->key == GLFW_KEY_F) {
            this->Runtime()->GetWindow().ToggleFullscreen();
        }
    }

protected:
    using BlankExcludes = HeaderTech::EntityComponentSystem::EntityComponentViewExcludes<>;
    using RenderExcludes = HeaderTech::EntityComponentSystem::EntityComponentViewExcludes<RenderComponent>;
    using CameraExcludes = HeaderTech::EntityComponentSystem::EntityComponentViewExcludes<CameraComponent>;

    inline void OnActivated() noexcept final {
        SPDLOG_LOGGER_INFO(m_log, "Activated Root Scene");
        m_updateView = Entities().CreateView<TransformComponent>(CameraExcludes{});
        m_renderView = Entities().CreateView<RenderComponent, TransformComponent>(BlankExcludes{});
        m_cameraView = Entities().CreateView<CameraComponent, TransformComponent>(RenderExcludes{});
        m_debugView = Entities().CreateView<DebugGuiComponent>(CameraExcludes{});
    }

    inline void OnDeactivated() noexcept final {
        SPDLOG_LOGGER_INFO(m_log, "Deactivated Root Scene");
        m_updateView = nullptr;
        m_renderView = nullptr;
        m_debugView = nullptr;
        m_cameraView = nullptr;
    }

    inline void OnSceneWillBePushed() noexcept final {}

    inline void OnSceneWillBePopped() noexcept final {}

    inline void OnSceneWasPushed() noexcept final {}

    inline void OnSceneWasPopped() noexcept final {}

    inline void OnSceneTicked(double delta, double lag) noexcept final {
        TransformComponent *transform = nullptr;
        for (const auto &update: *m_updateView) {
            std::tie(std::ignore, transform) = update;
            transform->position.x += 2 * delta;
            transform->position.y += 3 * delta;
            transform->position.z += 2 * delta;

            transform->vector += {2 * delta, 2 * delta, 2 * delta};
        }

        CameraComponent *camera = nullptr;

        constexpr float speed = 2;
        bool forward = IsKeyPressed(HeaderTech::Core::KeyType::Key_W);
        bool backward = IsKeyPressed(HeaderTech::Core::KeyType::Key_S);
        bool strafeLeft = IsKeyPressed(HeaderTech::Core::KeyType::Key_A);
        bool strafeRight = IsKeyPressed(HeaderTech::Core::KeyType::Key_D);
        bool raise = IsKeyPressed(HeaderTech::Core::KeyType::Key_Space);
        bool lower = IsKeyPressed(HeaderTech::Core::KeyType::Key_Shift_Left);
        for (const auto &update:*m_cameraView) {
            std::tie(std::ignore, camera, transform) = update;
            if (forward) transform->position.x += speed * (float) delta;
            if (backward) transform->position.x -= speed * (float) delta;
            if (strafeLeft) transform->position.z -= speed * (float) delta;
            if (strafeRight) transform->position.z += speed * (float) delta;
            if (raise) transform->position.y += speed * (float) delta;
            if (lower) transform->position.y -= speed * (float) delta;
        }
    }

    inline void OnSceneRendered(
            double offset,
            const HeaderTech::Render::SceneGraph::SceneGraphRenderManagement &mgmt
    ) noexcept final {
        CameraComponent *camera = nullptr;
        TransformComponent *cameraTransform = nullptr;
        RenderComponent *render = nullptr;
        TransformComponent *transform = nullptr;
        for (const auto &camEntity : *m_cameraView) {
            std::tie(std::ignore, camera, cameraTransform) = camEntity;

            for (const auto &entity : *m_renderView) {
                std::tie(std::ignore, render, transform) = entity;

//                SPDLOG_LOGGER_INFO(
//                        m_log,
//                        "Render {} {} {}",
//                        transform->position.x,
//                        transform->position.y,
//                        transform->position.z
//                );
            }
        }
    }

    inline void OnDebugGuiRendered() noexcept final {
        ImGui::Begin("Example");
        EntityId entityId;
        DebugGuiComponent *debug = nullptr;
        TransformComponent *transform = nullptr;
        for (const auto &entity : *m_debugView) {
            std::tie(entityId, debug) = entity;
            ImGui::BulletText("%llu -> %s", entityId, debug->name);
        }
        for (const auto &entity : *m_updateView) {
            std::tie(entityId, transform) = entity;
            ImGui::BulletText(
                    "%llu -> %f\t%f\t%f",
                    entityId,
                    transform->position.x,
                    transform->position.y,
                    transform->position.z
            );
        }
        CameraComponent *camera = nullptr;
        ImGui::Text("Camera Components");
        for (const auto &entity : *m_cameraView) {
            std::tie(entityId, camera, transform) = entity;
            ImGui::BulletText(
                    "%llu -> %f\t%f\t%f",
                    entityId,
                    transform->position.x,
                    transform->position.y,
                    transform->position.z
            );
        }
        ImGui::End();
    }

    inline void OnFramebufferResized(int width, int height) noexcept final {
        SPDLOG_LOGGER_INFO(m_log, "Resize Framebuffer: {} {}", width, height);
    }

private:
    std::shared_ptr<HeaderTech::EntityComponentSystem::EntityComponentView<CameraExcludes, TransformComponent>> m_updateView;
    std::shared_ptr<HeaderTech::EntityComponentSystem::EntityComponentView<BlankExcludes, RenderComponent, TransformComponent>> m_renderView;
    std::shared_ptr<HeaderTech::EntityComponentSystem::EntityComponentView<RenderExcludes, CameraComponent, TransformComponent>> m_cameraView;
    std::shared_ptr<HeaderTech::EntityComponentSystem::EntityComponentView<CameraExcludes, DebugGuiComponent>> m_debugView;
};

int main(int argc, const char **argv) {
    try {
        IMGUI_CHECKVERSION();
#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable : 4068)
#endif
#pragma clang diagnostic push
#pragma ide diagnostic ignored "UnusedValue"
        int result = -1;
#pragma clang diagnostic pop
#ifdef _MSC_VER
#pragma warning(pop)
#endif
        auto config = BuildConfiguration(argc, argv);
        [[maybe_unused]] ScopedFileSystem fileSystem(argv[0], "Sandbox");
        {
            [[maybe_unused]] ScopedLogging logging(argc, argv);
            {
                ScopedProfiler profiler;
                {
                    ScopedGlfw glfw;
                    {
                        rmt_SetCurrentThreadName("MainLoop");
                        Runtime runtime(config);
                        {
                            HeaderTech::Scene::SceneManager sceneManager(&runtime);
                            sceneManager.SetRootScene<RootScene>();
                            result = runtime.Launch(sceneManager);
                        }
                    }
                }
            }
        }
        return result;
    } catch (std::exception &e) {
        return -1;
    }
}
