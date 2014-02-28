#version 130

// in vec4 vPosition;
// in vec3 vNormal;
// out vec4 color;

// uniform vec4 AmbientProduct, DiffuseProduct, SpecularProduct;
// uniform mat4 ModelView;
// uniform mat4 Projection;
// uniform vec4 LightPosition;
// uniform float Shininess;

// void main(){
//      vec3 pos = (ModelView * vPosition).xyz;
     
//      vec3 L = normalize(LightPosition.xyz - pos);
//      vec3 E = normalize(-pos);
//      vec3 H = normalize(L + E);

//      vec3 N = normalize(ModelView * vec4(vNormal, 0.0)).xyz;

//      vec4 ambient = AmbientProduct;
//      float Kd = max(dot(L, N), 0.0);
//      vec4 diffuse = Kd*DiffuseProduct;
//      float Ks = pow(max(dot(N, H), 0.0), Shininess);
//      vec4 specular = Ks*SpecularProduct;
//      if (dot(L, N) < 0.0) specular = vec4(0.0, 0.0, 0.0, 1.0);

//      gl_Position = Projection * ModelView * vPosition;

//      color = ambient + diffuse + specular;
//      color.a = 1.0;
// }
	
uniform mat4 Matrix;
uniform mat4 viewMatrix;
uniform mat4 modelMatrix;

in vec3 in_position;
in vec4 in_color;
out vec4 pass_color;

void main(){
     gl_Position=Matrix*viewMatrix*modelMatrix*vec4(in_position,1.0); 
     pass_color=in_color;
}