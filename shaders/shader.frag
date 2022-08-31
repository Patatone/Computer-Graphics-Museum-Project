#version 450

layout(set = 1, binding = 1) uniform sampler2D texSampler;

layout(location = 0) in vec3 fragViewDir;
layout(location = 1) in vec3 fragNorm;
layout(location = 2) in vec2 fragTexCoord;

layout(location = 0) out vec4 outColor;

void main() {
	const vec3  diffColor = texture(texSampler, fragTexCoord).rgb;
	const vec3  specColor = vec3(1.0f, 1.0f, 1.0f);
	const float specPower = 150.0f;
	const vec3  L = vec3(-0.4830f, 0.8365f, -0.2588f);
	
	vec3 N = normalize(fragNorm);
	vec3 R = -reflect(L, N);
	vec3 V = normalize(fragViewDir);
	
	// LAMBERT (diffuse reflection model)
	// Has only the diffuse part, which corresponds to a constant term
	// Each point of the object hit by a ray reflect it with uniform probability in all directions
	// N.B: the quantity of light is not costant but is proportional to the angle between the ray 
	// and the normal vector of the x point (depends on the reflecting surface)
	vec3 diffuse  = diffColor * max(dot(N,L), 0.0f);
	
	// PHONG (specular reflection model)
	// Specular reflection has same angle of incoming light ray w.r.t normal vector but oriented in opposite direction \|/
	// also the sirection of the viewer is considered. In particular we are interested in the cosin of the angle between 
	// the direction of the viewer and the direction of the reflection.
	// This parameter enstablish the intensity of the specular reflection ( max reflection when viewer aligned with reflection direction, zero when 90 degree)
	vec3 specular = specColor * pow(max(dot(R,V), 0.0f), specPower);
	
	// Hemispheric ambient
	vec3 ambient  = (vec3(0.1f,0.1f, 0.1f) * (1.0f + N.y) + vec3(0.0f,0.0f, 0.1f) * (1.0f - N.y)) * diffColor;
	
	outColor = vec4(clamp(ambient + diffuse + specular, vec3(0.0f), vec3(1.0f)), 1.0f);
}