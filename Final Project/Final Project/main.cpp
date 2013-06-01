//
//  main.cpp
//  Final Project
//
//  Created by rschen7754 on 5/24/13.
//
//

#include "main.h"

const int ANIMATE_NONE = 0;
const int ANIMATE_UP = 1;
const int ANIMATE_DOWN = 2;
const int ANIMATE_RIGHT = 3;
const int ANIMATE_LEFT = 4;


const int HEIGHT_BOTTOM = 0;
const int HEIGHT_CENTER = 1;
const int HEIGHT_TOP = 2;


//==============================================


// quad generates two triangles for each face and assigns colors
//    to the vertices


void quad( int a, int b, int c, int d, point4 vertices[], point4 points[])
{
    points[Index] = vertices[a]; Index++;
    points[Index] = vertices[b]; Index++;
    points[Index] = vertices[c]; Index++;
    points[Index] = vertices[a]; Index++;
    points[Index] = vertices[c]; Index++;
    points[Index] = vertices[d]; Index++;
    
}

// Creates a cube given a set of vertices and color
void colorcube(point4 vertices[], int indexColor, point4 points[])
{
    quad( 1, 0, 3, 2 ,vertices, points);
    quad( 2, 3, 7, 6 ,vertices, points);
    quad( 3, 0, 4, 7 ,vertices, points);
    quad( 6, 5, 1, 2 ,vertices, points);
    quad( 4, 5, 6, 7 ,vertices, points);
    quad( 5, 4, 0, 1 ,vertices, points);
}


// Establishes cube vertices given an initial position
void createCube(point4 cube[], int x, int y, int z, int width, int height, int length){
    
    cube[0] = point4(x,y,z+5+length,1.0);
    cube[1] = point4(x,y+5+height,z+5+length,1.0);
    cube[2] = point4(x+5+width,y+5+height,z+5+length,1.0);
    cube[3] = point4(x+5+width,y,z+5+length,1.0);
    cube[4] = point4(x,y,z,1.0);
    cube[5] = point4(x,y+5+height,z,1.0);
    cube[6] = point4(x+5+width,y+5+height,z,1.0);
    cube[7] = point4(x+5+width,y,z,1.0);
    
}

void intializeRectangle(GLfloat x, GLfloat y, GLfloat z, GLfloat width, GLfloat height,GLfloat length,  point4 points[])
{
    Index = 0;
    createCube(cube, x, y, z,width,height, length);
    colorcube(cube, 0, points);
}

// Draws a rectangle
void drawRectangle(point4 points[], vec4 fColor, GLfloat x, GLfloat y, GLfloat z)
{

    // Create and initialize a buffer object
    glBufferData( GL_ARRAY_BUFFER, sizeof(point4)*NumVertices, NULL, GL_STATIC_DRAW );
    glBufferSubData( GL_ARRAY_BUFFER, 0, sizeof(point4)*NumVertices, points );
    
    // set up vertex arrays
    glEnableVertexAttribArray( vPosition );
    glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0) );
    
    // Create model_view matrix to transform and rotate the cubes
    mat4  mv =Translate(pos_x, pos_y,pos_z)*Translate(x, y, z);
    glUniformMatrix4fv( ModelView, 1, GL_TRUE, mv );
    
    // Define a viewing box
    mat4 p = Perspective(45, aspect, zNear, zFar);
    glUniformMatrix4fv( Projection, 1, GL_TRUE, p );
    glUniform4fv(glGetUniformLocation(program, "fcolor"), 1, fColor);
    
    // Draw proper items
    glDrawArrays( GL_TRIANGLES, 0, NumVertices );
    
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
    
    // Get animation status
    int getAnimationStatus();
    
    // Set animation Status
    void setAnimationStatus(int status);
    
    // Get Height Level
    int getHeightLevel();
    
    // Set Height Level
    void setHeightLevel(int height);
    
    // Gets the y position of the ship
    GLfloat getY();
    
    // Draw Ship
    void draw();
    
private:
    // Position of the player
    GLfloat m_posx;
    GLfloat m_posy;
    GLfloat m_posz;
    
    bool m_isAlive;
    bool m_animationStatus;
    int m_heightLevel;
    
};

Player::Player(int x, int y)
{
    
    m_posx = 0;
    m_posy = 0;
    m_posz = 0;
    
    pos_x = -x-2.0;
    pos_y = -y-15.0;
    m_isAlive = true;
    m_heightLevel = HEIGHT_CENTER;
    
    
    // Initialize Ship Rectangles
    intializeRectangle(x, y, -20, 0,0,10, shipCenter);
    intializeRectangle(x + 5, y, -20 +3, 0, -2,5, shipleft);
    intializeRectangle(x-5, y, -20 +3, 0, -2, 5, shipRight);
    
}

