#ifndef OPG_H
#define OPG_H

#include "scene_manager.h"
#include "scenes.h"

const int WindowWidth  = 800;
const int WindowHeight = 600;

class Render
{
protected:
    GLFWwindow *mWindow;

    // scenes
    SceneManager mSceneManager;
    std::shared_ptr<Scene> mScene;
    std::vector<const char *> mSceneNameList;
    int mCurrentIndex = 0;
    // flag
    bool mInitSuccess;

    static void window_size_callback(GLFWwindow *window, int width, int height)
    {
        Render *pThis = (Render *)glfwGetWindowUserPointer(window);

        pThis->Resize(width, height);
    }
    static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
    {
        Render *pThis = (Render *)glfwGetWindowUserPointer(window);

        pThis->OnKey(key, scancode, action, mods);
    }
    static void char_callback(GLFWwindow *window, unsigned int codepoint)
    {
        Render *pThis = (Render *)glfwGetWindowUserPointer(window);

        pThis->OnChar(codepoint);
    }
    static void scroll_callback(GLFWwindow *window, double xoffset, double yoffset)
    {
        Render *pThis = (Render *)glfwGetWindowUserPointer(window);

        pThis->OnScoll(xoffset, yoffset);
    }
    static void cursor_callback(GLFWwindow *window, double xposIn, double yposIn)
    {
        Render *pThis = (Render *)glfwGetWindowUserPointer(window);

        pThis->OnMouseMove(xposIn, yposIn);
    }
    static void mouse_button_callback(GLFWwindow *window, int button, int action, int mods)
    {
        Render *pThis = (Render *)glfwGetWindowUserPointer(window);

        pThis->OnMouseButton(button, action, mods);
    }

private:
    void init();
    void loop();
    void cleanup();
    void sceneui();

public:
    Render(/* args */);
    ~Render();
    void Checkout();
    void Start();
    void Stop();
    void LogCurrentSceneInfo();

    virtual void Resize(int width, int height)
    {
        glViewport(0, 0, width, height);
    }

    virtual void OnKey(int key, int scancode, int action, int mods)
    { /* NOTHING */
    }

    virtual void OnChar(unsigned int codepoint)
    { /* NOTHING */
    }

    virtual void OnScoll(double xoffset, double yoffset)
    { /* NOTHING */
    }

    virtual void OnMouseMove(double xoffset, double yoffset)
    { /* NOTHING */
    }

    virtual void OnMouseButton(int button, int action, int mods)
    { /* NOTHING */
    }
};

#endif // OPG_H