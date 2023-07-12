#include "scene_manager.h"

#include "imgui.h"

Scene::Scene(std::string name = "untitled") : mName(name)
{
}

Scene::~Scene()
{
}

std::string Scene::GetName()
{
    return mName;
}

unsigned int Scene::GetTime()
{
    return (unsigned int)(glfwGetTime() * 1000.0);
}

void Scene::Init()
{
}

void Scene::Clean()
{
}

void Scene::Start()
{
}

void Scene::Leave()
{
}

void Scene::Resize(int width, int height)
{
    glViewport(0, 0, width, height);
}

void Scene::OnKey(int key, int scancode, int action, int mods)
{
}

void Scene::OnChar(unsigned int codepoint)
{
}

void Scene::OnScoll(double xoffset, double yoffset)
{
}

void Scene::OnMouseMove(double xoffset, double yoffset)
{
}

void Scene::OnMouseButton(int button, int action, int mods)
{
}

SceneManager::SceneManager()
{
}

SceneManager::~SceneManager()
{
}

void SceneManager::RegisterScene(std::shared_ptr<Scene> scene)
{
    mSceneList.push_back(scene);
    if (!mCurrentScene)
        mCurrentScene = scene;
}

std::shared_ptr<Scene> SceneManager::GetCurrentScene()
{
    return mCurrentScene;
}

std::vector<std::shared_ptr<Scene>> SceneManager::GetSceneList()
{
    return mSceneList;
}

void SceneManager::SwitchScene(uint16_t index)
{
    DEBUG_PRINTF("SceneManager: Switch to scene %d \n", index);
    if (index < 0 || index >= mSceneList.size())
    {
        ERR_PRINT("scene index error.\n");
        return;
    }
    mCurrentScene = mSceneList[index];
}