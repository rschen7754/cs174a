//
//  main.h
//  Final Project
//
//  Created by rschen7754 on 5/30/13.
//
//

#ifndef Final_Project_main_h
#define Final_Project_main_h


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
#include <vector>

#ifdef __APPLE__
#define glutInitContextVersion(a,b)
#define glutInitContextProfile(a)
#define glewExperimental int glewExperimentalAPPLE
#define glewInit()
#endif

#include "mapGen.h"
#include "tga.h"
#include "Timer.h"


const static int MENU_ON=1;
const static int MENU_PLAY=2;
const static int MENU_OVER=3;

const int ANIMATE_NONE = 0;
const int ANIMATE_UP = 1;
const int ANIMATE_DOWN = 2;
const int ANIMATE_RIGHT = 3;
const int ANIMATE_LEFT = 4;


const int HEIGHT_BOTTOM = 0;
const int HEIGHT_CENTER = 1;
const int HEIGHT_TOP = 2;

const int UP = 0;
const int DOWN = 1;
const int LEFT = 2;
const int RIGHT = 3;
const int FORWARD = 4;

float SCORE = 0;
int health = 3;

int Width = 800;
int Height = 800 ;

int menuState = MENU_ON;

mat4         model_view;
GLint        uModelView, uProjection, uView;
GLint        uAmbient, uDiffuse, uSpecular, uLightPos, uShininess;
GLint        uTex, uEnableTex;

typedef Angel::vec4  color4;
typedef Angel::vec4  point4;
typedef Angel::vec3 point3;
typedef Angel::vec2 point2;

int Index = 0;
const int NumVertices = 36;

// Arrays to hold ship points

point4 cube[NumVertices];

point4 shipleft[NumVertices];
vec3 shipleftNormals[NumVertices];
point2 shipleftUV[NumVertices];
point4 shipRight[NumVertices];
vec3 shipRightNormals[NumVertices];
point2 shipRightUV[NumVertices];
point4 shipCenter[NumVertices];
vec3 shipCenterNormals[NumVertices];
point2 shipCenterUV[NumVertices];
point4 blockModel[NumVertices];
vec3 blockModelNormals[NumVertices];
point2 blockModelUV[NumVertices];


struct cubePos {
    GLfloat x;
    GLfloat y;
    GLfloat z;
};

std::vector<cubePos> blocks;


// Creates a cube
void createCube(point4 cube[], int x, int y, int z, int width, int height, int length);

// Initializes a rectangle to an array
void intializeRectangle(GLfloat x, GLfloat y, GLfloat z, GLfloat width, GLfloat height,GLfloat length,  point4 points[], vec3 normals[]);

// Draws the rectangle
void drawRectangle(point4 points[], vec3 normals[], vec4 fColor, GLfloat x, GLfloat y, GLfloat z);

GLuint program;
GLuint vao[2];
GLuint vPosition;
GLuint vNormal;
GLuint buffer;

// Model-view and projection matrices uniform location
GLuint  ModelView, Projection, Transformation;

//===============


// View Box
GLfloat left = -10.0, right = 10.0, bottom = -10.0, top = 10.0;
GLfloat  zNear = 5.0, zFar = 400;

GLfloat aspect;

// Coordinates of the camera
GLfloat pos_x = -2.0;
GLfloat pos_y = -15.0;
GLfloat pos_z = -40.0;



// Define Colors
const vec4 COLOR_GREY = vec4(0.44,0.44,0.44,1.0);
const vec4 COLOR_BLUE = vec4(0.5376,0.96,0.9459,1.0);
const vec4 COLOR_SWAMP = vec4( 0.523,0.95,0.7149,1.0);
const vec4 COLOR_WHITE = vec4(0.94,0.996,1,1.0);
const vec4 COLOR_BROWN = vec4(0.85, 0.6233, 0.425, 1.0);
const vec4 COLOR_MENU = vec4(0.2,0.2,0.9459,1.0);



// Time Rotate Variables
double TIME;
double TIME_LAST;
double DTIME;
Timer TM;



//define crosshairs as a series of triangles
point4 menuBox[6] = {
    point4( 10.0, 5.0,  0.0, 1.0 ),
    point4( -10.0,  5.0, 0.0, 1.0 ),
    point4( -10.0, -5.0, 0.0, 1.0 ),
    
    //next one
    point4( -10.0, -5.0, 0.0, 1.0 ),
    point4( 10.0, 5.0, 0.0, 1.0 ),
    point4( 10.0, -5.0,  0.0, 1.0 ),
};

GLuint texture_cube;
int end;

#endif
