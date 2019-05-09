#version 330 core

out vec4 FragColor;

struct Material {
    sampler2D diffuse;
    sampler2D specular;
    bool hasSpecularTexture;
    vec3 specularVector;
    float shininess;
}; 

struct DirLight {
    vec3 direction;
	
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;

uniform vec3 viewPos;
uniform DirLight dirLight;
uniform Material material;

// function prototypes
vec4 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir);

void main()
{
	// properties
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);
    
    // == =====================================================
    // Our lighting is set up in 3 phases: directional, point lights and an optional flashlight
    // For each phase, a calculate function is defined that calculates the corresponding color
    // per lamp. In the main() function we take all the calculated colors and sum them up for
    // this fragment's final color.
    // == =====================================================
    // phase 1: directional lighting
    vec4 result = CalcDirLight(dirLight, norm, viewDir);
    // phase 2: point lights
    //for(int i = 0; i < NR_POINT_LIGHTS; i++)
      //  result += CalcPointLight(pointLights[i], norm, FragPos, viewDir);    
    // phase 3: spot light
    //result += CalcSpotLight(spotLight, norm, FragPos, viewDir);    
    if (result.a == 0)
        discard;
    FragColor = vec4(result);
}

// calculates the color when using a directional light.
vec4 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
    vec3 lightDir = normalize(-light.direction);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // combine results
    vec4 ambient = vec4(light.ambient, 1.0) * vec4(texture(material.diffuse, TexCoords));
    vec4 diffuse = vec4(light.diffuse, 1.0) * diff * vec4(texture(material.diffuse, TexCoords));
    vec4 specular;
    if (material.hasSpecularTexture)
        specular = vec4(light.specular, 1.0) * spec * vec4(texture(material.specular, TexCoords));
    else
        specular = vec4(light.specular, 1.0) * (spec * vec4(material.specularVector, 0.0f));

    return (ambient + diffuse + specular);
}