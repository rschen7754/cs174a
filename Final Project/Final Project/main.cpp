//
//  main.cpp
//  Final Project
//
//  Created by rschen7754 on 5/24/13.
//
//

#include "main.h"



//==============================================


// quad generates two triangles for each face and assigns colors
//    to the vertices


void quad( int a, int b, int c, int d, point4 vertices[])
{
    points[Index] = vertices[a]; Index++;
    points[Index] = vertices[b]; Index++;
    points[Index] = vertices[c]; Index++;
    points[Index] = vertices[a]; Index++;
    points[Index] = vertices[c]; Index++;
    points[Index] = vertices[d]; Index++;
    
}

// Creates a cube given a set of vertices and color
void colorcube(point4 vertices[], int indexColor)
{
    quad( 1, 0, 3, 2 ,vertices);
    quad( 2, 3, 7, 6 ,vertices);
    quad( 3, 0, 4, 7 ,vertices);
    quad( 6, 5, 1, 2 ,vertices);
    quad( 4, 5, 6, 7 ,vertices);
    quad( 5, 4, 0, 1 ,vertices);
}

// Establishes cube vertices given an initial position
void createCube(point4 cube[], int x, int y, int z, int width, int height, int length){
    //    cube[0] = point4(x-2.5,y-2.5,z+2.5+length,1.0);
    //    cube[1] = point4(x-2.5,y+2.5+height,z+2.5+length,1.0);
    //    cube[2] = point4(x+2.5+width,y+2.5+height,z+2.5+length,1.0);
    //    cube[3] = point4(x+2.5+width,y-2.5,z+2.5+length,1.0);
    //    cube[4] = point4(x-2.5,y-2.5,z-2.5,1.0);
    //    cube[5] = point4(x-2.5,y+2.5+height,z-2.5,1.0);
    //    cube[6] = point4(x+2.5+width,y+2.5+height,z-2.5,1.0);
    //    cube[7] = point4(x+2.5+width,y-2.5,z-2.5,1.0);
    cube[0] = point4(x,y,z+5+length,1.0);
    cube[1] = point4(x,y+5+height,z+5+length,1.0);
    cube[2] = point4(x+5+width,y+5+height,z+5+length,1.0);
    cube[3] = point4(x+5+width,y,z+5+length,1.0);
    cube[4] = point4(x,y,z,1.0);
    cube[5] = point4(x,y+5+height,z,1.0);
    cube[6] = point4(x+5+width,y+5+height,z,1.0);
    cube[7] = point4(x+5+width,y,z,1.0);
    
}

//======================================

// Player Class that handles the user
class Player {
public:
    Player(int x, int y);
    
    // Moves in a specific direction
    void move(int dir);
    
    // Sets the player to dead
    void setDead();
    
    // Determines if the player is alive
    bool isAlive();
    
    // Determine if player collided with a block
    bool didCollide();
    
    // Draw Ship
    void draw();
    
private:
    // Position of the player
    GLfloat m_posx;
    GLfloat m_posy;
    GLfloat m_posz;
    bool m_isAlive;
    
    
};

Player::Player(int x, int y)
{
    m_posx = x;
    m_posy = y;
    m_posz = -20;
    //
    pos_x = -x-2.0;
    pos_y = -y-15.0;
    m_isAlive = true;
    
}

void Player::move(int dir)
{
    if (dir == UP) {
        m_posy += 5;
        pos_y -= 5;
    }else if (dir == DOWN){
        m_posy -= 5;
        pos_y += 5;
    }else if (dir == LEFT){
        m_posx -= 5+5;
        pos_x += 5+5;
    }else if (dir == RIGHT){
        m_posx += 5+5;
        pos_x -=5+5;
    }else if (dir == FORWARD){
        m_posz -= 1;
        pos_z += 1;
    }
}

void Player::setDead(){
    m_isAlive = false;
}

bool Player::isAlive(){
    return m_isAlive;
}

bool Player:: didCollide(){
    for (int i = 0; i < blocks.size(); i++) {
        if ((m_posx+10 > blocks[i].x && m_posx-5 < blocks[i].x+5) &&
            (m_posy + 5 > blocks[i].y && m_posy < blocks[i].y+5)&&
            (m_posz -6 < blocks[i].z && m_posz > blocks[i].z-5)) {
            setDead();
            std::cerr << "dead";
            return true;
        }
    }
    
    return false;
}

void Player::draw(){
    
    drawRectangle(m_posx, m_posy, m_posz, 0,0,10, vec4(1.0,0.0,0.0,1.0));
    drawRectangle(m_posx + 5, m_posy, m_posz +3, 0, -2,5, vec4(0.0,1.0,0.0,1.0));
    drawRectangle(m_posx-5, m_posy, m_posz +3, 0, -2, 5,vec4(0.0,1.0,0.0,1.0));
    
}


// Initialize Player
Player User(0,0);

