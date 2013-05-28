//
//  main.cpp
//  Final Project
//
//  Created by rschen7754 on 5/24/13.
//
//

#ifdef WIN32
#include <windows.h>
#include "GL/glew.h"
#include <GL/gl.h>
#include <GL/glu.h>
#else
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>

#ifdef WIN32
#include "GL/freeglut.h"
#else
#include <GLUT/glut.h>
#endif


#include "Angel/Angel.h"

#ifdef __APPLE__
#define glutInitContextVersion(a,b)
#define glutInitContextProfile(a)
#define glewExperimental int glewExperimentalAPPLE
#define glewInit()
#endif

#include "mapGen.h"
#include "tga.h"

int Width = 800;
int Height = 800 ;

GLfloat shiftX = 0.0;
GLfloat shiftY = 0.0;
GLfloat shiftZ = 0.0;
GLfloat shiftTheta = 0.0;

mat4         model_view;
GLint        uModelView, uProjection, uView;
GLint        uAmbient, uDiffuse, uSpecular, uLightPos, uShininess;
GLint        uTex, uEnableTex;

// The eye point and look-at point.
// Currently unused. Use to control a camera with LookAt().
Angel::vec4 eye{0, 0.0, 50.0,1.0};
Angel::vec4 ref{0.0, 0.0, 0.0,1.0};
Angel::vec4 up{0.0,1.0,0.0,0.0};

void init() {
    
    GLuint program = InitShader( "vshader.glsl", "fshader.glsl" );
    glUseProgram(program);
    
    readFile();
    
    uModelView  = glGetUniformLocation( program, "ModelView"  );
    uProjection = glGetUniformLocation( program, "Projection" );
    uView       = glGetUniformLocation( program, "View"       );
    
    glClearColor( 0.2, 0.2, 1.0, 1.0 ); // dark blue background
    
    uAmbient   = glGetUniformLocation( program, "AmbientProduct"  );
    uDiffuse   = glGetUniformLocation( program, "DiffuseProduct"  );
    uSpecular  = glGetUniformLocation( program, "SpecularProduct" );
    uLightPos  = glGetUniformLocation( program, "LightPosition"   );
    uShininess = glGetUniformLocation( program, "Shininess"       );
    uTex       = glGetUniformLocation( program, "Tex"             );
    uEnableTex = glGetUniformLocation( program, "EnableTex"       );
    
    glUniform4f(uAmbient,    0.2f,  0.2f,  0.2f, 1.0f);
    glUniform4f(uDiffuse,    0.6f,  0.6f,  0.6f, 1.0f);
    glUniform4f(uSpecular,   0.2f,  0.2f,  0.2f, 1.0f);
    glUniform4f(uLightPos,  0.0f, 10.0f, 20.0f, 0.0f);
    glUniform1f(uShininess, 100.0f);
    
    glEnable(GL_DEPTH_TEST);
}

void displayHandler() {
    // Clear the screen with the background colour (set in myinit)
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    model_view = mat4(1.0f)*Translate(0.25*shiftX, 0.25*shiftY, 0.25*shiftZ);
    
    glUniformMatrix4fv( uModelView, 1, GL_TRUE, model_view );

    glutSwapBuffers();
}

void keyHandler(unsigned char key, int x, int y) {
        if (key=='q' || key=='Q') exit(0);
}
void reshapeHandler(int w, int h) {
    
}
void buttonHandler(int button, int state, int x, int y) {
    
}

void motionHandler(int x, int y) {
    
}
void idleHandler() {
    
}

int main(int argc, char** argv)
{

    glutInit(&argc, argv);
    // If your code fails to run, uncommenting these lines may help.
    //glutInitContextVersion(3, 2);
    //glutInitContextProfile(GLUT_CORE_PROFILE);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition (0, 0);
    glutInitWindowSize(Width,Height);
    glutCreateWindow( "Game");
    //printf("GL version %s\n", glGetString(GL_VERSION));
    glewExperimental = GL_TRUE;
    glewInit();
    
    init();
    
    glutIdleFunc(idleHandler) ;
    glutReshapeFunc (reshapeHandler);
    glutKeyboardFunc( keyHandler );
    glutMouseFunc(buttonHandler) ;
    glutMotionFunc(motionHandler) ;
    
    glutDisplayFunc(displayHandler);
    glutMainLoop();
    
    return 0;         // never reached

}
