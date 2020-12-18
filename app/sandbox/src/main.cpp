#include <Sandbox.h>

class SampleScene2 final : public SceneGraph {
public:
    explicit SampleScene2(::Runtime *runtime, SceneManager *owner, SceneGraph *parent) :
            SceneGraph(runtime, owner, parent),
            m_log(HeaderTech::Logging::make_logger_async<SampleScene2>())
    {}

    ~SampleScene2() final
    { SPDLOG_LOGGER_INFO(m_log, "Destroy"); }

    void Activate() final
    { SPDLOG_LOGGER_INFO(m_log, "Activated"); }

    void Deactivate() final
    { SPDLOG_LOGGER_INFO(m_log, "Deactivated"); }

private:
    HeaderTech::Logging::Logger m_log;
};

class SampleScene3 final : public SceneGraph {
public:
    explicit SampleScene3(::Runtime *runtime, SceneManager *owner, SceneGraph *parent) :
            SceneGraph(runtime, owner, parent),
            m_log(HeaderTech::Logging::make_logger_async<SampleScene3>())
    {}

    ~SampleScene3() final
    { SPDLOG_LOGGER_INFO(m_log, "Destroy"); }

    void Activate() final
    { SPDLOG_LOGGER_INFO(m_log, "Activated"); }

    void Deactivate() final
    { SPDLOG_LOGGER_INFO(m_log, "Deactivated"); }

private:
    HeaderTech::Logging::Logger m_log;
};

class SampleScene4 final : public SceneGraph {
public:
    explicit SampleScene4(::Runtime *runtime, SceneManager *owner, SceneGraph *parent) :
            SceneGraph(runtime, owner, parent),
            m_log(HeaderTech::Logging::make_logger_async<SampleScene4>())
    {
        AddChildScene<SampleScene3>();
    }

    ~SampleScene4() final
    { SPDLOG_LOGGER_INFO(m_log, "Destroy"); }

    void Activate() final
    { SPDLOG_LOGGER_INFO(m_log, "Activated"); }

    void Deactivate() final
    { SPDLOG_LOGGER_INFO(m_log, "Deactivated"); }

private:
    HeaderTech::Logging::Logger m_log;
};

struct TransformComponent {
    float x, y, z;
    float pitch, yaw, roll;

    TransformComponent(float x, float y, float z, float pitch, float yaw, float roll)
            : x(x), y(y), z(z),
              pitch(pitch), yaw(yaw), roll(roll)
    {}
};

struct RenderComponent {
};
struct PhysicsComponent {
};
struct ImGuiComponent {
};

struct DebugComponent {
    const char *name;

    DebugComponent(const char *name) : name(name)
    {}
};

struct MaterialComponent {

};
struct DebugRenderComponent {

};
struct CameraComponent {

};