void Player::move(int dir)
{
    if (dir == UP) {
//        m_posy += 15;
//        pos_y -= 15;
        m_posy += DTIME*100;
        pos_y -= DTIME*100;
    }else if (dir == DOWN){
//        m_posy -= 15;
//        pos_y += 15;
        m_posy -= DTIME*100;
        pos_y += DTIME*100;
    }else if (dir == LEFT){
        m_posx -= 20+5;
        pos_x += 20+5;
    }else if (dir == RIGHT){
        m_posx += 20+5;
        pos_x -=20+5;
    }else if (dir == FORWARD){
        m_posz -= DTIME*100;
        pos_z += DTIME*100;
    }
}

int Player::getHeightLevel()
{
    return m_heightLevel;
}

void Player::setHeightLevel(int height)
{
    m_heightLevel = height;
}

int Player::getAnimationStatus()
{
    return m_animationStatus;
}

void Player::setAnimationStatus(int status)
{
    m_animationStatus = status;
}

GLfloat Player::getY(){
    return m_posy;
}

void Player::setDead(){
    m_isAlive = false;
}

bool Player::isAlive(){
    return m_isAlive;
}

bool Player:: didCollide(){
    if (menuState==MENU_ON || menuState==MENU_OVER)
        return false;
    
    for (int i = 0; i < blocks.size(); i++) {
        if ((m_posx+10 > blocks[i].x && m_posx-5 < blocks[i].x+5) &&
            (m_posy + 5 > blocks[i].y && m_posy < blocks[i].y+5)&&
            (m_posz -30< blocks[i].z && m_posz > blocks[i].z+5)) {
            setDead();
            std::cerr << "dead";
            menuState = MENU_OVER;
            return true;
        }


        
    }
    
    return false;
}



void Player::draw(){
    drawRectangle(shipleft, COLOR_BLUE, m_posx, m_posy, m_posz);
    drawRectangle(shipCenter, COLOR_GREY, m_posx, m_posy, m_posz);
    drawRectangle(shipRight, COLOR_BLUE, m_posx, m_posy, m_posz);
    
}


// Initialize Player
Player User(0,0);


void init() {
    
    // Initialize 5x5 Blocks
    intializeRectangle(0, 0, 0, 0, 0, 0, blockModel);
    
    glGenVertexArraysAPPLE(1, &vao[0]);
    glBindVertexArrayAPPLE(vao[0]);
    
    // Create a vertex array object
    glGenBuffers( 1, &buffer );
    glBindBuffer( GL_ARRAY_BUFFER, buffer );
    
 
    program = InitShader( "vshader.glsl", "fshader.glsl" );
    
    glUseProgram(program);
	//data stored in "map" (20x10 array of integers);
	//0 = no block, 1 = block present, 2 = start position

	std::vector<float> xPos;
	std::vector<float> yPos;
	std::vector<float> zPos;
    readFile();
    storeBlocks(xPos, yPos, zPos);
	int numBlocks = xPos.size();

	for (int i = 0; i < numBlocks; i++)
	{
		cubePos tempBlock;
		tempBlock.x = -xPos[i];
		tempBlock.y = yPos[i];
		tempBlock.z = -zPos[i];
		blocks.push_back(tempBlock);

	}

    ModelView = glGetUniformLocation( program, "ModelView" );
    Projection = glGetUniformLocation( program, "Projection" );
    
    // Place test blocks into blocks vector for collision detection
    
    // Set black background
    glClearColor( 0.0, 0.0, 0.0, 1.0 );
   //   glClearColor( 1.0, 1.0, 1.0, 1.0 );
    
    TgaImage menuImage;
    if (!menuImage.loadTGA("menu.tga"))
    {
        printf("Error loading image file menu\n");
        exit(1);
    }
    
    TgaImage gameoverImage;
    if (!gameoverImage.loadTGA("gameover.tga"))
    {
        printf("Error loading image file gameover\n");
        exit(1);
    }

    
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

//// Here are the fonts:
//LPVOID glutFonts[7] = {
//    GLUT_BITMAP_9_BY_15,
//    GLUT_BITMAP_8_BY_13,
//    GLUT_BITMAP_TIMES_ROMAN_10,
//    GLUT_BITMAP_TIMES_ROMAN_24,
//    GLUT_BITMAP_HELVETICA_10,
//    GLUT_BITMAP_HELVETICA_12,
//    GLUT_BITMAP_HELVETICA_18
//};

void glutPrint(float x, float y, char* text, float r, float g, float b, float a)
{
    if(!text || !strlen(text)) return;
    bool blending = false;
    if(glIsEnabled(GL_BLEND)) blending = true;
    glEnable(GL_BLEND);
    glUniform4fv(glGetUniformLocation(program, "fcolor"), 1, color4(r,g,b,a));
    glRasterPos2f(x,y);
    while (*text) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *text);
        text++;
    }
    if(!blending) glDisable(GL_BLEND);
}

