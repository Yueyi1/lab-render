#include "scenes.h"

#include <stb_image.h>
#include <glm/gtc/matrix_transform.hpp>


#include "opg.h"


class Scene_5 : public Scene
{
private:
    // Member variables
    Shader* mShader;
    Model* mModel;
    Camera mCamera;

    float mLastX = 0;
    float mLastY = 0;
    bool mFirstMouse = true;
    bool mMouseDown = false;
    float mDeltaTime = 0.0f;
    float mLastFrame = 0.0f;

public:
    Scene_5(std::string name = "Scene_5") : Scene(name){};
    ~Scene_5()
    {
        if (mInitialized)
            Clean();
    }

    void Init()
    {
        stbi_set_flip_vertically_on_load(true); // make sure you set this flag before load any models

        std::string vpath("../../../shaders/1-3.vert");
        std::string fpath("../../../shaders/1-3.frag");
        ShaderInfo shaders[3] = { {GL_VERTEX_SHADER, vpath, 0}, {GL_FRAGMENT_SHADER, fpath, 0}, {GL_NONE, "", 0} };

        mShader = new Shader(shaders);

        // load model
        //const char *pFile = "../../../models/DragonAttenuation/glTF/DragonAttenuation.gltf";
        //const char *pFile = "../../../models/buster_drone/scene.gltf";
        const char* pFile = "../../../models/backpack/backpack.obj";
        mModel = new Model(pFile);

        mInitialized = true;
    }

    void Clean()
    {
        delete mShader;
        delete mModel;
        glUseProgram(0);
    }

    void Start()
    {
        if (!mInitialized)
            Init();
        Render::GetWindowSize((int&)mLastX, (int&)mLastY);
        mLastX /= 2;
        mLastY /= 2;
        glEnable(GL_DEPTH_TEST);
    }

    void Leave()
    {
        glDisable(GL_DEPTH_TEST);
    }

    void GLRendering()
    {
        float currentFrame = static_cast<float>(glfwGetTime());
        mDeltaTime = currentFrame - mLastFrame;
        mLastFrame = currentFrame;

        // render
        // ------
        glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        mShader->use();
        // view/projection transformations
        int WindowWidth, WindowHeight;
        Render::GetWindowSize(WindowWidth, WindowHeight);
        glm::mat4 projection =
            glm::perspective(glm::radians(45.0f), (float)WindowWidth / (float)WindowHeight, 0.1f, 100.0f);
        glm::mat4 view = mCamera.getViewMatrix();
        mShader->setMat4("projection", projection);
        mShader->setMat4("view", view);

        // render the loaded model
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
        model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        model = glm::scale(model, glm::vec3(0.1f));
        mShader->setMat4("model", model);

        mModel->Draw(*mShader);
    }

    void ImguiRendering()
    {

    }

    void OnKey(int key, int scancode, int action, int mods)
    {
        if (action == GLFW_PRESS || action == GLFW_REPEAT)
        {
            // LogMessage("GLFW EVENT:" + key);
            switch (key)
            {
            case GLFW_KEY_W:
            {
                mCamera.moveForward(mDeltaTime * 10);
                break;
            }
            case GLFW_KEY_S:
            {
                mCamera.moveBackward(mDeltaTime * 10);
                break;
            }
            case GLFW_KEY_A:
            {
                mCamera.moveLeft(mDeltaTime * 10);
                break;
            }
            case GLFW_KEY_D:
            {
                mCamera.moveRight(mDeltaTime * 10);
                break;
            }
            case GLFW_MOUSE_BUTTON_1:
            {
                mMouseDown = true;
                break;
            }
            }
        }
        else if (action == GLFW_RELEASE)
        {
            // LogMessage("GLFW_RELEASE");
            switch (key)
            {
            case GLFW_MOUSE_BUTTON_1:
            {
                mMouseDown = false;
                break;
            }
            }
        }
    }

    void OnMouseMove(double xposIn, double yposIn)
    {
        float xpos = static_cast<float>(xposIn);
        float ypos = static_cast<float>(yposIn);

        if (!mMouseDown)
        {
            mLastX = xpos;
            mLastY = ypos;
            return;
        }

        if (mFirstMouse)
        {
            mLastX = xpos;
            mLastY = ypos;
            mFirstMouse = false;
        }

        float xoffset = xpos - mLastX;
        float yoffset = mLastY - ypos;

        mLastX = xpos;
        mLastY = ypos;

        mCamera.rotate(xoffset, yoffset);
    }

    void OnMouseButton(int button, int action, int mods)
    {
        if (action == GLFW_PRESS)
        {
            switch (button)
            {
            case GLFW_MOUSE_BUTTON_1:
            {
                mMouseDown = true;
                break;
            }
            }
        }
        else if (action == GLFW_RELEASE)
        {
            switch (button)
            {
            case GLFW_MOUSE_BUTTON_1:
            {
                mMouseDown = false;
                break;
            }
            }
        }
    }
};