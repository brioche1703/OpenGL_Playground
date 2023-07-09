#version 330 core

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

struct Light {
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

out vec4 FragColor;

in vec3 normal;
in vec3 fragPos;

uniform vec3 viewPosition;

uniform Light light;

uniform Material material;

void main()
{
    // Ambient
    vec3 ambient = material.ambient * light.ambient;

    // Directional
    vec3 lightDirection = normalize(light.position - fragPos);
    float diffuseFactor = max(dot(normalize(normal), lightDirection), 0.0f);
    vec3 diffuse = diffuseFactor * material.diffuse * light.diffuse;

    // Specular
    vec3 viewDirection = normalize(viewPosition - fragPos);
    vec3 reflectedDirection = reflect(-lightDirection, normal);
    float spec = pow(max(dot(viewDirection, reflectedDirection), 0.0f), material.shininess);
    vec3 specular = material.specular * spec * light.specular;
    

    vec3 result = (ambient + diffuse + specular);

    FragColor = vec4(result, 1.0f);
}
