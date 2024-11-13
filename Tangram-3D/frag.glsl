#version 330 core
out vec4 color;

in vec3 FragPos;  
in vec3 Normal;
in vec2 TexCoords; // Add texture coordinates

uniform vec3 lightPos; 
uniform vec3 viewPos;
uniform vec3 lightColor;
uniform vec3 objectColor;

uniform sampler2D texture1; // Texture sampler for texture support
uniform bool useTexture;    // Boolean to toggle texture usage

void main()
{
    // Ambient
    float ambientStrength = 0.1f;
    vec3 ambient = ambientStrength * lightColor;

    // Diffuse
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    // Specular
    float specularStrength = 0.5f;
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * lightColor;

    // Combine lighting components
    vec3 lighting = (ambient + diffuse + specular) * objectColor;

    // Apply texture if enabled
    vec3 texColor = texture(texture1, TexCoords).rgb; // Fetch texture color
    vec3 finalColor = useTexture ? (lighting * texColor) : lighting; // Blend texture with lighting

    color = vec4(finalColor, 1.0f); // Output final color
}