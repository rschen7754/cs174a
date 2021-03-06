//
//  main.cpp
//  Final Project
//
//  Created by rschen7754 on 5/24/13.
//
//

#include "main.h"
#include <sstream>
#include <string>



//==============================================


// quad generates two triangles for each face and assigns colors
//    to the vertices

//For whatever reason when we use this version of the code the rectangles (say the ship) draw really strangely. Commenting out for now.

void quad( int a, int b, int c, int d, point4 vertices[], point4 points[], const vec3& normal, vec3 cubeNormals[])
{
    points[Index] = vertices[a];
    cubeNormals[Index] = normal;
    //  cubeUV[Index] = point2(0.0f, 1.0f);
    Index++;
    points[Index] = vertices[b];
    cubeNormals[Index] = normal;
    // cubeUV[Index] = point2(0.0f, 0.0f);
    Index++;
    points[Index] = vertices[c];
    cubeNormals[Index] = normal;
    // cubeUV[Index] = point2(1.0f, 0.0f);
    Index++;
    points[Index] = vertices[a];
    cubeNormals[Index] = normal;
    //  cubeUV[Index] = point2(0.0f, 1.0f);
    Index++;
    points[Index] = vertices[c];
    cubeNormals[Index] = normal;
    // cubeUV[Index] = point2(1.0f, 0.0f);
    Index++;
    points[Index] = vertices[d];
    cubeNormals[Index] = normal;
    // cubeUV[Index] = point2(1.0f, 1.0f);
    Index++;
    
    
}
/*
 void quad( int a, int b, int c, int d, point4 vertices[], point4 points[], const point3& normal)
 {
 points[Index] = vertices[a]; Index++;
 points[Index] = vertices[b]; Index++;
 points[Index] = vertices[c]; Index++;
 points[Index] = vertices[a]; Index++;
 points[Index] = vertices[c]; Index++;
 points[Index] = vertices[d]; Index++;
 
 }
 */



