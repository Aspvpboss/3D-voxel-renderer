#version 430

out vec4 color;

in vec2 texCoord;
in vec3 fragPos;
in vec3 normalCoord;

uniform sampler2D samp;
uniform vec3 lightPos;
uniform vec3 lightColor;

void main(void){

	vec4 texColor = texture(samp, texCoord);
    // Every pixel on the face will use the exact same normal vector
    vec3 norm = normalize(normalCoord);
    vec3 lightDir = normalize(lightPos - fragPos);
    
    float diff = max(dot(norm, lightDir), 0.0);

    vec3 diffuse = diff * lightColor;
	vec3 ambient = vec3(0.1); // 10% ambient lighting

	vec3 rgb_value = (diffuse + ambient) * texColor.rgb;
    color = vec4(rgb_value, texColor.a); // 0.1 ambient
}