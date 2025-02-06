#include "scenes.h"

#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <stb_image.h>

#include "common.h"
#include "opg.h"

static inline float random_float()
{
    float res;
    unsigned int tmp;
    static unsigned int seed = 0x13371337;

    seed *= 16807;

    tmp = seed ^ (seed >> 4) ^ (seed << 15);

    *((unsigned int *)&res) = (tmp >> 9) | 0x3F800000;

    return (res - 1.0f);
}

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

void Scene::OnResize(int width, int height)
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

void Scene1_1::Init()
{
    static const GLfloat vertices[52][2] = {// Points
                                            {-0.8, -0.8},
                                            {0.8, 0.8},
                                            {0.8, -0.8},
                                            {-0.8, 0.8},
                                            // triangle
                                            {0., 0.},
                                            {0.05, 0.2},
                                            {0.1, 0.},
                                            {0.15, 0.2},
                                            {0.2, 0.},
                                            {0.25, 0.2},
                                            {0.3, 0.},
                                            {0.35, 0.2},
                                            {0.4, 0.},
                                            {0.45, 0.2},
                                            {0.5, 0.},
                                            {0.55, 0.2},
                                            // triangle strip
                                            {0., 0.3},
                                            {0.05, 0.5},
                                            {0.1, 0.3},
                                            {0.15, 0.5},
                                            {0.2, 0.3},
                                            {0.25, 0.5},
                                            {0.3, 0.3},
                                            {0.35, 0.5},
                                            {0.4, 0.3},
                                            {0.45, 0.5},
                                            {0.5, 0.3},
                                            {0.55, 0.5},
                                            // triangle fan
                                            {0., 0.6},
                                            {0.05, 0.8},
                                            {0.1, 0.6},
                                            {0.15, 0.8},
                                            {0.2, 0.6},
                                            {0.25, 0.8},
                                            {0.3, 0.6},
                                            {0.35, 0.8},
                                            {0.4, 0.6},
                                            {0.45, 0.8},
                                            {0.5, 0.6},
                                            {0.55, 0.8},
                                            // triangle fan
                                            {0., -0.6},
                                            {0.05, -0.8},
                                            {0.1, -0.6},
                                            {0.15, -0.8},
                                            {0.2, -0.6},
                                            {0.25, -0.8},
                                            {0.3, -0.6},
                                            {0.35, -0.8},
                                            {0.4, -0.6},
                                            {0.45, -0.8},
                                            {0.5, -0.6},
                                            {0.55, -0.8}};

    glCreateVertexArrays(1, VAOs);
    glCreateBuffers(1, VBOs);
    glNamedBufferStorage(VBOs[0], sizeof(vertices), vertices, 0);

    std::string vpath("../../../shaders/1-1.vert");
    std::string fpath("../../../shaders/1-1.frag");
    ShaderInfo shaders[3] = {{GL_VERTEX_SHADER, vpath, 0}, {GL_FRAGMENT_SHADER, fpath, 0}, {GL_NONE, "", 0}};
    mShader               = new Shader(shaders);

    // VBO
    glBindVertexArray(VAOs[0]);
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
    glVertexAttribPointer(vPosition, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
    glEnableVertexAttribArray(vPosition);
    mInitialized = true;
}

void Scene1_1::Clean()
{
    delete mShader;
    glUseProgram(0);
    glDeleteVertexArrays(1, VAOs);
    glDeleteBuffers(1, VBOs);
}

void Scene1_1::Start()
{
    if (!mInitialized)
        Init();

    // set gl global state
    glPolygonMode(GL_FRONT, GL_LINE);
    glPolygonMode(GL_BACK, GL_FILL);
    glFrontFace(GL_CW);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
}

void Scene1_1::Leave()
{
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glFrontFace(GL_CCW);
    glDisable(GL_CULL_FACE);
}

void Scene1_1::GLRendering()
{
    static const float black[] = {0.0f, 0.0f, 0.0f, 0.0f};
    glClearBufferfv(GL_COLOR, 0, black);
    // Activate simple shading program
    mShader->use();
    mShader->setFloat("u_time", (GLfloat)glfwGetTime());
    mShader->setVec2("u_resolution", 800.0f, 600.0f);

    glBindVertexArray(VAOs[0]);

    // draw points
    // glEnable(GL_POINT_SPRITE); // use gl_PointCoord to see effects
    // glEnable(GL_PROGRAM_POINT_SIZE);
    // glPointSize(64.0f);
    // glDrawArrays(GL_POINTS, 0, 4);

    // draw lines
    // glLineWidth(64.0f);
    // glDrawArrays(GL_LINES, 0, 4);
    // glDrawArrays(GL_LINE_LOOP, 0, 4);
    // glDrawArrays(GL_LINE_STRIP, 0, 4);

    // draw triangle
    glDrawArrays(GL_TRIANGLES, 4, 12);
    glDrawArrays(GL_TRIANGLE_STRIP, 16, 12);
    glDrawArrays(GL_TRIANGLE_FAN, 28, 12);
    glDrawArrays(GL_TRIANGLE_FAN, 40, 12);
}

void Scene1_1::ImguiRendering()
{
}

void Scene1_2::Init()
{
    std::string vpath("../../../shaders/1-2.vert");
    std::string fpath("../../../shaders/1-2.frag");
    ShaderInfo shaders[3] = {{GL_VERTEX_SHADER, vpath, 0}, {GL_FRAGMENT_SHADER, fpath, 0}, {GL_NONE, "", 0}};
    mShader               = new Shader(shaders);

    mShader->use();

    // A single triangle
    static const GLfloat vertex_positions[] = {
        -1.0f, -1.0f, 0.0f, 1.0f, 1.0f, -1.0f, 0.0f, 1.0f, -1.0f, 1.0f, 0.0f, 1.0f, -1.0f, -1.0f, 0.0f, 1.0f,
    };

    // Color for each vertex
    static const GLfloat vertex_colors[] = {1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
                                            1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f};

    // Indices for the triangle strips
    static const GLushort vertex_indices[] = {0, 1, 2};

    // Set up the element array buffer
    glGenBuffers(1, ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo[0]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(vertex_indices), vertex_indices, GL_STATIC_DRAW);

    // Set up the vertex attributes
    glGenVertexArrays(1, vao);
    glBindVertexArray(vao[0]);

    glGenBuffers(1, vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_positions) + sizeof(vertex_colors), NULL, GL_STATIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertex_positions), vertex_positions);
    glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertex_positions), sizeof(vertex_colors), vertex_colors);

    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, NULL);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (const GLvoid *)sizeof(vertex_positions));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    mInitialized = true;
}