// Creates a cube given a set of vertices and color
void colorcube(point4 vertices[], int indexColor, point4 points[], vec3 normals[])
{
    quad( 1, 0, 3, 2, vertices, points, vec3( 0.0f,  0.0f,  1.0f), normals );
    quad( 2, 3, 7, 6, vertices, points, vec3( 1.0f,  0.0f,  0.0f) , normals);
    quad( 3, 0, 4, 7, vertices, points, vec3( 0.0f, -1.0f,  0.0f), normals );
    quad( 6, 5, 1, 2, vertices, points, vec3( 0.0f,  1.0f,  0.0f) , normals);
    quad( 4, 5, 6, 7, vertices, points, vec3( 0.0f,  0.0f, -1.0f), normals );
    quad( 5, 4, 0, 1, vertices, points, vec3(-1.0f,  0.0f,  0.0f) , normals);
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

void intializeRectangle(GLfloat x, GLfloat y, GLfloat z, GLfloat width, GLfloat height,GLfloat length,  point4 points[], vec3 normals[])
{
    Index = 0;
    createCube(cube, x, y, z,width,height, length);
    colorcube(cube, 0, points, normals);
}



//======================================

// Player Class that handles the user
class Player {
public:
    Player(int x, int y);
    
    // Reinitializes the Player
    void reinitializePlayer();
    
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
    
    // Get the x position of the ship
    GLfloat getX();
    
    // Get the value of the width counter
    GLfloat getOldX();
    
    GLfloat getZ();
    
    // Round Positions to Integer Value
    void RoundPositions(int animation);
    
    // Draw Ship
    void draw();
    
private:
    // Position of the player
    GLfloat m_posx;
    GLfloat m_posy;
    GLfloat m_posz;
    
    bool m_isAlive;
    int m_animationStatus;
    int m_heightLevel;
    GLfloat m_oldx;
    
    
};

Player::Player(int x, int y)
{
    
    m_posx = 0;
    m_posy = 0;
    m_posz = 0;
    
    m_isAlive = true;
    m_heightLevel = HEIGHT_CENTER;
    m_animationStatus = ANIMATE_NONE;
    m_oldx = m_posx;
    
    // Initialize Ship Rectangles
    intializeRectangle(x, y, -20, 0,0,10, shipCenter, shipCenterNormals);
    intializeRectangle(x + 5, y, -20 +3, 0, -2,5, shipleft, shipleftNormals);
    intializeRectangle(x-5, y, -20 +3, 0, -2, 5, shipRight, shipRightNormals);
    
}

void Player::reinitializePlayer()
{
    //    m_posx = 0;
    //    m_posy = 0;
    //    m_posz = 0;
    health=10;
    m_isAlive = true;
    m_heightLevel = HEIGHT_CENTER;
    m_animationStatus = ANIMATE_NONE;
    m_oldx = m_posx;
    
    
}

void Player::move(int dir)
{
    GLfloat speed = 1.7;
    
    GLfloat movement = DTIME*250*speed;
    
    
    if (dir == UP) {
        m_posy += movement;
        pos_y -= movement;
    }else if (dir == DOWN){
        m_posy -= movement;
        pos_y += movement;
    }else if (dir == LEFT){
        if (m_posx > mapWidthLeft) {
            m_posx -= movement;
            pos_x += movement;
        }else{
            health = 0;
            setDead();
        }
        
    }else if (dir == RIGHT){
        if (m_posx < mapWidthRight) {
            m_posx += movement;
            pos_x -= movement;
        }else{
            health = 0;
            setDead();
        }
        
    }else if (dir == FORWARD){
        m_posz -= movement/speed;
        pos_z += movement/speed;
        
    }
}

int Player::getHeightLevel()
{
    return m_heightLevel;
}

GLfloat Player::getZ()
{
    return m_posz;
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
    if(status == ANIMATE_LEFT || status == ANIMATE_RIGHT)
    {
        m_oldx = m_posx;
    }
    m_animationStatus = status;
    
}

GLfloat Player::getOldX()
{
    return m_oldx;
}

GLfloat Player::getY(){
    return m_posy;
}

GLfloat Player::getX(){
    return m_posx;
}

void Player::setDead(){
    m_isAlive = false;
}

bool Player::isAlive(){
    return m_isAlive;
}

void Player::RoundPositions(int animation)
{
    
    if (animation == ANIMATE_LEFT) {
        m_posx = getOldX() - 25;
    }else if (animation == ANIMATE_RIGHT)
    {
        m_posx = getOldX() + 25;
    }else
    {
        if (getHeightLevel() == HEIGHT_TOP) {
            m_posy = 15;
        }else if (getHeightLevel() == HEIGHT_CENTER)
        {
            m_posy = 0;
        }else{
            m_posy = -15;
        }
    }
    
    
    pos_x = -m_posx - 2.0;
    pos_y = -m_posy -15.0;
    
    
}

bool Player:: didCollide(){
    if (menuState==MENU_ON || menuState==MENU_OVER)
        return false;
    
    std::vector<cubePos>::iterator it = blocks.begin();
    for (int i = 0; i < blocks.size(); i++) {
        
        
        if ((m_posx+5 >= blocks[i].x && m_posx-5 <= blocks[i].x+5) &&
            (m_posy + 5 > blocks[i].y && m_posy < blocks[i].y+5)&&
            (m_posz -30< blocks[i].z && m_posz > blocks[i].z+5)) {
			health--;
            
            if (health <= 0)
			{
				setDead();
				menuState = MENU_OVER;
                
			}else{
                it+=i;
                blocks.erase(it);
            }
            return true;
        }
        
        
        
    }
    
    if ((m_posz*-1) >= end) {
        
        setDead();
        menuState = MENU_OVER;
    }
    
    return false;
}



void Player::draw(){
    drawRectangle(shipleft, shipleftNormals, COLOR_BLUE, m_posx, m_posy, m_posz, 0);
    drawRectangle(shipCenter,shipCenterNormals, COLOR_GREY, m_posx, m_posy, m_posz, 0);
    drawRectangle(shipRight, shipRightNormals, COLOR_BLUE, m_posx, m_posy, m_posz, 0);
}

// Initialize Player
Player User(0,0);

// Draws a rectangle
void drawRectangle(point4 points[], vec3 normals[], vec4 fColor, GLfloat x, GLfloat y, GLfloat z, int texture)
{
    
    glUseProgram(program);
    
    // Create and initialize a buffer object
    glBufferData( GL_ARRAY_BUFFER, sizeof(point4)*NumVertices + sizeof(vec3)*NumVertices, NULL, GL_STATIC_DRAW );
    glBufferSubData( GL_ARRAY_BUFFER, 0, sizeof(point4)*NumVertices, points );
    glBufferSubData(GL_ARRAY_BUFFER, sizeof(point4)*NumVertices, sizeof(vec3)*NumVertices, normals);
    
    glEnableVertexAttribArray(vPosition);
    glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0) );
    glEnableVertexAttribArray( vNormal );
    glVertexAttribPointer( vNormal, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(point4)*NumVertices) );
    
    // Collin's Light Code ========================================================
    
    point4 light_position( User.getX(), User.getY()+10, User.getZ()-100, 1.0 );
    glUniform4fv( glGetUniformLocation(program, "LightPosition"), 1, light_position );
    
    
    // Collin's Light Code ========================================================
    
    // Create model_view matrix to transform and rotate the cubes
    mat4 transform = Translate(x, y, z);
    glUniformMatrix4fv(glGetUniformLocation(program, "Transformation"), 1,GL_TRUE,transform);
    
    mat4  mv =Translate(pos_x, pos_y,pos_z);
    glUniformMatrix4fv( ModelView, 1, GL_TRUE, mv );
    
    // Define a viewing box
    mat4 p = Perspective(45, aspect, zNear, zFar);
    glUniformMatrix4fv( Projection, 1, GL_TRUE, p );
    glUniform4fv(glGetUniformLocation(program, "fcolor"), 1, fColor);
    
    //    if (texture==1) {
    //        glBindTexture( GL_TEXTURE_2D, texture_cube );
    //        glUniform1i( uEnableTex, 1 );
    //    }
    // Draw proper items
    glDrawArrays( GL_TRIANGLES, 0, NumVertices );
    
    glUniform1i( uEnableTex, 0 );
    
}





