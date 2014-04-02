#version 130 
in   vec4 vPosition;
in   vec3 vNormal;

// output values that will be interpretated per-fragment
out  vec3 fN;
out  vec3 fE;
out  vec3 fL1;
out  vec3 fL2;

uniform mat4 ModelView;
uniform vec4 Light1Position;
uniform vec4 Light2Position;
uniform mat4 Projection;

void main()
{
    fN = vNormal;
    fE = (ModelView*vPosition).xyz;
    fL1 = Light1Position.xyz;
	fL2 = Light2Position.xyz;
    
    if( Light1Position.w != 0.0 ) {
		fL1 = Light1Position.xyz - vPosition.xyz;
    }

	if( Light1Position.w != 0.0 ) {
		fL2 = Light1Position.xyz - vPosition.xyz;
    }

    gl_Position = Projection*ModelView*vPosition;
}
