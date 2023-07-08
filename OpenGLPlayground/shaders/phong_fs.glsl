#version 330 core

out vec4 FragColor;

in vec3 normal;
in vec3 fragPos;

uniform vec3 lightPosition;
uniform vec3 viewPosition;

uniform vec3 lightColor;
uniform vec3 objectColor;

void main()
{
    // Ambient
    float ambientFactor = 0.1f;
    vec3 ambient = ambientFactor * lightColor;

    // Directional
    vec3 lightDirection = normalize(lightPosition - fragPos);
    float diffuseFactor = max(dot(normalize(normal), lightDirection), 0.0f);
    vec3 diffuse = diffuseFactor * lightColor;

    // Specular
    float specularFactor = 0.5f;
    float shininessFactor = 32.0f;
    vec3 viewDirection = normalize(viewPosition - fragPos);
    vec3 reflectedDirection = reflect(-lightDirection, normal);
    float spec = pow(max(dot(viewDirection, reflectedDirection), 0.0f), shininessFactor);
    vec3 specular = specularFactor * spec * lightColor;
    

    vec3 result = (ambient + diffuse + specular) * objectColor;

    FragColor = vec4(result, 1.0f);
}
