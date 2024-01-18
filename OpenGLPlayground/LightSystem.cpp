#include "LightSystem.h"

#include "PointLight.h"
#include "SpotLight.h"
#include "ShaderProgram.h"
#include "VertexShader.h"
#include "VertexAttribute.h"
#include "FragmentShader.h"
#include "CubeMesh.h"

#include <glm\gtc\type_ptr.hpp>

namespace Playground
{
LightSystem::LightSystem(std::vector<PointLight> pointLights)
    : _pointLights(pointLights)
{
    _spotLights.push_back(SpotLight());
}

void LightSystem::Init()
{
    CubeMesh cube;

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
}

void LightSystem::SetUniforms(const ShaderProgram &shaderProgram, const glm::mat4 &view, const glm::mat4 &proj)
{
    shaderProgram.SetUniformLocation(glUniform3fv, "directionalLight.direction", 1,
                                     glm::value_ptr(_directionalLight._direction));
    shaderProgram.SetUniformLocation(glUniform3fv, "directionalLight.ambient", 1,
                                     glm::value_ptr(_directionalLight._ambient));
    shaderProgram.SetUniformLocation(glUniform3fv, "directionalLight.diffuse", 1,
                                     glm::value_ptr(_directionalLight._diffuse));
    shaderProgram.SetUniformLocation(glUniform3fv, "directionalLight.specular", 1,
                                     glm::value_ptr(_directionalLight._specular));

    shaderProgram.SetUniformLocation(glUniform1i, "numberOfPointLight", (GLint)_pointLights.size());

    for (int i = 0; i < _pointLights.size(); i++)
    {
        shaderProgram.SetUniformLocation(glUniform3fv, "pointLights[" + std::to_string(i) + "].position", 1,
                                         glm::value_ptr(_pointLights[i]._position));
        shaderProgram.SetUniformLocation(glUniform3fv, "pointLights[" + std::to_string(i) + "].ambient", 1,
                                         glm::value_ptr(_pointLights[i]._ambient));
        shaderProgram.SetUniformLocation(glUniform3fv, "pointLight[" + std::to_string(i) + "].diffuse", 1,
                                         glm::value_ptr(_pointLights[i]._diffuse));
        shaderProgram.SetUniformLocation(glUniform3fv, "pointLights[" + std::to_string(i) + "]specular", 1,
                                         glm::value_ptr(_pointLights[i]._specular));
        shaderProgram.SetUniformLocation(glUniform1f, "pointLights[" + std::to_string(i) + "].constant",
                                         _pointLights[i]._constant);
        shaderProgram.SetUniformLocation(glUniform1f, "pointLights[" + std::to_string(i) + "].linear",
                                         _pointLights[i]._linear);
        shaderProgram.SetUniformLocation(glUniform1f, "pointLights[" + std::to_string(i) + "].quadratic",
                                         _pointLights[i]._quadratic);
    }

    shaderProgram.SetUniformLocation(glUniform3fv, "spotLight.position", 1, glm::value_ptr(_spotLights[0]._position));
    shaderProgram.SetUniformLocation(glUniform3fv, "spotLight.direction", 1, glm::value_ptr(_spotLights[0]._direction));
    shaderProgram.SetUniformLocation(glUniform1f, "spotLight.cutOffAngle", _spotLights[0]._cutOffAngle);
    shaderProgram.SetUniformLocation(glUniform1f, "spotLight.outerCutOffAngle", _spotLights[0]._outerCutOffAngle);
    shaderProgram.SetUniformLocation(glUniform3fv, "spotLight.ambient", 1, glm::value_ptr(_spotLights[0]._ambient));
    shaderProgram.SetUniformLocation(glUniform3fv, "spotLight.diffuse", 1, glm::value_ptr(_spotLights[0]._diffuse));
    shaderProgram.SetUniformLocation(glUniform3fv, "spotLight.specular", 1, glm::value_ptr(_spotLights[0]._specular));
    shaderProgram.SetUniformLocation(glUniform1f, "spotLight.constant", _spotLights[0]._constant);
    shaderProgram.SetUniformLocation(glUniform1f, "spotLight.linear", _spotLights[0]._linear);
    shaderProgram.SetUniformLocation(glUniform1f, "spotLight.quadratic", _spotLights[0]._quadratic);
}

void LightSystem::DrawLightsObjects(const glm::mat4 &view, const glm::mat4 &proj)
{
    for (size_t i = 0; i < _pointLights.size(); i++)
    {
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, _pointLights[i]._position);
        model = glm::scale(model, glm::vec3(0.2f));

        _lightCubeShaderProgram.Use();
        _lightCubeShaderProgram.SetUniformLocation(glUniformMatrix4fv, "view", 1, GL_FALSE, glm::value_ptr(view));
        _lightCubeShaderProgram.SetUniformLocation(glUniformMatrix4fv, "projection", 1, GL_FALSE, glm::value_ptr(proj));
        _lightCubeShaderProgram.SetUniformLocation(glUniformMatrix4fv, "model", 1, GL_FALSE, glm::value_ptr(model));
        _lightCubeShaderProgram.SetUniformLocation(glUniform3fv, "pointLight.position", 1,
                                                   glm::value_ptr(_pointLights[i]._position));
        _lightCubeShaderProgram.SetUniformLocation(glUniform3fv, "pointLight.ambient", 1,
                                                   glm::value_ptr(_pointLights[i]._ambient));
        _lightCubeShaderProgram.SetUniformLocation(glUniform3fv, "pointLight.diffuse", 1,
                                                   glm::value_ptr(_pointLights[i]._diffuse));

        _VAOLight.Bind();
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }
}
} // namespace Playground
