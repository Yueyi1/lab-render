#include "scenes.h"

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

void Scene1_2::Resize(int width, int height)
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
