//
//  main.h
//  Space Runner
//
//  Created by Collin Yen on 5/24/13.
//  Copyright (c) 2013 Collin Yen. All rights reserved.
//

#ifndef Space_Runner_main_h
#define Space_Runner_main_h

#include <stdlib.h>
#include "angel.h"
#include "InitShader.h"
#include <vector>


const int UP = 0;
const int DOWN = 1;
const int LEFT = 2;
const int RIGHT = 3;
const int FORWARD = 4;


typedef Angel::vec4  color4;
typedef Angel::vec4  point4;

int Index = 0;
const int NumVertices = 36;

point4 cube[8];
point4 points[NumVertices];
point4 colors[NumVertices];


struct cubePos {
    GLfloat x;
    GLfloat y;
    GLfloat z;
};


std::vector<cubePos> blocks;




void callbackDisplay();
void drawSphere(GLfloat x, GLfloat y, GLfloat z, GLfloat r, GLfloat rotate, int numSubdivide, vec4 fColor, GLint shading);
void createCube(point4 cube[], int x, int y, int z);
void drawRectangle(GLfloat x, GLfloat y, GLfloat z, GLfloat width, GLfloat height, GLfloat length, vec4 fColor);



GLsizei w=512, h=512;

GLuint program;
GLuint vao[2];
GLuint vPosition;
GLuint buffer;

// Model-view and projection matrices uniform location
GLuint  ModelView, Projection, Transformation;

//===============


// View Box
GLfloat left = -10.0, right = 10.0, bottom = -10.0, top = 10.0;
GLfloat  zNear = 5.0, zFar = 400;

// Coordinates of the camera
GLfloat pos_x = -2.0;
GLfloat pos_y = -15.0;
GLfloat pos_z = -40.0;

//// camera direction from the z-axis
//GLfloat displacement_z = 6.0*DegreesToRadians;
//GLfloat displacement_y = 30.0*DegreesToRadians;


// Time Rotate Variables
double TIME;
double TIME_LAST;
double DTIME;
//Timer TM;
double rotation;
int FRAME_COUNT = 0;
bool pause = false;
bool detachCamera = false;

// Define Colors
const vec4 COLOR_RED = vec4(0.96,0.305,0.1056,1.0);
const vec4 COLOR_BLUE = vec4(0.084,0.7644,0.84,1.0);
const vec4 COLOR_SWAMP = vec4( 0.523,0.95,0.7149,1.0);
const vec4 COLOR_WHITE = vec4(0.94,0.996,1,1.0);
const vec4 COLOR_BROWN = vec4(0.85, 0.6233, 0.425, 1.0);


// Define Shading
const GLint SHADE_NONE = 0;
const GLint SHADE_FLAT = 1;
const GLint SHADE_GOURAUD = 2;
const GLint SHADE_PHONG = 3;
const GLint SHADE_DULL = 4;

// Define Moon Rotation
const GLfloat ROTATION_MOON = 666;
GLfloat aspect;
#endif