class SampleScene final : public SceneGraph, public RenderSurface {
public:
    explicit SampleScene(::Runtime *runtime, SceneManager *owner, SceneGraph *parent) :
            SceneGraph(runtime, owner, parent),
            RenderSurface(runtime->GetWindow().GetRenderContext()),
            m_log(HeaderTech::Logging::make_logger_async<SampleScene>()),
            m_view(nullptr)
    {
        AddChildScene<SampleScene2>();
        AddChildScene<SampleScene4>();

        runtime->Subscribe<HeaderTech::Window::Events::FramebufferSizeEvent>(this);

        auto entity1 = AddEntity()
                .WithComponent<TransformComponent>(1.f, 1.f, 1.f, 0.f, 0.f, 0.f)
                .WithComponent<DebugComponent>("Example Component")
                .WithComponent<CameraComponent>()
                .WithComponent<PhysicsComponent>()
                .WithComponent<ImGuiComponent>()
                .WithComponent<MaterialComponent>()
                .WithComponent<DebugRenderComponent>()
                .WithComponent<RenderComponent>()
                .ToEntityId();

        AddEntity()
                .WithComponent<TransformComponent>(1.f, 10.f, 1.f, 0.f, 0.f, 0.f)
                .WithComponent<DebugComponent>("Example Component 2")
                .WithComponent<PhysicsComponent>()
                .WithComponent<ImGuiComponent>()
                .WithComponent<MaterialComponent>()
                .WithComponent<RenderComponent>()
            /*.Release()*/;

        AddEntity()
                .WithComponent<TransformComponent>(0.f, 10.f, 0.f, 0.f, 0.f, 0.f)
                .WithComponent<DebugComponent>("Example Component 3")
                .WithComponent<PhysicsComponent>()
                .WithComponent<ImGuiComponent>()
                .WithComponent<MaterialComponent>()
                .WithComponent<RenderComponent>()
            /*.Release()*/;

        auto entity2 = AddEntity()
                .WithComponent<TransformComponent>(1.f, 10.f, 1.f, 0.f, 0.f, 0.f)
                .WithComponent<DebugComponent>("Example Component 4")
                .WithComponent<PhysicsComponent>()
                .WithComponent<ImGuiComponent>()
                .WithComponent<MaterialComponent>()
                .WithComponent<DebugRenderComponent>()
                .WithComponent<RenderComponent>()
                .ToEntityId();

        SPDLOG_LOGGER_INFO(m_log, "TransformComponent Id: {}",
                           HeaderTech::Scene::ECS::ComponentIdSeq<TransformComponent>::value());
        SPDLOG_LOGGER_INFO(m_log, "DebugComponent Id: {}",
                           HeaderTech::Scene::ECS::ComponentIdSeq<DebugComponent>::value());
        SPDLOG_LOGGER_INFO(m_log, "DebugComponent Id: {}",
                           HeaderTech::Scene::ECS::ComponentIdSeq<DebugComponent>::value());
        SPDLOG_LOGGER_INFO(m_log, "PhysicsComponent Id: {}",
                           HeaderTech::Scene::ECS::ComponentIdSeq<PhysicsComponent>::value());
        SPDLOG_LOGGER_INFO(m_log, "ImGuiComponent Id: {}",
                           HeaderTech::Scene::ECS::ComponentIdSeq<ImGuiComponent>::value());
        SPDLOG_LOGGER_INFO(m_log, "MaterialComponent Id: {}",
                           HeaderTech::Scene::ECS::ComponentIdSeq<MaterialComponent>::value());
        SPDLOG_LOGGER_INFO(m_log, "DebugRenderComponent Id: {}",
                           HeaderTech::Scene::ECS::ComponentIdSeq<DebugRenderComponent>::value());
        SPDLOG_LOGGER_INFO(m_log, "RenderComponent Id: {}",
                           HeaderTech::Scene::ECS::ComponentIdSeq<RenderComponent>::value());
        SPDLOG_LOGGER_INFO(m_log, "TransformComponent Id: {}",
                           HeaderTech::Scene::ECS::ComponentIdSeq<TransformComponent>::value());

        RegisterTickingSystem(
                [](double delta, double lag, const HeaderTech::Scene::ECS::EntityCollection &entities) {}
        );
        RegisterRenderingSystem(
                [](double offset, const HeaderTech::Scene::ECS::EntityCollection &entities) {
//                    for (auto &transform_render : components.Get<TransformComponent, RenderComponent>()) {
//
//                    }
                }
        );

        auto count = Collection().ComponentSize<RenderComponent>();
        SPDLOG_LOGGER_INFO(m_log, "RenderComponent Count: {}", count);

        GetEntity(entity1).RemoveComponent<CameraComponent>();
        GetEntity(entity2).AddComponent<CameraComponent>();

        auto view = Collection().View<RenderComponent, PhysicsComponent>();
        for (auto group : *view) {
            auto id = std::get<EntityId>(group);
            auto render = std::get<RenderComponent*>(group);
            auto physics = std::get<PhysicsComponent*>(group);
            SPDLOG_LOGGER_INFO(m_log, "Get data for entity: {}", id);
        }

        m_view = Collection().View<RenderComponent, TransformComponent, DebugComponent, PhysicsComponent>();
    }

