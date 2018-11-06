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

uniform sampler2D lightwood;
uniform sampler2D checker;

uniform Material material;
uniform bool dirLightEnabled;
uniform bool pointLightsEnabled;
uniform bool spotLightsEnabled;

uniform vec3 viewPos;
uniform DirLight dirLight;

out vec4 FragColor;

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;


vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir);

void main() {
	
    vec3 norm = normalize(Normal);
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 result = CalcDirLight(dirLight, norm, viewDir);

    vec4 spec = vec4(0.0);
    float intensity = max(dot(norm,dirLight.direction), 0.0);
    if (intensity > 0.0)
    {
        vec3 h = normalize(dirLight.direction + viewPos);
        float intSpec = max(dot(h,norm), 0.0);
        spec = vec4(material.specular,1.0) * pow(intSpec, material.shininess);
    }

	//FragColor = vec4(1.0,1.0,1.0 , 1.0);
    //FragColor = texture(lightwood, TexCoords);

    vec4 texel, texel1;
    texel = texture(lightwood, TexCoords);  // texel from lighwood.tga
    texel1 = texture(checker, TexCoords);  // texel from checker.tga
    //FragColor = 0.5*texel*texel1;
    FragColor = max(intensity*texel*texel1 + spec, 0.1*texel*texel1);
}

// calculates the color when using a directional light.
vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
    /*vec3 lightDir = normalize(-light.direction);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // combine results
    vec3 ambient = light.ambient * vec3(texture(texmap1, TexCoords));
    vec3 diffuse = light.diffuse * diff * vec3(texture(texmap1, TexCoords));
    vec3 specular = light.specular * spec * vec3(texture(texmap2, TexCoords));
    return (ambient + diffuse + specular);*/
    return vec3(1.0);
}