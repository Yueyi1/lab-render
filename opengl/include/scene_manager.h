#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

#include <memory>
#include <vector>

#include "scenes.h"

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