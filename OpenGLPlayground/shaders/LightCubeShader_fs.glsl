#version 330 core

out vec4 FragColor;

struct Light {
    vec3 ambient;
    vec3 diffuse;
};

uniform Light pointLight;

void main()
{
    FragColor = vec4(pointLight.ambient + pointLight.diffuse, 1.0f);
}
