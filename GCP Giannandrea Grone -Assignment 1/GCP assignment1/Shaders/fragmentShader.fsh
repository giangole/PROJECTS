#version 130

in vec3 fN;
in vec3 fL;

in vec3 fE;				

out vec4 fColor;

void main () {
	vec3 N = normalize(fN);
	vec3 L = normalize(fL);

	vec3 E = normalize(-fE);	
	vec3 H = normalize(L + E);	

	// Diffuse component
	float diffuse_intensity = max(dot(N, L), 0.001);
	//vec4 diffuse_final = diffuse_intensity*vec4(0.1, 0.5, 0.4, 1.0);		
	vec4 diffuse_final = diffuse_intensity*vec4(0.5, 0.6, 0.3, 1.0);

	// NEW! Specular component
	float spec_intensity = pow(max(dot(N, H), 0.0), 10);
	//vec4 spec_final = spec_intensity*vec4(0.7, 0.7, 0.2, 1.0);
	vec4 spec_final = spec_intensity*vec4(0.3, 0.2, 0.4, 1.0);
	
	fColor = diffuse_final + spec_final;
}