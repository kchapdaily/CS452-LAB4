// fragment shading of sphere model

#include "Angel.h"

const int NumVertices = 8;

typedef Angel::vec4 point4;
typedef Angel::vec4 color4;

// Model-view and projection matrices uniform location
GLuint  ModelView, Projection;

GLfloat size=1;

GLfloat vertexarray[]={size, size, size,   //V0
					   -size, size, size,  //V1
					   -size, size, -size, //V2
					   size, size, -size,  //V3
					   size, -size, size,  //V4
					   -size, -size, size, //V5
					   -size, -size, -size,//V6
					   size, -size, -size  //V7
};

GLfloat colorarray[]={1.0f,1.0f,1.0f,1.0f,
					  0.5f,1.0f,1.0f,1.0f,
					  1.0f,0.5f,1.0f,1.0f,
					  1.0f,1.0f,0.5f,1.0f,
					  1.0f,1.0f,1.0f,1.0f,
					  0.5f,1.0f,1.0f,1.0f,
					  1.0f,0.5f,1.0f,1.0f,
                      1.0f,1.0f,0.5f,1.0f
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
    // Create a vertex array object
    GLuint vao, vbo, ebo;

    glGenVertexArrays( 1, &vao );
    glBindVertexArray( vao );
	
	// bind vertex, color, and elems arrays to buffers
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER,vbo);
	glBufferData(GL_ARRAY_BUFFER,sizeof(vertexarray),vertexarray,GL_STATIC_DRAW);
	glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,(void*)0);
    
	glGenBuffers(1,&ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(elems),elems,GL_STATIC_DRAW);

	
    // Load shaders and use the resulting shader program
    GLuint program = InitShader( "vshader56.glsl", "fshader56.glsl" );
    glUseProgram( program );
	
    // set up vertex arrays
	glEnableVertexAttribArray(0);
	// glEnableVertexAttribArray(1);

    // Initialize shader lighting parameters
    point4 light_position( 0.0, 0.0, -2.0, 0.0 );
    color4 light_ambient( 0.0, 0.5, 0.0, 1.0 );
    color4 light_diffuse( 0.0, 1.0, 0.0, 1.0 );
    color4 light_specular( 0.0, 0.0, 0.0, 1.0 );

    color4 material_ambient( 1.0, 1.0, 1.0, 1.0 );
    color4 material_diffuse( 1.0, 1.0, 1.0, 1.0 );
    color4 material_specular( 1.0, 1.0, 1.0, 1.0 );
    float  material_shininess = 5.0;

    color4 ambient_product = light_ambient * material_ambient;
    color4 diffuse_product = light_diffuse * material_diffuse;
    color4 specular_product = light_specular * material_specular;
	
    glUniform4fv( glGetUniformLocation(program, "AmbientProduct"),
		  1, ambient_product );
    glUniform4fv( glGetUniformLocation(program, "DiffuseProduct"),
		  1, diffuse_product );
    glUniform4fv( glGetUniformLocation(program, "SpecularProduct"),
		  1, specular_product );
	
    glUniform4fv( glGetUniformLocation(program, "LightPosition"),
		  1, light_position );

    glUniform1f( glGetUniformLocation(program, "Shininess"),
		 material_shininess );
		 
    // Retrieve transformation uniform variable locations
    ModelView = glGetUniformLocation( program, "ModelView" );
    Projection = glGetUniformLocation( program, "Projection" );
    
    glEnable( GL_DEPTH_TEST );
    
    glClearColor( 1.0, 1.0, 1.0, 1.0 ); /* white background */
}

//----------------------------------------------------------------------------

void
display( void )
{
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    point4 at( 0.0, 0.0, 0.0, 1.0 );
    point4 eye( 2.0, 2.0, 2.0, 1.0 );
    vec4   up( 0.0, 1.0, 0.0, 0.0 );

    mat4 model_view = LookAt( eye, at, up );
    glUniformMatrix4fv( ModelView, 1, GL_TRUE, model_view );

	glDrawElements(GL_TRIANGLES, sizeof(elems), GL_UNSIGNED_BYTE,NULL);
    // glDrawArrays( GL_TRIANGLES, 0, NumVertices );
    glutSwapBuffers();
}

//----------------------------------------------------------------------------

void
keyboard( unsigned char key, int x, int y )
{
    switch( key ) {
	case 033: // Escape Key
	case 'q': case 'Q':
	    exit( EXIT_SUCCESS );
	    break;
    }
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
    glutCreateWindow( "Sphere" );

    glewInit();

    init();

    glutDisplayFunc( display );
    glutReshapeFunc( reshape );
    glutKeyboardFunc( keyboard );

    glutMainLoop();
    return 0;
}