void Scene1_2::Clean()
{
    delete mShader;
    glUseProgram(0);
    glDeleteVertexArrays(1, vao);
    glDeleteBuffers(1, vbo);
}

void Scene1_2::Start()
{
    if (!mInitialized)
        Init();
    // gl global settings
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
}

void Scene1_2::Leave()
{
    glDisable(GL_CULL_FACE);
    glDisable(GL_DEPTH_TEST);
}

void Scene1_2::OnResize(int width, int height)
{
    DEBUG_PRINTF("SCENE1_2 : RESIZE width = %i height = %i \n", width, height);
    glViewport(0, 0, width, height);
    aspect = float(height) / float(width);
}

void Scene1_2::GLRendering()
{
    float t        = float(GetTime() & 0x1FFF) / float(0x1FFF);
    static float q = 0.0f;
    static const glm::vec3 X(1.0f, 0.0f, 0.0f);
    static const glm::vec3 Y(0.0f, 1.0f, 0.0f);
    static const glm::vec3 Z(0.0f, 0.0f, 1.0f);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Activate simple shading program
    mShader->use();

    // Set up the model and projection matrix
    glm::mat4 projection_matrix(glm::frustum(-1.0f, 1.0f, -aspect, aspect, 1.0f, 500.0f));
    mShader->setMat4("projection_matrix", projection_matrix);

    // Set up for a glDrawElements call
    glBindVertexArray(vao[0]);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo[0]);

    glm::mat4 model_matrix = glm::mat4(1.0f);

    // Draw Arrays...
    model_matrix = glm::translate(model_matrix, glm::vec3(-3.0f, 0.0f, -5.0f));
    mShader->setMat4("model_matrix", model_matrix);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    // DrawElements
    model_matrix = glm::translate(model_matrix, glm::vec3(2.0f, 0.0f, 0.0f));
    mShader->setMat4("model_matrix", model_matrix);
    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_SHORT, NULL);

    // DrawElementsBaseVertex
    model_matrix = glm::translate(model_matrix, glm::vec3(2.0f, 0.0f, 0.0f));
    mShader->setMat4("model_matrix", model_matrix);
    glDrawElementsBaseVertex(GL_TRIANGLES, 3, GL_UNSIGNED_SHORT, NULL, 1);

    // DrawArraysInstanced
    model_matrix = glm::translate(model_matrix, glm::vec3(2.0f, 0.0f, 0.0f));
    mShader->setMat4("model_matrix", model_matrix);
    glDrawArraysInstanced(GL_TRIANGLES, 0, 3, 1);
}

