#version 330 core

struct Material {
    sampler2D diffuse;
    sampler2D specular;
    sampler2D emissive;
    float shininess;
};

struct PointLight {
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;
};

struct DirectionalLight {
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

out vec4 FragColor;

in vec3 fragPos;
in vec3 normal;
in vec2 texCoords;

uniform vec3 viewPosition;
uniform DirectionalLight directionalLight;
uniform PointLight pointLight;
uniform Material material;

void main()
{
    // Ambient
    vec3 ambient = pointLight.ambient * vec3(texture(material.diffuse, texCoords));

    // Directional
    vec3 directinalLightDirection = normalize(pointLight.position);
    float diffuseFactor = max(dot(normalize(normal), directinalLightDirection), 0.0f);
    vec3 diffuse = pointLight.diffuse * diffuseFactor * vec3(texture(material.diffuse, texCoords));


    // Specular
    vec3 viewDirection = normalize(viewPosition - fragPos);
    vec3 reflectedDirection = reflect(-directinalLightDirection, normal);
    float spec = pow(max(dot(viewDirection, reflectedDirection), 0.0f), material.shininess);
    vec3 specular = vec3(texture(material.specular, texCoords)) * spec * pointLight.specular;

    // Emission
    vec3 emissive = texture(material.emissive, texCoords).rgb;

    // Point Light
    float distance = length(pointLight.position - fragPos);
    float attenuation = 1 / (pointLight.constant + pointLight.linear * distance + pointLight.quadratic * distance * distance);

    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;

    vec3 result = ambient + diffuse + specular + emissive;

    FragColor = vec4(result, 1.0f);
}
