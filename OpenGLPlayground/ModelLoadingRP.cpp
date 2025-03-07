#include "ModelLoadingRP.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stbi/stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "App.h"
#include "VertexShader.h"
#include "FragmentShader.h"
#include "Window.h"
#include "Input.h"
#include "Camera.h"
#include "GarbageCollection.h"

namespace Playground
{
void ModelLoadingRP::Init()
{
    glEnable(GL_DEPTH_TEST);

    VertexShader vertexShader("shaders/modelLoading_vs.glsl");
    FragmentShader fragmentShader("shaders/modelLoadingUnlit_fs.glsl");

    _shaderProgram.AttachShader({vertexShader, fragmentShader});
    _shaderProgram.LinkProgram();

    _model = Entity::Create<Model>("models/backpack/backpack.obj");

    vertexShader.Delete();
    fragmentShader.Delete();
}

void ModelLoadingRP::Draw(const std::unique_ptr<Window> &window, const std::unique_ptr<Camera> &camera)
{
    glClearColor(0.2f, 0.2f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Cube
    glm::mat4 model(1.0f);
    glm::mat4 view = camera->LookAt();
    glm::mat4 projection(1.0f);
    projection = glm::perspective(glm::radians(camera->GetFov()),
                                  (float)window->GetWidth() / (float)window->GetHeight(), 0.1f, 100.0f);

    _shaderProgram.Use();
    _shaderProgram.SetUniformLocation(glUniformMatrix4fv, "model", 1, GL_FALSE, glm::value_ptr(model));
    _shaderProgram.SetUniformLocation(glUniformMatrix4fv, "view", 1, GL_FALSE, glm::value_ptr(view));
    _shaderProgram.SetUniformLocation(glUniformMatrix4fv, "projection", 1, GL_FALSE, glm::value_ptr(projection));

    _model->Draw(_shaderProgram);
}

void ModelLoadingRP::Clear()
{
    _shaderProgram.Delete();
}
} // namespace Playground
