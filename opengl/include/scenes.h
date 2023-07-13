#ifndef SCENES_H
#define SCENES_H

#include <string>

#include <glad/glad.h>

#include "model.h"
#include "camera.h"

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

class Scene1_1 : public Scene
{
private:
    // Member variables
    Shader *mShader;
    GLuint VAOs[1];
    GLuint VBOs[1];
    enum Attrib_IDs
    {
        vPosition = 0
    };

public:
    Scene1_1(std::string name = "Scene1_1") : Scene(name){};
    ~Scene1_1()
    {
        if (mInitialized)
            Clean();
    };
    void Init() override;
    void Clean() override;
    void Start() override;
    void Leave() override;
    void GLRendering() override;
    void ImguiRendering() override;
};

class Scene1_2 : public Scene
{
private:
    // Member variables
    float aspect = 600.0 / 800.0;
    GLuint vao[1];
    GLuint vbo[1];
    GLuint ebo[1];
    Shader *mShader;

public:
    Scene1_2(std::string name = "Scene1_2") : Scene(name){};
    ~Scene1_2()
    {
        if (mInitialized)
            Clean();
    };
    void Init() override;
    void Clean() override;
    void Start() override;
    void Leave() override;
    void Resize(int width, int height) override;
    void GLRendering() override;
    void ImguiRendering() override;
};

class Scene1_3 : public Scene
{
private:
    // Member variables
    Camera mCamera;
    GLuint vao[1];
    GLuint vbo[1];
    GLuint ebo[1];
    Shader *mShader;

public:
    Scene1_3(std::string name = "Scene1_3") : Scene(name){};
    ~Scene1_3()
    {
        if (mInitialized)
            Clean();
    };
    void Init() override;
    void Clean() override;
    void Start() override;
    void Leave() override;
    void GLRendering() override;
};

#endif // SCENE_H