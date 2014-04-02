#version 130 
// per-fragment interpolated values from the vertex shader
in  vec3 fN;
in  vec3 fL1;
in  vec3 fL2;
in  vec3 fE;

out vec4 fColor;

uniform vec4 AmbientProduct1, DiffuseProduct1, SpecularProduct1;
uniform vec4 AmbientProduct2, DiffuseProduct2, SpecularProduct2;
uniform mat4 ModelView;
// uniform vec4 Light1Position;
// uniform vec4 Light2Position;
uniform float Shininess;

void main() 
{ 
    // Normalize the input lighting vectors
    vec3 N = normalize(fN);
    vec3 E = normalize(fE);
    vec3 L1 = normalize(fL1);
	vec3 L2 = normalize(fL2);

    vec3 H1 = normalize( L1 + E );
    vec3 H2 = normalize( L2 + E );
    
    vec4 ambient = AmbientProduct1 + AmbientProduct2;

    float Kd1 = max(dot(L1, N), 0.0);
    float Kd2 = max(dot(L2, N), 0.0);
    vec4 diffuse = Kd1*DiffuseProduct1 + Kd2*DiffuseProduct2;
    
    float Ks1 = pow(max(dot(N, H1), 0.0), Shininess);
    float Ks2 = pow(max(dot(N, H2), 0.0), Shininess);
    vec4 specular1 = Ks1*SpecularProduct1;
    vec4 specular2 = Ks2*SpecularProduct2;

    // discard the specular highlight if the light's behind the vertex
    if( dot(L1, N) < 0.0 ) {
		specular1 = vec4(0.0, 0.0, 0.0, 1.0);
    }

	if( dot(L2, N) < 0.0 ) {
		specular2 = vec4(0.0, 0.0, 0.0, 1.0);
    }

	vec4 specular = specular1 + specular2;

    fColor = ambient + diffuse + specular;
    fColor.a = 1.0;
} 

