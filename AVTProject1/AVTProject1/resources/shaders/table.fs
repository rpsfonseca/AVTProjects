#version 330 core

//uniform sampler2D checker;
//uniform sampler2D lightwood;

struct DirLight {
    vec3 direction;
    
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct Material {
    vec3 diffuse;
    vec3 ambient;
    vec3 specular;
    float shininess;
};

struct PointLight {
    vec3 position;
    
    float constant;
    float linear;
    float quadratic;
    
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct SpotLight {
    vec3 position;
    vec3 direction;
    float cutOff;
    float outerCutOff;
  
    float constant;
    float linear;
    float quadratic;
  
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;       
};

#define NR_POINT_LIGHTS 6

uniform sampler2D lightwood;
uniform sampler2D checker;

uniform Material material;
uniform bool dirLightEnabled;
uniform bool pointLightsEnabled;
uniform bool spotLightsEnabled;

uniform vec3 viewPos;
uniform DirLight dirLight;
uniform PointLight pointLights[NR_POINT_LIGHTS];
uniform SpotLight spotLight;
uniform SpotLight spotLight2;

const vec3 RimColor = vec3(0.2, 0.2, 0.2);
const vec3 fogColor = vec3(0.5, 0.5,0.5);

out vec4 FragColor;

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;
in vec3 world_normal;
in vec4 viewSpace;


vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir);
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir);

void main() {
	
    vec3 norm = normalize(Normal);
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 result = CalcDirLight(dirLight, norm, viewDir);

    // == =====================================================
    // Our lighting is set up in 3 phases: directional, point lights and an optional flashlight
    // For each phase, a calculate function is defined that calculates the corresponding color
    // per lamp. In the main() function we take all the calculated colors and sum them up for
    // this fragment's final color.
    // == =====================================================
    // phase 1: directional lighting
    if(dirLightEnabled)
    {
        result += CalcDirLight(dirLight, norm, viewDir);
    }
    // phase 2: point lights
    if(pointLightsEnabled)
    {
        for(int i = 0; i < NR_POINT_LIGHTS; i++)
        {
            result += CalcPointLight(pointLights[i], norm, FragPos, viewDir);
        }
    }
    // phase 3: spot light
    if(spotLightsEnabled)
    {
        result += CalcSpotLight(spotLight, norm, FragPos, viewDir);
        result += CalcSpotLight(spotLight2, norm, FragPos, viewDir);
    }

    //rim lighting
    float rim = 1 - max(dot(viewDir, world_normal), 0.0);
    rim = smoothstep(0.6, 1.0, rim);
    vec3 finalRim = RimColor * vec3(rim, rim, rim);
    //get all lights and texture
    result += finalRim;
     
    vec3 finalColor = vec3(0, 0, 0);
     
    //compute range based distance
    float dist = length(viewSpace);
     
    //my camera y is 10.0. you can change it or pass it as a uniform
    float be = (viewPos.y - viewSpace.y) * 0.004;//0.004 is just a factor; change it if you want
    float bi = (viewPos.y - viewSpace.y) * 0.001;//0.001 is just a factor; change it if you want
     
    float ext = exp(-dist * be);
    float insc = exp(-dist * bi);
    
    float fogFactor = 0;
    fogFactor = 1.0 /exp( (dist * 0.05)* (dist * 0.05));
    fogFactor = clamp( fogFactor, 0.0, 1.0 );
 
    finalColor = mix(fogColor, result, fogFactor);
     
    //finalColor = result * ext + vec3(0.5, 0.5,0.5) * (1 - insc);
    
    FragColor = vec4(finalColor, 0.25);

    /*vec4 spec = vec4(0.0);
    float intensity = max(dot(norm, dirLight.direction), 0.0);
    if (intensity > 0.0)
    {
        vec3 h = normalize(dirLight.direction + viewPos);
        float intSpec = max(dot(h,norm), 0.0);
        spec = vec4(material.specular,1.0) * pow(intSpec, material.shininess);
    }


    vec4 texel, texel1;
    texel = texture(lightwood, TexCoords);  // texel from lighwood.tga
    texel1 = texture(checker, TexCoords);  // texel from checker.tga
    //FragColor = vec4(1.0,1.0,1.0 , 1.0);
    //FragColor = texture(lightwood, TexCoords);
    //FragColor = 0.5*texel*texel1;
    FragColor = max(intensity*texel*texel1 + spec, 0.1*texel*texel1);
    FragColor = max(vec4(result, 1.0)*texel*texel1, 0.1*texel*texel1);*/
}

// calculates the color when using a directional light.
vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
    vec3 lightDir = normalize(-light.direction);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // combine results
    vec3 ambient = light.ambient * vec3(texture(lightwood, TexCoords) * texture(checker, TexCoords));
    vec3 diffuse = light.diffuse * diff * vec3(texture(lightwood, TexCoords) * texture(checker, TexCoords));
    vec3 specular = light.specular * spec * vec3(texture(lightwood, TexCoords) * texture(checker, TexCoords));
    return (ambient + diffuse + specular);
    //return vec3(1.0);
}

// calculates the color when using a point light.
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 halfwayDir = normalize(lightDir + viewDir);
    float spec = pow(max(dot(normal, halfwayDir), 0.0), material.shininess);
    // attenuation
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));    
    // combine results
    vec3 ambient = light.ambient * material.ambient;
    vec3 diffuse = light.diffuse * diff * material.diffuse;
    vec3 specular = light.specular * spec * material.specular;
    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;
    return (ambient + diffuse + specular);
}

// calculates the color when using a spot light.
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 halfwayDir = normalize(lightDir + viewDir);
    float spec = pow(max(dot(normal, halfwayDir), 0.0), material.shininess);
    // attenuation
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));    
    // spotlight intensity
    float theta = dot(lightDir, normalize(-light.direction)); 
    float epsilon = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);
    // combine results
    vec3 ambient = light.ambient * material.ambient;
    vec3 diffuse = light.diffuse * diff * material.diffuse;
    vec3 specular = light.specular * spec * material.specular;
    ambient *= attenuation * intensity;
    diffuse *= attenuation * intensity;
    specular *= attenuation * intensity;
    return (ambient + diffuse + specular);
}