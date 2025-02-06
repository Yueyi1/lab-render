#ifndef OPG_H
#define OPG_H

#include <memory>
#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "scene_manager.h"

class Render
{
protected:
    // window
    GLFWwindow *mWindow;
    static int mWindowWidth;
    static int mWindowHeight;
    // scenes
    SceneManager mSceneManager;
    std::shared_ptr<Scene> mScene;
    std::vector<const char *> mSceneNameList;
    int mCurrentIndex = 0;
    // flag
    bool mInitSuccess;
    // imgui variables
    bool mWireframeEnabled = false;
    bool mDepthTestEnabled = true;
    bool mCullFaceEnabled = true;

private:
    void init();
    void loop();
    void cleanup();
    void sceneui();
    static void window_size_callback(GLFWwindow *window, int width, int height);
    static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);
    static void char_callback(GLFWwindow *window, unsigned int codepoint);
    static void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);
    static void cursor_callback(GLFWwindow *window, double xposIn, double yposIn);
    static void mouse_button_callback(GLFWwindow *window, int button, int action, int mods);

public:
    Render(/* args */);
    ~Render();
    void Checkout();
    void Start();
    void Stop();
    void LogCurrentSceneInfo();
    static void GetWindowSize(int &width, int &height);
};

#endif // OPG_H