// Draws a rectangle
void drawRectangle(GLfloat x, GLfloat y, GLfloat z, GLfloat width, GLfloat height,GLfloat length, vec4 fColor)
{
    Index = 0;
    createCube(cube, x, y, z,width,height, length);
    colorcube(cube, 0);
    glUseProgram(program);
    
    // Create and initialize a buffer object
    glBufferData( GL_ARRAY_BUFFER, sizeof(point4)*NumVertices, NULL, GL_STATIC_DRAW );
    glBufferSubData( GL_ARRAY_BUFFER, 0, sizeof(point4)*NumVertices, points );
    
    // set up vertex arrays
    glEnableVertexAttribArray( vPosition );
    glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0) );
    
    // Create model_view matrix to transform and rotate the cubes
    mat4  mv =Translate(pos_x, pos_y,pos_z);
    glUniformMatrix4fv( ModelView, 1, GL_TRUE, mv );
    
    // Define a viewing box
    mat4 p = Perspective(45, aspect, zNear, zFar);
    glUniformMatrix4fv( Projection, 1, GL_TRUE, p );
    glUniform4fv(glGetUniformLocation(program, "fcolor"), 1, fColor);
    
    // Draw proper items
    glDrawArrays( GL_TRIANGLES, 0, NumVertices );
    
}




void init() {
    
    glGenVertexArraysAPPLE(1, &vao[0]);
    glBindVertexArrayAPPLE(vao[0]);
    
    // Create a vertex array object
    glGenBuffers( 1, &buffer );
    glBindBuffer( GL_ARRAY_BUFFER, buffer );
    
 
    GLuint program = InitShader( "vshader.glsl", "fshader.glsl" );
    glUseProgram(program);
    
	//data stored in "map" (20x10 array of integers);
	//0 = no block, 1 = block present, 2 = start position

    readFile();
    
    ModelView = glGetUniformLocation( program, "model_view" );
    Projection = glGetUniformLocation( program, "projection" );
    
    // Place test blocks into blocks vector for collision detection
    cubePos testBlock;
    testBlock.x = 0;
    testBlock.y = 10;
    testBlock.z = -40;
    cubePos testBlock2;
    testBlock2.x = 0;
    testBlock2.y = 40;
    testBlock2.z = -40;
    blocks.push_back(testBlock);
    blocks.push_back(testBlock2);
    
    // Set black background
    glClearColor( 0.0, 0.0, 0.0, 1.0 );

    
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
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    
    mat4 p;
    
    //draw menu
    if (menuState==MENU_ON) {
        //orthographic projection
        p = Ortho(-1.0, 1.0, -1.0, 1.0, 0.5, 3.0);
        glUniformMatrix4fv( Projection, 1, GL_TRUE, p );
        
        for (int i=0; i<12; i++) {
            colors[i] = color4 (1.0, 1.0, 1.0, 1.0);
        }
        glBufferSubData( GL_ARRAY_BUFFER, 0, sizeof(crosshairs), crosshairs );
        glBufferSubData( GL_ARRAY_BUFFER, sizeof(points), sizeof(colors), colors );
        
        glDrawArrays( GL_TRIANGLES, 0, 12 );
    }
    
    // Draw the Planets and the Sun
    // drawSun(); // Sun at 17,0,0
    User.draw();
    drawRectangle(0, 10,-40, 0, 0, 0, vec4(0.0,0.0,1.0,1.0));
    drawRectangle(0, 40,-40, 0, 0, 0, vec4(0.0,0.0,1.0,1.0));
    
    User.didCollide();
    glutSwapBuffers();
}

void keyHandler(unsigned char key, int x, int y) {
    
    switch (key) {
            
        case 'w':       // Move the camera forward
            pos_x -= 2;
            pos_z += 2;
            zFar -= 2;
            break;
        case 's':       // Move the camera backward
            pos_x += 2;
            pos_z -= 2;
            zFar += 2;
            break;
        case 'd':       // Move the camera to the right
            pos_x -= 2;
            pos_z -= 2;
            break;
        case 'a':       // Move the camera to the left
            pos_x += 2;
            pos_z += 2;
            break;
        case 'i': // Moves the camera up
            pos_y -= 1;
            break;
        case 'm': // Moves the camera down
            pos_y += 1;
            break;
        case ' ':// Resets the view of the camera
            // Coordinates of the camera
            pos_x = 0.0;
            pos_y = -110.0;
            pos_z = -250.0;
            
        case 'f':
            User.move(FORWARD);
            break;
            
            break;
        case 'p': // Pauses the entire scene
            pause = !pause;
            break;
            break;
            
            
            
            
        case 'q':
        case 'Q':
            exit(0);
            break;
            
        default:
            break;
    }
    glutPostRedisplay();
}
void reshapeHandler(int width, int height) {
    
    glViewport(0,0,width,height);
    aspect = GLfloat(width)/height;
    
}

void specialHandler(int key, int x, int y)
{
    
    switch (key) {
        case GLUT_KEY_UP: // Moves the camera up
            User.move(UP);
            break;
        case GLUT_KEY_DOWN: // Moves the camera down
            User.move(DOWN);
            break;
        case GLUT_KEY_LEFT: // Turns the camera left
            User.move(LEFT);
            break;
        case GLUT_KEY_RIGHT: // Turns the camera right
            User.move(RIGHT);
            break;
            
        default:
            break;
    }
    
    glutPostRedisplay();
}

void buttonHandler(int button, int state, int x, int y) {
    
}

void motionHandler(int x, int y) {
    //if player dead, game over, restart initializes
    //score
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
    glutSpecialFunc(specialHandler);
    
    glutDisplayFunc(displayHandler);
    glutMainLoop();
    
    return 0;         // never reached

}