void Scene1_2::ImguiRendering()
{
}

void Scene1_3::Init()
{
    stbi_set_flip_vertically_on_load(true); // make sure you set this flag before load any models

    std::string vpath("../../../shaders/1-3.vert");
    std::string fpath("../../../shaders/1-3.frag");
    ShaderInfo shaders[3] = {{GL_VERTEX_SHADER, vpath, 0}, {GL_FRAGMENT_SHADER, fpath, 0}, {GL_NONE, "", 0}};

    mShader = new Shader(shaders);

    // load model
    const char *pFile = "../../../models/DragonAttenuation/glTF/DragonAttenuation.gltf";
    //const char *pFile = "../../../models/backpack/backpack.obj";
    mModel            = new Model(pFile);

    mInitialized = true;
}

void Scene1_3::Clean()
{
    delete mShader;
    delete mModel;
    glUseProgram(0);
}

void Scene1_3::Start()
{
    if (!mInitialized)
        Init();
    Render::GetWindowSize((int &)mLastX, (int &)mLastY);
    mLastX /= 2;
    mLastY /= 2;
    glEnable(GL_DEPTH_TEST);
}

void Scene1_3::Leave()
{
    glDisable(GL_DEPTH_TEST);
}

void Scene1_3::GLRendering()
{
    float currentFrame = static_cast<float>(glfwGetTime());
    mDeltaTime         = currentFrame - mLastFrame;
    mLastFrame         = currentFrame;

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
    model           = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
    model           = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    model           = glm::scale(model, glm::vec3(0.1f));
    mShader->setMat4("model", model);

    mModel->Draw(*mShader);
}

void Scene1_3::ImguiRendering()
{
}

void Scene1_3::OnKey(int key, int scancode, int action, int mods)
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

void Scene1_3::OnMouseMove(double xposIn, double yposIn)
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
        mLastX      = xpos;
        mLastY      = ypos;
        mFirstMouse = false;
    }

    float xoffset = xpos - mLastX;
    float yoffset = mLastY - ypos;

    mLastX = xpos;
    mLastY = ypos;

    mCamera.rotate(xoffset, yoffset);
}

void Scene1_3::OnMouseButton(int button, int action, int mods)
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

void Scene1_4::Init()
{
    std::string vpath("../../../shaders/1-4.vert");
    std::string fpath("../../../shaders/1-4.frag");
    ShaderInfo shaders[3] = {{GL_VERTEX_SHADER, vpath, 0}, {GL_FRAGMENT_SHADER, fpath, 0}, {GL_NONE, "", 0}};
    mShader               = new Shader(shaders);
    mShader->use();

    // init data
    // 8 corners of a cube, side length 2, centered on the origin
    static const GLfloat cube_positions[] = {-1.0f, -1.0f, -1.0f, 1.0f, -1.0f, -1.0f, 1.0f,  1.0f,  -1.0f, 1.0f, -1.0f,
                                             1.0f,  -1.0f, 1.0f,  1.0f, 1.0f,  1.0f,  -1.0f, -1.0f, 1.0f,  1.0f, -1.0f,
                                             1.0f,  1.0f,  1.0f,  1.0f, -1.0f, 1.0f,  1.0f,  1.0f,  1.0f,  1.0f};

    // Color for each vertex
    static const GLfloat cube_colors[] = {1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f,
                                          1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
                                          0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.5f, 0.5f, 0.5f, 1.0f};

    // Indices for the triangle strips
    static const GLushort cube_indices[] = {
        0,      1, 2, 3, 6, 7, 4, 5, // First strip
        0xFFFF,                      // <<-- This is the restart index
        2,      6, 0, 4, 1, 5, 3, 7  // Second strip
    };

    // Set up the element array buffer
    glGenBuffers(1, ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo[0]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cube_indices), cube_indices, GL_STATIC_DRAW);

    // Set up the vertex attributes
    glGenVertexArrays(1, vao);
    glBindVertexArray(vao[0]);

    glGenBuffers(1, vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cube_positions) + sizeof(cube_colors), NULL, GL_STATIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(cube_positions), cube_positions);
    glBufferSubData(GL_ARRAY_BUFFER, sizeof(cube_positions), sizeof(cube_colors), cube_colors);

    // chang color
    static glm::vec4 *vertex_positions = (glm::vec4 *)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
    for (int n = 8; n < 16; n++)
    {
        vertex_positions[n] =
            glm::vec4(random_float() * 2.0f - 1.0f, random_float() * 2.0f - 1.0f, random_float() * 2.0f - 1.0f, 1.0f);
    }
    glUnmapBuffer(GL_ARRAY_BUFFER);

    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, NULL);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (const GLvoid *)sizeof(cube_positions));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
}