    ~SampleScene() final
    { SPDLOG_LOGGER_INFO(m_log, "Destroy"); }

    void Activate() final
    {
        SPDLOG_LOGGER_INFO(m_log, "Activated");
        OnSetup();
        for (auto group : *m_view) {
            auto id = std::get<EntityId>(group);
            auto render = std::get<RenderComponent *>(group);
            auto transform = std::get<TransformComponent *>(group);
            auto debug = std::get<DebugComponent *>(group);
            SPDLOG_LOGGER_DEBUG(
                    m_log,
                    "Get data for entity 2: {} {} - {} {} {}",
                    id,
                    debug->name,
                    transform->x,
                    transform->y,
                    transform->z
            );
        }
    }

    void Deactivate() final
    {
        SPDLOG_LOGGER_INFO(m_log, "Deactivated");
        OnTeardown();
    }

    void TickScene(double delta, double lag) final
    {
        HeaderTech::Profiler::ScopedProfileMark frame("TickScene");
        SceneGraph::TickScene(delta, lag);
//        Owner()->PushScene();



        for (auto group : *m_view) {
            auto transform = std::get<TransformComponent *>(group);

            transform->x *= (float) (10 * delta);
            transform->y *= (float) (-10 * delta);
            transform->z *= (float) (80 * delta);
            transform->yaw *= (float) (10 * delta);
            transform->pitch *= (float) (-10 * delta);
            transform->roll *= (float) (80 * delta);
        }
    }

    void RenderScene(double offset) final
    {
        HeaderTech::Profiler::ScopedProfileMark frame("RenderScene");
        SceneGraph::RenderScene(offset);
        Render(offset);

        SPDLOG_LOGGER_INFO(
                m_log,
                "Render; {}",
                offset
        );

        for (auto group : *m_view) {
            auto id = std::get<EntityId>(group);
            auto render = std::get<RenderComponent *>(group);
            auto transform = std::get<TransformComponent *>(group);
            auto debug = std::get<DebugComponent *>(group);
            SPDLOG_LOGGER_INFO(
                    m_log,
                    "Get data for entity 2: {} {} - {} {} {}",
                    id,
                    debug->name,
                    transform->x,
                    transform->y,
                    transform->z
            );
        }
    }

    void OnEvent(HeaderTech::Window::Events::FramebufferSizeEvent *event)
    { SPDLOG_LOGGER_INFO(m_log, "Resize Framebuffer: {}x{}", event->width, event->height); }

protected:
    void OnSetup() final
    {
        m_ctx->MakeCurrent();
    }

    void OnTeardown() final
    {
        m_ctx->MakeCurrent();
    }

    void OnRender(double offset) final
    {
        m_ctx->MakeCurrent();
    }

private:
    HeaderTech::Logging::Logger m_log;
    HeaderTech::Scene::ECS::EntityComponentViewPtr<RenderComponent, TransformComponent, DebugComponent, PhysicsComponent> m_view;
};

int main(int argc, const char **argv)
{
    auto config = BuildConfiguration(argc, argv);
    [[maybe_unused]] ScopedFileSystem fileSystem(argv[0], "Sandbox");
    {
        [[maybe_unused]] ScopedLogging logging(argc, argv);
        {
            ScopedProfiler profiler;
            {
                ScopedGlfw glfw;
                {

                    Runtime runtime(config);
                    {
                        HeaderTech::Scene::SceneManager sceneManager(&runtime);
                        sceneManager.SetRootScene<SampleScene>();
                        return runtime.Launch(sceneManager);
                    }
                }
            }
        }
    }
}
