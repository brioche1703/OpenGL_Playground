#include "BasicMultipleCubesRP.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <vector>

#include <stbi/stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "VertexShader.h"
#include "FragmentShader.h"
#include "ShaderProgram.h"
#include "Buffer.h"
#include "VertexAttribute.h"
#include "VertexArrayObject.h"
#include "Texture.h"
#include "Window.h"
#include "Input.h"
#include "Camera.h"
#include "CubeMesh.h"

namespace Playground
{
void BasicMultipleCubesRP::Init()
{
    CubeMesh cube;

    VertexShader vertexShader("shaders/MultipleCubesShader_vs.glsl");
    FragmentShader fragmentShader("shaders/MultipleCubesShader_fs.glsl");

    _shaderProgram.AttachShader({vertexShader, fragmentShader});
    _shaderProgram.LinkProgram();

    vertexShader.Delete();
    fragmentShader.Delete();

    _VAO.Bind();
    _VBO.Bind(GL_ARRAY_BUFFER);
    _VBO.Data(GL_ARRAY_BUFFER, cube.GetSize(), &cube.GetVertices()[0], GL_STATIC_DRAW);
    VertexAttribute vertexAttrib;
    vertexAttrib.SetAttributePointer(glVertexAttribPointer, 0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
    vertexAttrib.Enable(0);
    vertexAttrib.SetAttributePointer(glVertexAttribPointer, 1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float),
                                     (void *)(3 * sizeof(float)));
    vertexAttrib.Enable(1);

    glEnable(GL_DEPTH_TEST);
}

void BasicMultipleCubesRP::Draw(const std::unique_ptr<Window> &window, const std::unique_ptr<Camera> &camera)
{
    glm::vec3 cubePositions[] = {glm::vec3(0.0f, 0.0f, 0.0f),    glm::vec3(2.0f, 5.0f, -15.0f),
                                 glm::vec3(-1.5f, -2.2f, -2.5f), glm::vec3(-3.8f, -2.0f, -12.3f),
                                 glm::vec3(2.4f, -0.4f, -3.5f),  glm::vec3(-1.7f, 3.0f, -7.5f),
                                 glm::vec3(1.3f, -2.0f, -2.5f),  glm::vec3(1.5f, 2.0f, -2.5f),
                                 glm::vec3(1.5f, 0.2f, -1.5f),   glm::vec3(-1.3f, 1.0f, -1.5f)};

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::mat4 view = camera->LookAt();

    glm::mat4 projection(1.0f);
    projection = glm::perspective(glm::radians(camera->GetFov()),
                                  (float)window->GetWidth() / (float)window->GetHeight(), 0.1f, 100.0f);

    _shaderProgram.Use();
    _shaderProgram.SetUniformLocation(glUniform1i, "texture1", 0);
    _shaderProgram.SetUniformLocation(glUniform1i, "texture2", 1);
    _shaderProgram.SetUniformLocation(glUniformMatrix4fv, "view", 1, GL_FALSE, glm::value_ptr(view));
    _shaderProgram.SetUniformLocation(glUniformMatrix4fv, "projection", 1, GL_FALSE, glm::value_ptr(projection));

    _texture1.Activate(GL_TEXTURE0);
    _texture1.Bind();
    _texture2.Activate(GL_TEXTURE1);
    _texture2.Bind();

    _VAO.Bind();

    for (int i = 0; i < 10; i++)
    {
        glm::mat4 model(1.0f);
        model = glm::translate(model, cubePositions[i]);
        model = glm::rotate(model, (float)glfwGetTime() * glm::radians(20.0f * i), glm::vec3(1.0f, 0.3f, 0.5f));

        _shaderProgram.SetUniformLocation(glUniformMatrix4fv, "model", 1, GL_FALSE, glm::value_ptr(model));

        glDrawArrays(GL_TRIANGLES, 0, 36);
    }
}

void BasicMultipleCubesRP::Clear()
{
    _VAO.Delete();
    _VBO.Delete();
    _shaderProgram.Delete();
}
} // namespace Playground
