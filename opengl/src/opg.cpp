#include "opg.h"

#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

#include "common.h"
#include "scenes/scenes.h"
#include <scenes/scene_5.cpp>

// opg.cpp
int Render::mWindowWidth  = 1280;
int Render::mWindowHeight = 720;

Render::Render()
{
    static bool counter = false;
    if (counter)
    {
        ERR_PRINT("You are trying to construct a new Render which should be global unique.\n");
        return;
    }
    init();
    counter = true;
}

Render::~Render()
{
    if (mInitSuccess)
        cleanup();
}

void Render::init()
{
    DEBUG_PRINTF("enter Render::init()\n");
    // init GLFW
    DEBUG_PRINTF("Render::init() load glfw\n");
    if (!glfwInit())
        DEBUG_PRINTF("Render::init() glfwInit() failed\n");
#ifdef _DEBUG
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
#endif
    // Create a GLFW window
    mWindow = glfwCreateWindow(mWindowWidth, mWindowHeight, "OPG Example", NULL, NULL);
    if (!mWindow)
    {
        glfwTerminate();
        return;
    }
    glfwSetWindowUserPointer(mWindow, this);
    glfwSetWindowSizeCallback(mWindow, window_size_callback);
    glfwSetKeyCallback(mWindow, key_callback);
    glfwSetCharCallback(mWindow, char_callback);
    glfwSetScrollCallback(mWindow, scroll_callback);
    glfwSetCursorPosCallback(mWindow, cursor_callback);
    glfwSetMouseButtonCallback(mWindow, mouse_button_callback);

    glfwMakeContextCurrent(mWindow);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        DEBUG_PRINTF("Failed to initialize OpenGL context\n");
        return;
    }
    // glad populates global constants after loading to indicate,
    // if a certain extension/version is available.
    DEBUG_PRINTF("OpenGL %d.%d\n", GLVersion.major, GLVersion.minor);

    // Initialize ImGui
    DEBUG_PRINTF("Render::init() load imgui\n");
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(mWindow, true);
    ImGui_ImplOpenGL3_Init("#version 460");

    // Load Scene
    std::shared_ptr<Scene1_1> scene1_1 = std::make_shared<Scene1_1>("Scene1_1");
    std::shared_ptr<Scene1_2> scene1_2 = std::make_shared<Scene1_2>("Scene1_2");
    std::shared_ptr<Scene1_3> scene1_3 = std::make_shared<Scene1_3>("Scene1_3");
    std::shared_ptr<Scene1_4> scene1_4 = std::make_shared<Scene1_4>("Scene1_4");
    std::shared_ptr<Scene_5> scene_5 = std::make_shared<Scene_5>("Scene_5");
    mSceneManager.RegisterScene(scene1_1);
    mSceneManager.RegisterScene(scene1_2);
    mSceneManager.RegisterScene(scene1_3);
    mSceneManager.RegisterScene(scene1_4);
    mSceneManager.RegisterScene(scene_5);
    mScene        = mSceneManager.GetCurrentScene();
    int scene_num = mSceneManager.GetSceneList().size();
    for (auto item : mSceneManager.GetSceneList())
    {
        const char *tmp = new char[item->GetName().length() + 1];
        std::strcpy(const_cast<char *>(tmp), item->GetName().c_str());
        mSceneNameList.push_back(tmp);
    }
    mScene->Start();

    mInitSuccess = true;
    DEBUG_PRINTF("Render::init() %i \n", mInitSuccess);
}

void Render::loop()
{
    while (!glfwWindowShouldClose(mWindow))
    {
        glfwPollEvents();

        // GL part
        mScene->GLRendering();

        // IMGUI part
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // TODO: draw imgui stuff here
        sceneui();
        mScene->ImguiRendering();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(mWindow);
    }
}

void Render::cleanup()
{
    DEBUG_PRINTF("enter Render::cleanup()\n");

    for (const char *item : mSceneNameList)
    {
        delete[] item;
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(mWindow);
    glfwTerminate();
}

void Render::sceneui()
{
    // scenes switch
    static int last_scen_index = mCurrentIndex;
    if (ImGui::Begin("Scene Switcher"))
    {
        if (ImGui::Combo("ScenesList", &mCurrentIndex, mSceneNameList.data(), mSceneNameList.size()))
        {
            if (mCurrentIndex != last_scen_index)
            {
                mSceneManager.SwitchScene(mCurrentIndex);
                mScene->Leave();
                mScene = mSceneManager.GetCurrentScene();
                mScene->Start();
                last_scen_index = mCurrentIndex;
            }
        }
    }
    ImGui::End();
    // global gl settings
    if (ImGui::Begin("GL Global Settings"))
    {
        if (ImGui::Checkbox("Wireframe Mode", &mWireframeEnabled))
        {
            if (mWireframeEnabled)
            {
                glEnable(GL_POLYGON_OFFSET_LINE);
                glPolygonOffset(-1.0f, -1.0f);
                glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            }
            else
            {
                glDisable(GL_POLYGON_OFFSET_LINE);
                glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            }
        }
        if (ImGui::Checkbox("Depth Test", &mDepthTestEnabled))
        {
            if (mDepthTestEnabled)
            {
                glEnable(GL_DEPTH_TEST);
                glDepthFunc(GL_LESS);
            }
            else
            {
                glDisable(GL_DEPTH_TEST);
            }
        }
        if (ImGui::Checkbox("Face Cull", &mCullFaceEnabled))
        {
            if (mCullFaceEnabled)
            {
                glEnable(GL_CULL_FACE);
            }
            else
            {
                glDisable(GL_CULL_FACE);
            }
        }
    }
    ImGui::End();
}

void Render::window_size_callback(GLFWwindow *window, int width, int height)
{
    Render *pThis = (Render *)glfwGetWindowUserPointer(window);
    mWindowWidth  = width;
    mWindowHeight = height;
    pThis->mScene->OnResize(width, height);
}

void Render::key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    Render *pThis = (Render *)glfwGetWindowUserPointer(window);

    pThis->mScene->OnKey(key, scancode, action, mods);
}

void Render::char_callback(GLFWwindow *window, unsigned int codepoint)
{
    Render *pThis = (Render *)glfwGetWindowUserPointer(window);

    pThis->mScene->OnChar(codepoint);
}

void Render::scroll_callback(GLFWwindow *window, double xoffset, double yoffset)
{
    Render *pThis = (Render *)glfwGetWindowUserPointer(window);

    pThis->mScene->OnScoll(xoffset, yoffset);
}

void Render::cursor_callback(GLFWwindow *window, double xposIn, double yposIn)
{
    Render *pThis = (Render *)glfwGetWindowUserPointer(window);

    pThis->mScene->OnMouseMove(xposIn, yposIn);
}

void Render::mouse_button_callback(GLFWwindow *window, int button, int action, int mods)
{
    Render *pThis = (Render *)glfwGetWindowUserPointer(window);

    pThis->mScene->OnMouseButton(button, action, mods);
}

void Render::Start()
{
    if (!mInitSuccess)
    {
        ERR_PRINT("Render::Start() : opg render is uninitlized.")
        return;
    }
    loop();
}

void Render::LogCurrentSceneInfo()
{
}

void Render::GetWindowSize(int &width, int &height)
{
    width  = mWindowWidth;
    height = mWindowHeight;
}

int main(int argc, char **argv)
{
#ifdef DEBUG
    // init debug toolkits
    OPGToolkits toolkits;
#endif

    Render opg;
    opg.Start();
    return 0;
}