void init() {
    
    // Initialize 5x5 Blocks
    intializeRectangle(0, 0, 0, 0, 0, 0, blockModel, blockModelNormals);
    
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
    end = storeBlocks(xPos, yPos, zPos);
	int numBlocks = xPos.size();
    
    // Assume first and last are the widths of the field:
    mapWidthLeft = xPos[0]+25;
    mapWidthRight = xPos[xPos.size()-1]+25;

    
	for (int i = 0; i < numBlocks; i++)
	{
		cubePos tempBlock;
		tempBlock.x = -xPos[i];
		tempBlock.y = yPos[i];
		tempBlock.z = -zPos[i];
		blocks.push_back(tempBlock);
        
	}
    
    vPosition = glGetAttribLocation(program, "vPosition");
    vNormal = glGetAttribLocation(program, "vNormal");
    
    ModelView = glGetUniformLocation( program, "ModelView" );
    Projection = glGetUniformLocation( program, "Projection" );
    
    // Place test blocks into blocks vector for collision detection
    
    
    
    TgaImage cubeImage;
    if (!cubeImage.loadTGA("cube_Texture2.tga"))
    {
        printf("Error loading image file menu\n");
        exit(1);
    }
    
    //load first texture
    glGenTextures( 1, &texture_cube );
    glBindTexture( GL_TEXTURE_2D, texture_cube );
    glTexImage2D(GL_TEXTURE_2D, 0, 4, cubeImage.width, cubeImage.height, 0,
                 (cubeImage.byteCount == 3) ? GL_BGR : GL_BGRA,
                 GL_UNSIGNED_BYTE, cubeImage.data );
    glGenerateMipmap(GL_TEXTURE_2D);
    
    //nearest filtering
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    
    // Set texture sampler variable to texture unit 0
    // (set in glActiveTexture(GL_TEXTURE0))
    
    glUniform1i( uTex, 0);
    
    
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
    
    // Set black background
    glClearColor( 0.0, 0.0, 0.0, 1.0 );
    //   glClearColor( 1.0, 1.0, 1.0, 1.0 );
}

