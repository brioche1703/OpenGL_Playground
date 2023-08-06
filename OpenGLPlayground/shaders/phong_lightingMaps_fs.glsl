#version 330 core

struct Material {
    sampler2D diffuse;
    sampler2D specular;
    sampler2D emissive;
    float shininess;
};

struct Light {
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

out vec4 FragColor;

in vec3 fragPos;
in vec3 normal;
in vec2 texCoords;

uniform vec3 viewPosition;
uniform Light light;
uniform Material material;

void main()
{
    // Ambient
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, texCoords));

    // Directional
    vec3 lightDirection = normalize(light.position - fragPos);
    float diffuseFactor = max(dot(normalize(normal), lightDirection), 0.0f);
    vec3 diffuse = light.diffuse * diffuseFactor * vec3(texture(material.diffuse, texCoords));


    // Specular
    vec3 viewDirection = normalize(viewPosition - fragPos);
    vec3 reflectedDirection = reflect(-lightDirection, normal);
    float spec = pow(max(dot(viewDirection, reflectedDirection), 0.0f), material.shininess);
    vec3 specular = vec3(texture(material.specular, texCoords)) * spec * light.specular;

    // Emission
    vec3 emissive = texture(material.emissive, texCoords).rgb;

    vec3 result = ambient + diffuse + specular + emissive;

    FragColor = vec4(result, 1.0f);
}
