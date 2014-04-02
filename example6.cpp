// fragment shading of sphere model

#include "Angel.h"

const int NumVertices = 8;

typedef Angel::vec4 point4;
typedef Angel::vec4 color4;

static point4 at( 0.0, 0.0, 0.0, 1.0 );
static point4 eye( 2.0, 2.0, 2.0, 1.0 );
static vec4   up( 0.0, 1.0, 0.0, 0.0 );

// Model-view and projection matrices uniform location
GLuint  ModelView, Projection;

GLfloat size=1;
GLfloat norm=1/sqrt(3.0);

GLfloat vertexarray[]={size, size, size,   //V0
					   -size, size, size,  //V1
					   -size, size, -size, //V2
					   size, size, -size,  //V3
					   size, -size, size,  //V4
					   -size, -size, size, //V5
					   -size, -size, -size,//V6
					   size, -size, -size  //V7
};
GLfloat normals_array[]={norm, norm, norm,   //V0
					   -norm, norm, norm,  //V1
					   -norm, norm, -norm, //V2
					   norm, norm, -norm,  //V3
					   norm, -norm, norm,  //V4
					   -norm, -norm, norm, //V5
					   -norm, -norm, -norm,//V6
					   norm, -norm, -norm  //V7
};

GLubyte elems[]={0, 1, 2,
				 2, 3, 0,
				 0, 3, 7,
				 7, 4, 0,
				 0, 4, 5,
				 5, 0, 1,
				 1, 2, 5,
				 5, 2, 6,
				 6, 2, 3,
				 3, 6, 7,
				 7, 6, 4,
				 4, 5, 6
				 
};

//----------------------------------------------------------------------------

// OpenGL initialization
void
init()
{
	GLuint vao, vbo, ebo;
	glGenVertexArrays( 1,&vao);
	glBindVertexArray( vao );

	glGenBuffers(1,&vbo);
	glBindBuffer(GL_ARRAY_BUFFER,vbo);
	glBufferData(GL_ARRAY_BUFFER,sizeof(vertexarray) + sizeof(normals_array),NULL,GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER,0,sizeof(vertexarray),vertexarray);
	glBufferSubData(GL_ARRAY_BUFFER,sizeof(vertexarray),sizeof(normals_array),normals_array);

	GLuint program = InitShader( "vshader56.glsl", "fshader56.glsl" );
	glUseProgram( program );

	GLuint vPosition = glGetAttribLocation(program, "vPosition" );
	glVertexAttribPointer(vPosition,3,GL_FLOAT,GL_FALSE,0,BUFFER_OFFSET(0));
	glEnableVertexAttribArray( vPosition );

	GLuint vNormal = glGetAttribLocation(program, "vNormal" );
	glVertexAttribPointer(vNormal,3,GL_FLOAT,GL_FALSE,0,BUFFER_OFFSET(sizeof(vertexarray)));
	glEnableVertexAttribArray( vNormal );

	glGenBuffers(1,&ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(elems),elems,GL_STATIC_DRAW);

	
	// Initialize shader lighting parameters
	point4 light1_position( 10.0, 10.0, 10.0, 0.0 );
	color4 light1_ambient( 0.3, 0.2, 0.2, 1.0 );
	color4 light1_diffuse( 0.9, 0.6, 0.6, 1.0 );
	color4 light1_specular( 1.0, 0.6, 0.6, 1.0 );

	point4 light2_position( -10.0, -10.0, -10.0, 0.0 );
	color4 light2_ambient( 0.3, 0.2, 0.2, 1.0 );
	color4 light2_diffuse( 0.9, 0.6, 0.6, 1.0 );
	color4 light2_specular( 1.0, 0.6, 0.6, 1.0 );

	color4 material_ambient( 0.4, 0.25, 4.1, 1.0 );
	color4 material_diffuse( 0.8, 0.5, 0.2, 1.0 );
	color4 material_specular( 0.8, 0.8, 0.8, 1.0 );
    float  material_shininess = 5.0;
	
    color4 ambient_product1 = light1_ambient * material_ambient;
    color4 diffuse_product1 = light1_diffuse * material_diffuse;
    color4 specular_product1 = light1_specular * material_specular;

	color4 ambient_product2 = light2_ambient * material_ambient;
    color4 diffuse_product2 = light2_diffuse * material_diffuse;
    color4 specular_product2 = light2_specular * material_specular;

    glUniform4fv( glGetUniformLocation(program, "AmbientProduct1"),
		  1, ambient_product1 );
    glUniform4fv( glGetUniformLocation(program, "DiffuseProduct1"),
		  1, diffuse_product1 );
    glUniform4fv( glGetUniformLocation(program, "SpecularProduct1"),
		  1, specular_product1 );

	glUniform4fv( glGetUniformLocation(program, "AmbientProduct2"),
		  1, ambient_product2 );
    glUniform4fv( glGetUniformLocation(program, "DiffuseProduct2"),
		  1, diffuse_product2 );
    glUniform4fv( glGetUniformLocation(program, "SpecularProduct2"),
		  1, specular_product2 );
	
    glUniform4fv( glGetUniformLocation(program, "Light1Position"),
		  1, light1_position );

    glUniform4fv( glGetUniformLocation(program, "Light2Position"),
		  1, light2_position );
	
    glUniform1f( glGetUniformLocation(program, "Shininess"),
		 material_shininess );
		 
    ModelView = glGetUniformLocation( program, "ModelView" );
    Projection = glGetUniformLocation( program, "Projection" );
    
    glEnable( GL_DEPTH_TEST );
    
    glClearColor( 1.0, 1.0, 1.0, 1.0 );
}