void set_colour(float r, float g, float b)
{
    float ambient  = 0.2f;
    float diffuse  = 0.6f;
    float specular = 0.2f;
    glUniform4f(uAmbient,  ambient*r,  ambient*g,  ambient*b,  1.0f);
    glUniform4f(uDiffuse,  diffuse*r,  diffuse*g,  diffuse*b,  1.0f);
    glUniform4f(uSpecular, specular*r, specular*g, specular*b, 1.0f);
}

void glutPrint(float x, float y, float z, std::string text, float r, float g, float b, float a)
{
    bool blending = false;
    if(glIsEnabled(GL_BLEND)) blending = true;
    glEnable(GL_BLEND);
    glUniform4fv(glGetUniformLocation(program, "fcolor"), 1, color4(r,g,b,a));
    //glRasterPos2f(x,y);
    glRasterPos3f(x, y, z);
    
    for (int i = 0; i < text.size(); i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
    }
    if(!blending) glDisable(GL_BLEND);
}

void displayHandler() {
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    
    mat4 p;
    
    // Draw the map
    for (int i = 0; i < blocks.size(); i++) {
        drawRectangle(blockModel, blockModelNormals, vec4(0.0,1.0,0.0,1.0), blocks[i].x, blocks[i].y, blocks[i].z, 1);
    }
    
    // Handles the animation for the ship
    if (User.getAnimationStatus() == ANIMATE_UP) {
        if (User.getHeightLevel() == HEIGHT_BOTTOM) {
            if (User.getY() <=0) {
                User.move(UP);
            }else{
                User.setHeightLevel(HEIGHT_CENTER);
                User.setAnimationStatus(ANIMATE_NONE);
                User.RoundPositions(ANIMATE_UP);
            }
        }
        else if(User.getHeightLevel() == HEIGHT_CENTER){
            if (User.getY() <=15) {
                User.move(UP);
            }else{
                User.setHeightLevel(HEIGHT_TOP);
                User.setAnimationStatus(ANIMATE_NONE);
                User.RoundPositions(ANIMATE_UP);
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
                User.RoundPositions(ANIMATE_DOWN);
            }
        }else if (User.getHeightLevel() == HEIGHT_CENTER)
        {
            if (User.getY() >= -15) {
                User.move(DOWN);
            }else{
                User.setHeightLevel(HEIGHT_BOTTOM);
                User.setAnimationStatus(ANIMATE_NONE);
                User.RoundPositions(ANIMATE_DOWN);
            }
        }
        else
            User.setAnimationStatus(ANIMATE_NONE);
    }else if (User.getAnimationStatus() == ANIMATE_LEFT){
        if (static_cast<int>(User.getX())  >= static_cast<int>(User.getOldX()) - 24) {
            User.move(LEFT);
        }else{
            User.setAnimationStatus(ANIMATE_NONE);
            User.RoundPositions(ANIMATE_LEFT);
        }
    }else if (User.getAnimationStatus() == ANIMATE_RIGHT)
    {
        if (static_cast<int>(User.getX())  <= static_cast<int>(User.getOldX())  + 24) {
            User.move(RIGHT);
        }else{
            User.setAnimationStatus(ANIMATE_NONE);
            User.RoundPositions(ANIMATE_RIGHT);
        }
    }
    
    // Draw the ship
    User.draw();
    
    // Determine the score
    // Display the Score
    std::stringstream ss;
    ss <<"Score: " << SCORE;
    
	//Display health
	std::stringstream healthDisp;
    healthDisp <<"Lives: " << health;
    
    //draw menu
    if (menuState==MENU_ON || menuState == MENU_OVER) {
        
        
        //orthographic projection
        p = Ortho(2*left, 2*right, 2*bottom, 2*top, zNear, zFar);
        glUniformMatrix4fv( Projection, 1, GL_TRUE, p );
        
        
        mat4 mv =Translate(pos_x-3, pos_y+25,pos_z);
        
        glUniformMatrix4fv( ModelView, 1, GL_TRUE, mv );
        
        glutPrint(-5.5,30,User.getZ(), "Welcome to SpaceRunner!", 1, 1, 1, 1);
        
        mv =Translate(pos_x-2, pos_y+20,pos_z);
        glUniformMatrix4fv( ModelView, 1, GL_TRUE, mv );
        glutPrint(-4.5,17,User.getZ(), "Press Enter to begin.", 1, 1, 1, 1);
        
    }
    
    else {
        //should go inside else
        
        User.didCollide();
    }
    
    if ((User.getZ()*-1) >= end) {
        mat4 mv=ModelView*Translate(pos_x+0.1, pos_y+10,pos_z);
        glUniformMatrix4fv( ModelView, 1, GL_TRUE, mv );
        glutPrint(-1.8 , 35,-50, "You won!", 1.0, 1.0, 1.0, 1.0);
        
        mv=ModelView*Translate(pos_x-5, pos_y,pos_z);
        glUniformMatrix4fv( ModelView, 1, GL_TRUE, mv );
        
        glutPrint(-3 , 25,-50, ss.str(), 1.0, 1.0, 1.0, 1.0);
        
        
        mv=ModelView*Translate(pos_x+5, pos_y,pos_z);
        glUniformMatrix4fv( ModelView, 1, GL_TRUE, mv );
        glutPrint(-25, 35, -50,healthDisp.str(), 1.0, 1.0, 1.0, 1.0);
    }
    else if (!User.isAlive()) {
        mat4 mv=ModelView*Translate(pos_x, pos_y+10,pos_z);
        glUniformMatrix4fv( ModelView, 1, GL_TRUE, mv );
        glutPrint(-1.8 , 35,-50, "Game Over", 1.0, 1.0, 1.0, 1.0);
        
        mv=ModelView*Translate(pos_x-5, pos_y,pos_z);
        glUniformMatrix4fv( ModelView, 1, GL_TRUE, mv );
        glutPrint(-3 , 25,-50, ss.str(), 1.0, 1.0, 1.0, 1.0);
        
        mv=ModelView*Translate(pos_x+5, pos_y,pos_z);
        glUniformMatrix4fv( ModelView, 1, GL_TRUE, mv );
        glutPrint(-25, 35, -50,"Lives: 0", 1.0, 1.0, 1.0, 1.0);
        
    }else{
        mat4 mv=ModelView*Translate(pos_x-5, pos_y,pos_z);
        glUniformMatrix4fv( ModelView, 1, GL_TRUE, mv );
        glutPrint(0, 45, -20,ss.str(), 1.0, 1.0, 1.0, 1.0);
        
        mv=ModelView*Translate(pos_x+5, pos_y,pos_z);
        glUniformMatrix4fv( ModelView, 1, GL_TRUE, mv );
		glutPrint(-25, 35, -20,healthDisp.str(), 1.0, 1.0, 1.0, 1.0);
    }
    
    
    
    
    glutSwapBuffers();
}

