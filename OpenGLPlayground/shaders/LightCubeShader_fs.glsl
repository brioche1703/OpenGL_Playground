#version 330 core

out vec4 FragColor;

struct Light {
    vec3 ambient;
    vec3 diffuse;
};

uniform Light light;

void main()
{
    FragColor = vec4(light.ambient + light.diffuse, 1.0f);
}
