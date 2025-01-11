#include "LightingMapsRP.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <stbi/stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "VertexShader.h"
#include "FragmentShader.h"
#include "VertexAttribute.h"
#include "Texture.h"
#include "Window.h"
#include "Input.h"
#include "Camera.h"
#include "CubeMesh.h"
#include "Material.h"

namespace Playground
{
void LightingMaps::Init()
{
    CubeMesh cube;

    // Cube
    VertexShader vertexShader("shaders/shader_vs.glsl");
    FragmentShader fragmentShader("shaders/phong_lightingMaps_fs.glsl");

    _shaderProgram.AttachShader({vertexShader, fragmentShader});
    _shaderProgram.LinkProgram();

    vertexShader.Delete();
    fragmentShader.Delete();

    _VAO.Bind();
    _VBO.Bind(GL_ARRAY_BUFFER);
    _VBO.Data(GL_ARRAY_BUFFER, cube.GetSizeWithNormalsAndTexCoords(), &cube.GetVerticesWithNormalsAndTexCoords()[0],
              GL_STATIC_DRAW);
    VertexAttribute vertexAttrib;
    vertexAttrib.SetAttributePointer(glVertexAttribPointer, 0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)0);
    vertexAttrib.Enable(0);
    vertexAttrib.SetAttributePointer(glVertexAttribPointer, 1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
                                     (void *)(3 * sizeof(float)));
    vertexAttrib.Enable(1);
    vertexAttrib.SetAttributePointer(glVertexAttribPointer, 2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
                                     (void *)(6 * sizeof(float)));
    vertexAttrib.Enable(2);

    // Light
    VertexShader lightCubeVertexShader("shaders/shader_vs.glsl");
    FragmentShader lightCubeFragmentShader("shaders/LightCubeShader_fs.glsl");

    _lightCubeShaderProgram.AttachShader({lightCubeVertexShader, lightCubeFragmentShader});
    _lightCubeShaderProgram.LinkProgram();

    lightCubeVertexShader.Delete();
    lightCubeFragmentShader.Delete();

    _VAOLight.Bind();

    _VBO.Bind(GL_ARRAY_BUFFER);
    _VBO.Data(GL_ARRAY_BUFFER, cube.GetSizeWithNormalsAndTexCoords(), &cube.GetVerticesWithNormalsAndTexCoords()[0],
              GL_STATIC_DRAW);
    VertexAttribute vertexAttribLight;
    vertexAttribLight.SetAttributePointer(glVertexAttribPointer, 0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
                                          (void *)0);
    vertexAttribLight.Enable(0);

    glEnable(GL_DEPTH_TEST);
}

void LightingMaps::Draw(const std::unique_ptr<Window> &window, const std::unique_ptr<Camera> &camera)
{
    glClearColor(0.2f, 0.2f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    const float radius = 6.0f;
    light._position = glm::vec3(cos(glfwGetTime()) * radius, 0.5f, sin(glfwGetTime()) * radius);

    // Cube
    glm::mat4 model(1.0f);
    glm::mat4 view = camera->LookAt();
    glm::mat4 projection(1.0f);
    projection = glm::perspective(glm::radians(camera->GetFov()),
                                  (float)window->GetWidth() / (float)window->GetHeight(), 0.1f, 100.0f);

    _shaderProgram.Use();
    _shaderProgram.SetUniformLocation(glUniformMatrix4fv, "view", 1, GL_FALSE, glm::value_ptr(view));
    _shaderProgram.SetUniformLocation(glUniformMatrix4fv, "projection", 1, GL_FALSE, glm::value_ptr(projection));
    _shaderProgram.SetUniformLocation(glUniformMatrix4fv, "model", 1, GL_FALSE, glm::value_ptr(model));

    _shaderProgram.SetUniformLocation(glUniform3fv, "viewPosition", 1, glm::value_ptr(camera->GetPosition()));

    _shaderProgram.SetUniformLocation(glUniform1i, "material.diffuse", 0);
    _shaderProgram.SetUniformLocation(glUniform1i, "material.specular", 1);
    _shaderProgram.SetUniformLocation(glUniform1i, "material.emissive", 2);
    _shaderProgram.SetUniformLocation(glUniform3fv, "material.specular", 1, glm::value_ptr(material._specular));
    _shaderProgram.SetUniformLocation(glUniform1f, "material.shininess", material._shininess);

    _shaderProgram.SetUniformLocation(glUniform3fv, "light.position", 1, glm::value_ptr(light._position));
    _shaderProgram.SetUniformLocation(glUniform3fv, "light.ambient", 1, glm::value_ptr(light._ambient));
    _shaderProgram.SetUniformLocation(glUniform3fv, "light.diffuse", 1, glm::value_ptr(light._diffuse));
    _shaderProgram.SetUniformLocation(glUniform3fv, "light.specular", 1, glm::value_ptr(light._specular));

    _textureContainer.Activate(GL_TEXTURE0);
    _textureContainer.Bind();
    _textureContainerSpecular.Activate(GL_TEXTURE1);
    _textureContainerSpecular.Bind();
    _textureContainerEmissive.Activate(GL_TEXTURE2);
    _textureContainerEmissive.Bind();

    _VAO.Bind();
    glDrawArrays(GL_TRIANGLES, 0, 36);

    // Light object
    model = glm::translate(model, light._position);
    model = glm::scale(model, glm::vec3(0.2f));

    _lightCubeShaderProgram.Use();
    _lightCubeShaderProgram.SetUniformLocation(glUniformMatrix4fv, "view", 1, GL_FALSE, glm::value_ptr(view));
    _lightCubeShaderProgram.SetUniformLocation(glUniformMatrix4fv, "projection", 1, GL_FALSE,
                                               glm::value_ptr(projection));
    _lightCubeShaderProgram.SetUniformLocation(glUniformMatrix4fv, "model", 1, GL_FALSE, glm::value_ptr(model));
    _lightCubeShaderProgram.SetUniformLocation(glUniform3fv, "light.ambient", 1, glm::value_ptr(light._ambient));
    _lightCubeShaderProgram.SetUniformLocation(glUniform3fv, "light.diffuse", 1, glm::value_ptr(light._diffuse));

    _VAOLight.Bind();
    glDrawArrays(GL_TRIANGLES, 0, 36);
}

void LightingMaps::Clear()
{
    _VAO.Delete();
    _VBO.Delete();
    _shaderProgram.Delete();
}
} // namespace Playground
