#version 330 core
out vec4 color;

in vec3 FragPos;  
in vec3 Normal;
in vec2 TexCoords;

uniform vec3 lightPos; 
uniform vec3 viewPos;
uniform vec3 lightColor;
uniform vec3 objectColor; // Use this as the overlay color

uniform sampler2D texture1; // Texture sampler
uniform bool useTexture;    // Toggle for texture usage

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
    vec3 lighting = (ambient + diffuse + specular);

    // Fetch texture color
    vec3 texColor = texture(texture1, TexCoords).rgb;

    vec3 blendedColor = texColor * lighting;
    vec3 finalColor = useTexture 
        ? mix(blendedColor, blendedColor * objectColor, 0.75) 
        : lighting * objectColor;

    color = vec4(finalColor, 1.0f); // Output the final color
}