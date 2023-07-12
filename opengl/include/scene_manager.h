#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

#include "common.h"

class Scene
{
protected:
    std::string mName;
    bool mInitialized = false;

private:
public:
    Scene(std::string name);
    ~Scene();
    std::string GetName();
    unsigned int GetTime();
    virtual void Init();
    virtual void Clean();
    virtual void Start();
    virtual void Leave();
    virtual void Resize(int width, int height);
    virtual void OnKey(int key, int scancode, int action, int mods);
    virtual void OnChar(unsigned int codepoint);
    virtual void OnScoll(double xoffset, double yoffset);
    virtual void OnMouseMove(double xoffset, double yoffset);
    virtual void OnMouseButton(int button, int action, int mods);
    virtual void GLRendering()    = 0;
    virtual void ImguiRendering() = 0;
};

class SceneManager
{
protected:
    std::shared_ptr<Scene> mCurrentScene;
    std::vector<std::shared_ptr<Scene>> mSceneList;

private:
public:
    SceneManager();
    ~SceneManager();
    void RegisterScene(std::shared_ptr<Scene> scene);
    std::shared_ptr<Scene> GetCurrentScene();
    std::vector<std::shared_ptr<Scene>> GetSceneList();
    void SwitchScene(uint16_t index);
};

#endif // SCENE_MANAGER_H