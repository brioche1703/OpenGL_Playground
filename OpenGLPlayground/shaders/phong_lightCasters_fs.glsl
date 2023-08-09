#version 330 core

struct Material {
    sampler2D diffuse;
    sampler2D specular;
    sampler2D emissive;
    float shininess;
};

struct DirectionalLight {
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
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

struct SpotLight {
    vec3 position;
    vec3 direction;
    float cutOffAngle;
    float outerCutOffAngle;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;
};

out vec4 FragColor;

in vec3 fragPos;
in vec3 normal;
in vec2 texCoords;

uniform vec3 viewPosition;

uniform DirectionalLight directionalLight;

uniform int numberOfPointLight;

#define MAX_LIGHTS_NUMBER 10
uniform PointLight pointLights[MAX_LIGHTS_NUMBER];
uniform SpotLight spotLight;

uniform Material material;

vec3 CalculateDirLight(DirectionalLight light, vec3 normal, vec3 viewDirection);
vec3 CalculatePointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDirection);
vec3 CalculateSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDirection);

void main()
{
    vec3 norm = normalize(normal);
    vec3 viewDirection = normalize(viewPosition - fragPos);

    vec3 result = CalculateDirLight(directionalLight, norm, viewDirection);

    for (int i = 0; i < numberOfPointLight; i++)
    {
        result += CalculatePointLight(pointLights[i], norm, fragPos, viewDirection);
    }

    result += CalculateSpotLight(spotLight, norm, fragPos, viewDirection);

    FragColor = vec4(result, 1.0f);
}

vec3 CalculateDirLight(DirectionalLight light, vec3 normal, vec3 viewDirection)
{
    vec3 lightDir = normalize(-light.direction);

    float diffuseFactor = max(dot(normal, lightDir), 0.0f);

    vec3 reflectedDirection = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDirection, reflectedDirection), 0.0f), material.shininess);

    vec3 ambient = light.ambient * vec3(texture(material.diffuse, texCoords));
    vec3 diffuse = light.diffuse * diffuseFactor * vec3(texture(material.diffuse, texCoords));
    vec3 specular = light.specular * spec * vec3(texture(material.specular, texCoords));

    return ambient + diffuse + specular;
}

vec3 CalculatePointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDirection)
{
    vec3 lightDir = normalize(light.position - fragPos);

    float diffuseFactor = max(dot(normal, lightDir), 0.0f);

    vec3 reflectedDirection = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDirection, reflectedDirection), 0.0f), material.shininess);

    float distance = length(light.position - fragPos);
    float attenuation = 1.0f / (light.constant + light.linear * distance + light.quadratic * distance * distance);

    vec3 ambient = light.ambient * vec3(texture(material.diffuse, texCoords));
    vec3 diffuse = light.diffuse * diffuseFactor * vec3(texture(material.diffuse, texCoords));
    vec3 specular = light.specular * spec * vec3(texture(material.specular, texCoords));

    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;

    return ambient + diffuse + specular;
}

vec3 CalculateSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDirection)
{
    vec3 lightDir = normalize(light.position - fragPos);

    float diffuseFactor = max(dot(normal, lightDir), 0.0f);

    vec3 reflectedDirection = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDirection, reflectedDirection), 0.0f), material.shininess);

    float distance = length(light.position - fragPos);
    float attenuation = 1.0f / (light.constant + light.linear * distance + light.quadratic * distance * distance);

    vec3 ambient = light.ambient * vec3(texture(material.diffuse, texCoords));
    vec3 diffuse = light.diffuse * diffuseFactor * vec3(texture(material.diffuse, texCoords));
    vec3 specular = light.specular * spec * vec3(texture(material.specular, texCoords));

    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;

    return ambient + diffuse + specular;
    float theta = dot(lightDir, normalize(-light.direction));
    float epsilon = light.cutOffAngle - light.outerCutOffAngle;
    float intensity = clamp((theta - light.outerCutOffAngle) / epsilon, 0.0f, 1.0f);

    ambient *= intensity;
    diffuse *= intensity;
    specular *= intensity;

    return ambient + diffuse + specular;
}
