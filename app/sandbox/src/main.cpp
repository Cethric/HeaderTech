#define DEFINE_IMPLEMENTATION 1
#define GLFW_INCLUDE_NONE 1

#include <Sandbox.h>

using Runtime = HeaderTech::Core::Runtime;

class ExampleScene final : public HeaderTech::Scene::Scene {
public:
    void Tick(double delta) final
    {
        spdlog::info("Example Scene");
    }

    void Render(double offset) final
    {}
};

class ExampleScene2 final : public HeaderTech::Scene::Scene {
public:
    void Tick(double delta) final
    {
        spdlog::info("Example Scene 2");
    }

    void Render(double offset) final
    {}
};

class ExampleScene3 final : public HeaderTech::Scene::Scene {
public:
    void Tick(double delta) final
    {
        spdlog::info("Example Scene 3");
    }

    void Render(double offset) final
    {}
};

int main(int argc, const char **argv)
{
    auto config = HeaderTech::Config::BuildConfiguration(argc, argv);
    [[maybe_unused]] HeaderTech::FileSystem::Scoped::ScopedFileSystem fileSystem(argv[0], "Sandbox");
    {
        [[maybe_unused]] HeaderTech::Logging::Scoped::ScopedLogging logging(argc, argv);
        {
            HeaderTech::Profiler::Scoped::ScopedProfiler profiler;
            {
                HeaderTech::Core::Scoped::ScopedGlfw glfw;
                {
                    Runtime runtime(config);
                    {
                        HeaderTech::Scene::SceneManager sceneManager;
                        sceneManager.PushScene(std::make_shared<ExampleScene>());
                        sceneManager.PushScene(std::make_shared<ExampleScene2>());
                        sceneManager.PushScene(std::make_shared<ExampleScene3>());
                        sceneManager.PopScene();
                        return runtime.Launch(sceneManager);
                    }
                }
            }
        }
    }
}