//----------------------------------------------------------------------------

void
display( void )
{
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    mat4 model_view = LookAt( eye, at, up );
    glUniformMatrix4fv( ModelView, 1, GL_TRUE, model_view );
	
	glDrawElements(GL_TRIANGLES, sizeof(elems), GL_UNSIGNED_BYTE,NULL);
    glutSwapBuffers();
}

//----------------------------------------------------------------------------

void
keyboard( unsigned char key, int x, int y )
{
    switch( key ) {
	case 033: // Escape Key
	case 'q': case 'Q':
	    exit( EXIT_SUCCESS );break;
	case 'w':
		// move camera up
		eye[1]+=0.5;break;
	case 's':
		// move camera down
		eye[1]-=0.5;break;
	case 'a':
		// move camera left
		eye[0]-=0.5;break;
	case 'd':
		// move camera right
		eye[0]+=0.5;break;
    }
	if (eye[0] >= 18 | eye[0] <= -18) {
		eye[0] = -eye[0];
	}

	if (eye[1] >= 18 | eye[1] <= -18) {
		eye[1] = -eye[1];
	}
	glutPostRedisplay();
}

//----------------------------------------------------------------------------

void
reshape( int width, int height )
{
    glViewport( 0, 0, width, height );

    GLfloat left = -2.0, right = 2.0;
    GLfloat top = 2.0, bottom = -2.0;
    GLfloat zNear = -20.0, zFar = 20.0;

    GLfloat aspect = GLfloat(width)/height;

    if ( aspect > 1.0 ) {
		left *= aspect;
		right *= aspect;
    }
    else {
		top /= aspect;
		bottom /= aspect;
    }

    mat4 projection = Ortho( left, right, bottom, top, zNear, zFar );
    glUniformMatrix4fv( Projection, 1, GL_TRUE, projection );
}

//----------------------------------------------------------------------------

int
main( int argc, char **argv )
{

    glutInit( &argc, argv );
    glutInitDisplayMode( GLUT_RGBA | GLUT_DEPTH );
    glutInitWindowSize( 512, 512 );
    glutInitContextVersion( 2, 1 );
    glutInitContextProfile( GLUT_CORE_PROFILE );
    glutCreateWindow( "LAB4" );

    glewInit();

    init();

    glutDisplayFunc( display );
    glutReshapeFunc( reshape );
    glutKeyboardFunc( keyboard );

    glutMainLoop();
    return 0;
}
