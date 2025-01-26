#pragma once

#include "SceneActor.h"

namespace Playground
{
class LightBase : public SceneActor
{
public:
    LightBase(const std::string &name)
        : SceneActor(name)
    {}

    inline glm::vec3 &GetAmbient() { return _ambient; }
    inline glm::vec3 &GetDiffuse() { return _diffuse; }
    inline glm::vec3 &GetSpecular() { return _specular; }
    inline float &GetConstant() { return _constant; }
    inline float &GetLinear() { return _linear; }
    inline float &GetQuadratic() { return _quadratic; }    

    inline void SetAmbient(const glm::vec3 &ambient) { _ambient = ambient; }
    inline void SetDiffuse(const glm::vec3 &diffuse) { _diffuse = diffuse; }
    inline void SetSpecular(const glm::vec3 &specular) { _specular = specular; }
    inline void SetConstant(float constant) { _constant = constant; }
    inline void SetLinear(float linear) { _linear = linear; }
    inline void SetQuadratic(float quadratic) { _quadratic = quadratic; }

private:
    glm::vec3 _ambient = glm::vec3(0.2f);
    glm::vec3 _diffuse = glm::vec3(0.5f);
    glm::vec3 _specular = glm::vec3(1.0f);

    float _constant = 1.0f;
    float _linear = 0.09f;
    float _quadratic = 0.032f;
};
}