void Scene1_4::Clean()
{
    delete mShader;
    glUseProgram(0);
    glDeleteVertexArrays(1, vao);
    glDeleteBuffers(1, vbo);
}

void Scene1_4::Start()
{
    if (!mInitialized)
        Init();
    glEnable(GL_DEPTH_TEST);
}

// Define USE_PRIMITIVE_RESTART to 0 to use two separate draw commands
#define USE_PRIMITIVE_RESTART 0

void Scene1_4::Leave()
{
    glDisable(GL_DEPTH_TEST);
#if USE_PRIMITIVE_RESTART
    glDisable(GL_PRIMITIVE_RESTART);
#endif
}

void Scene1_4::GLRendering()
{
    float t        = float(GetTime() & 0x1FFF) / float(0x1FFF);
    static float q = 0.0f;
    static const glm::vec3 X(1.0f, 0.0f, 0.0f);
    static const glm::vec3 Y(0.0f, 1.0f, 0.0f);
    static const glm::vec3 Z(0.0f, 0.0f, 1.0f);

    // Setup
    glEnable(GL_CULL_FACE);
    glDisable(GL_DEPTH_TEST);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Activate simple shading program
    mShader->use();

    // Set up the model and projection matrix
    glm::mat4 model_matrix = glm::mat4(1.0f);
    model_matrix           = glm::translate(model_matrix, glm::vec3(0.0f, 0.0f, -5.0f)) *
                   glm::rotate(model_matrix, glm::radians(t * 360.0f), Y) *
                   glm::rotate(model_matrix, glm::radians(t * 720.0f), Z);
    glm::mat4 projection_matrix(glm::frustum(-1.0f, 1.0f, -aspect, aspect, 1.0f, 500.0f));

    mShader->setMat4("model_matrix", model_matrix);
    mShader->setMat4("projection_matrix", projection_matrix);

    // Set up for a glDrawElements call
    glBindVertexArray(vao[0]);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo[0]);

#if USE_PRIMITIVE_RESTART
    // When primitive restart is on, we can call one draw command
    glEnable(GL_PRIMITIVE_RESTART);
    glPrimitiveRestartIndex(0xFFFF);
    glDrawElements(GL_TRIANGLE_STRIP, 17, GL_UNSIGNED_SHORT, NULL);
#else
    // Without primitive restart, we need to call two draw commands
    glDrawElements(GL_TRIANGLE_STRIP, 8, GL_UNSIGNED_SHORT, NULL);
    // glDrawElements(GL_TRIANGLE_STRIP, 8, GL_UNSIGNED_SHORT, (const GLvoid *)(9 * sizeof(GLushort)));
#endif
}

void Scene1_4::ImguiRendering()
{
}

void Scene1_4::OnResize(int width, int height)
{
    DEBUG_PRINTF("SCENE1_2 : RESIZE width = %i height = %i \n", width, height);
    glViewport(0, 0, width, height);
    aspect = float(height) / float(width);
}

void Scene1_4::OnKey(int key, int scancode, int action, int mods)
{
    if (action == GLFW_PRESS || action == GLFW_REPEAT)
    {
        // LogMessage("GLFW EVENT:" + key);
        switch (key)
        {
        case GLFW_KEY_W:
        {
            mCamera.moveForward(mDeltaTime);
            break;
        }
        case GLFW_KEY_S:
        {
            mCamera.moveBackward(mDeltaTime);
            break;
        }
        case GLFW_KEY_A:
        {
            mCamera.moveLeft(mDeltaTime);
            break;
        }
        case GLFW_KEY_D:
        {
            mCamera.moveRight(mDeltaTime);
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

void Scene1_4::OnMouseMove(double xposIn, double yposIn)
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
        mLastX      = xpos;
        mLastY      = ypos;
        mFirstMouse = false;
    }

    float xoffset = xpos - mLastX;
    float yoffset = mLastY - ypos;

    mLastX = xpos;
    mLastY = ypos;

    mCamera.rotate(xoffset, yoffset);
}

void Scene1_4::OnMouseButton(int button, int action, int mods)
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