void keyHandler(unsigned char key, int x, int y) {
    
    if (menuState != MENU_PLAY && key != 'q' && key != 'Q' && key != 13)
        return;
    
    switch (key) {
            
            
            
        case 'q':
        case 'Q':
            exit(0);
            break;
            
        case 13: //hitting enter
            if (menuState != MENU_PLAY) {
                menuState = MENU_PLAY;
                TM.Reset();
                User.reinitializePlayer();
                TIME = 0;
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
    if (User.getAnimationStatus() == ANIMATE_NONE) {
        switch (key) {
                
            case GLUT_KEY_UP: // Moves the camera up
                if (User.getHeightLevel() != HEIGHT_TOP) {
                    User.setAnimationStatus(ANIMATE_UP);
                }
                break;
            case GLUT_KEY_DOWN: // Moves the camera down
                if (User.getHeightLevel() != HEIGHT_BOTTOM) {
                    User.setAnimationStatus(ANIMATE_DOWN);
                }
                break;
            case GLUT_KEY_LEFT: // Turns the camera left
                User.setAnimationStatus(ANIMATE_LEFT);
                break;
            case GLUT_KEY_RIGHT: // Turns the camera right
                User.setAnimationStatus(ANIMATE_RIGHT);
                break;
                
            default:
                break;
                
        }
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
        SCORE += DTIME*100;
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
    glutCreateWindow( "SpaceRunner");
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