void displayHandler() {
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    
    
    
    mat4 p;
    
    for (int i = 0; i < blocks.size(); i++) {
        drawRectangle(blockModel, vec4(0.0,1.0,0.0,1.0), blocks[i].x, blocks[i].y, blocks[i].z);
    }
    
                std::cerr << "hello" << User.getAnimationStatus();
    if (User.getAnimationStatus() == ANIMATE_UP) {
        if (User.getHeightLevel() == HEIGHT_BOTTOM) {
            if (User.getY() <=0) {
                User.move(UP);
            }else{
                User.setHeightLevel(HEIGHT_CENTER);
                User.setAnimationStatus(ANIMATE_NONE);
            }
        }
        else if(User.getHeightLevel() == HEIGHT_CENTER){
            if (User.getY() <=15) {
                User.move(UP);
            }else{
                User.setHeightLevel(HEIGHT_TOP);
                User.setAnimationStatus(ANIMATE_NONE);
            }

        }

    }else if (User.getAnimationStatus() == ANIMATE_DOWN)
    {

        if (User.getHeightLevel() == HEIGHT_TOP) {
            if (User.getY()>=0) {
                User.move(DOWN);
            }else{
                User.setHeightLevel(HEIGHT_CENTER);
                User.setAnimationStatus(ANIMATE_NONE);
            }
        }
    }
    
    User.draw();
    
    //draw menu
    if (menuState==MENU_ON || menuState == MENU_OVER) {
        mat4  mv =Translate(0, 0,pos_z);
        glUniformMatrix4fv( ModelView, 1, GL_TRUE, mv );

        //orthographic projection
        p = Ortho(2*left, 2*right, 2*bottom, 2*top, zNear, zFar);
        glUniformMatrix4fv( Projection, 1, GL_TRUE, p );
        
        
        glUniform4fv(glGetUniformLocation(program, "fcolor"), 1, COLOR_MENU);
        glBufferSubData( GL_ARRAY_BUFFER, 0, sizeof(menuBox), menuBox );
        
        //kept drawing on top of the text :(
       // glDrawArrays( GL_TRIANGLES, 0, 6 ); 
        
        mv =Translate(pos_x+2.5, pos_y,pos_z);
        glUniformMatrix4fv( ModelView, 1, GL_TRUE, mv );
        
        glutPrint(-5.5,20, "Welcome to SpaceRunner!", 1, 1, 1, 1);
        
        mv =Translate(pos_x+2.5, pos_y+15,pos_z);
        glutPrint(-4.5,17, "Press Enter to begin.", 1, 1, 1, 1);
        
    }
    
    else {
        //should go inside else

        drawRectangle(shipCenter, vec4(0.0,1.0,0.0,1.0), 0, 10, -100);
        drawRectangle(shipCenter, vec4(0.0,1.0,0.0,1.0), 20, 10, -200);
        drawRectangle(blockModel, vec4(0.0,1.0,0.0,1.0), -10, 10, -200);
        

    
        User.didCollide();
    }
    
    glutSwapBuffers();
}

void keyHandler(unsigned char key, int x, int y) {
    
    if (menuState != MENU_PLAY && key != 'q' && key != 'Q' && key != 13)
        return;
    
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
            break;
            
        case 'q':
        case 'Q':
            exit(0);
            break;
            
        case 13: //hitting enter
            if (menuState != MENU_PLAY) {
                menuState = MENU_PLAY;
                TM.Reset();
            }
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
    if (menuState != MENU_PLAY)
        return;
    switch (key) {
        case GLUT_KEY_UP: // Moves the camera up
//            User.move(UP);
            User.setAnimationStatus(ANIMATE_UP);
            break;
        case GLUT_KEY_DOWN: // Moves the camera down
            User.setAnimationStatus(ANIMATE_DOWN);
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
    if (menuState==MENU_PLAY) {
        TIME = TM.GetElapsedTime() ;
    
        DTIME = TIME - TIME_LAST;
        TIME_LAST = TIME;
    
    
        User.move(FORWARD);
        glutPostRedisplay();
    

    }
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

    
