#include "ModelLoadingLitRP.h"

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
#include "ImGuiController.h"
#include "Input.h"
#include "Camera.h"
#include "GarbageCollection.h"

namespace Playground
{
void ModelLoadingLitRP::Init()
{
    glEnable(GL_DEPTH_TEST);

    glm::vec3 pointLightPositions[] = {glm::vec3(0.7f, 0.2f, 2.0f), glm::vec3(2.3f, -3.3f, -4.0f),
                                       glm::vec3(-4.0f, 2.0, -12.0), glm::vec3(0.0f, 0.0f, -3.0f)};

    std::vector<std::shared_ptr<PointLight>> pointLights;
    pointLights.reserve(pointLightPositions->length());
    pointLights.push_back(
        Entity::Create<PointLight>("PointLight1", pointLightPositions[0]));
    pointLights.push_back(
        Entity::Create<PointLight>("PointLight2", pointLightPositions[1]));
    pointLights.push_back(
        Entity::Create<PointLight>("PointLight3", pointLightPositions[2]));
    pointLights.push_back(
        Entity::Create<PointLight>("PointLight4", pointLightPositions[3]));

    _lightSystem = std::make_unique<LightSystem>(pointLights);

    VertexShader vertexShader("shaders/modelLoading_vs.glsl");
    FragmentShader fragmentShader("shaders/modelLoadingLit_fs.glsl");

    _shaderProgram.AttachShader({vertexShader, fragmentShader});
    _shaderProgram.LinkProgram();

    _model = Entity::Create<Model>("models/backpack/backpack.obj");

    vertexShader.Delete();
    fragmentShader.Delete();

    _lightSystem->Init();
}

void ModelLoadingLitRP::ImGuiMenu()
{
    ImGui::Begin("Settings");

    ImGui::Text("Entities:");
    ImGui::Spacing();
    static float posX, posY, posZ = 0.f;
    ImGui::SliderFloat("pos X", &posX, -100.0f, 100.0f, "ratio = %.3f");
    ImGui::SliderFloat("pos Y", &posY, -100.0f, 100.0f, "ratio = %.3f");
    ImGui::SliderFloat("pos Z", &posZ, -100.0f, 100.0f, "ratio = %.3f");
    _model->SetPosition(glm::vec3(posX, posY, posZ));

    static float lposX, lposY, lposZ = 0.f;
    ImGui::SliderFloat("lpos X", &lposX, -100.0f, 100.0f, "ratio = %.3f");
    ImGui::SliderFloat("lpos Y", &lposY, -100.0f, 100.0f, "ratio = %.3f");
    ImGui::SliderFloat("lpos Z", &lposZ, -100.0f, 100.0f, "ratio = %.3f");
    _lightSystem->_pointLights[0]->SetPosition(glm::vec3(lposX, lposY, lposZ));

    static float r, g, b, dr, dg, db, sr, sg, sb, c, l, q = 1.f;
    ImGui::SliderFloat("r", &r, 0.0f, 1.0f, "ratio = %.3f");
    ImGui::SliderFloat("g", &g, 0.0f, 1.0f, "ratio = %.3f");
    ImGui::SliderFloat("b", &b, 0.0f, 1.0f, "ratio = %.3f");
    ImGui::SliderFloat("dr", &r, 0.0f, 1.0f, "ratio = %.3f");
    ImGui::SliderFloat("dg", &g, 0.0f, 1.0f, "ratio = %.3f");
    ImGui::SliderFloat("db", &b, 0.0f, 1.0f, "ratio = %.3f");
    ImGui::SliderFloat("sr", &sr, 0.0f, 1.0f, "ratio = %.3f");
    ImGui::SliderFloat("sg", &sg, 0.0f, 1.0f, "ratio = %.3f");
    ImGui::SliderFloat("sb", &sb, 0.0f, 1.0f, "ratio = %.3f");
    ImGui::SliderFloat("c", &c, 0.0f, 1.0f, "ratio = %.3f");
    ImGui::SliderFloat("l", &l, 0.0f, 1.0f, "ratio = %.3f");
    ImGui::SliderFloat("q", &q, 0.0f, 1.0f, "ratio = %.3f");
    _lightSystem->_pointLights[0]->SetAmbient(glm::vec3(r, g, b));
    _lightSystem->_pointLights[0]->SetDiffuse(glm::vec3(dr, dg, db));
    _lightSystem->_pointLights[0]->SetSpecular(glm::vec3(sr, sg, sb));
    _lightSystem->_pointLights[0]->SetConstant(c);
    _lightSystem->_pointLights[0]->SetLinear(l);
    _lightSystem->_pointLights[0]->SetQuadratic(q);

    ImGui::End();
}

void ModelLoadingLitRP::Draw(const std::unique_ptr<Window> &window, const std::unique_ptr<Camera> &camera)
{
    glClearColor(0.2f, 0.2f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Cube
    glm::mat4 model = _model->GetModelMatrix();
    glm::mat4 view = camera->LookAt();
    glm::mat4 projection(1.0f);
    projection = glm::perspective(glm::radians(camera->GetFov()),
                                  (float)window->GetWidth() / (float)window->GetHeight(), 0.1f, 100.0f);

    _shaderProgram.Use();
    _shaderProgram.SetUniformLocation(glUniformMatrix4fv, "model", 1, GL_FALSE, glm::value_ptr(model));
    _shaderProgram.SetUniformLocation(glUniformMatrix4fv, "view", 1, GL_FALSE, glm::value_ptr(view));
    _shaderProgram.SetUniformLocation(glUniformMatrix4fv, "projection", 1, GL_FALSE, glm::value_ptr(projection));
    _shaderProgram.SetUniformLocation(glUniform3fv, "viewPosition", 1, glm::value_ptr(camera->GetPosition()));

    _lightSystem->SetUniforms(_shaderProgram, view, projection);

    _model->Draw(_shaderProgram);

    _lightSystem->DrawLightsObjects(view, projection);
}

void ModelLoadingLitRP::Clear()
{
    _shaderProgram.Delete();
}
} // namespace Playground
