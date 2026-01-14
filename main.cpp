#include <GL/glut.h>
#include <stdio.h>
#include <string.h>
#include <cmath>
#include <math.h>

int screen = 0;
int rotorOn = 0;
int moveOn  = 0;

float heliX = -0.65f, heliY = -0.75f;
float speed = 0.02f;
float rotorAngle = 0.0f;

//DRAW TEXT
void printText(float x, float y, void *font, const char *str){
    glRasterPos2f(x, y);
    for(int i=0; str[i] != '\0'; i++)
        glutBitmapCharacter(font, str[i]);
}

//INTRO SCREEN
void drawIntro(){
    glClearColor(0.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(0,0,0);
    printText(-0.33f,0.85f,GLUT_BITMAP_TIMES_ROMAN_24,"Computer Graphics Project");
    printText(-0.33f,0.75f,GLUT_BITMAP_TIMES_ROMAN_24,"HELICOPTER GAME");

    printText(-0.65f,0.45f,GLUT_BITMAP_HELVETICA_18,"Submitted by:");
    printText(-0.65f,0.35f,GLUT_BITMAP_HELVETICA_18,"Name : Rahat Sarkar");
    printText(-0.65f,0.25f,GLUT_BITMAP_HELVETICA_18,"ID: 223311248");
    printText(-0.65f,0.15f,GLUT_BITMAP_HELVETICA_18,"Section : B ");
    printText(-0.65f,-0.10f,GLUT_BITMAP_HELVETICA_18,"Submitted TO:");
    printText(-0.65f,-0.20f,GLUT_BITMAP_HELVETICA_18," Mohsiul Mumit Alik ");
    printText(-0.65f,-0.25f,GLUT_BITMAP_HELVETICA_18," Lecturer in Department of Computer Science and Engineering,Varendra University. ");
    printText(-0.35f,-0.80f,GLUT_BITMAP_HELVETICA_18,"For instructions press : n");

    glutSwapBuffers();
}

//INSTRUCTIONS SCREEN
void drawInstructions(){
    glClearColor(0.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0,0,0);

    printText(-0.10f, 0.8f, GLUT_BITMAP_TIMES_ROMAN_24, "Instructions");
    printText(-0.55f, 0.55f, GLUT_BITMAP_HELVETICA_18, "s : Start/Stop ");
    printText(-0.55f, 0.45f, GLUT_BITMAP_HELVETICA_18, "m : Toggle movement ");
    printText(-0.55f, 0.35f, GLUT_BITMAP_HELVETICA_18, "h : increase speed");
    printText(-0.55f, 0.25f, GLUT_BITMAP_HELVETICA_18, "l : decrease speed");
    printText(-0.55f, 0.15f, GLUT_BITMAP_HELVETICA_18, "r : move right");
    printText(-0.55f, 0.05f, GLUT_BITMAP_HELVETICA_18, "b : move left");
    printText(-0.55f, -0.05f,GLUT_BITMAP_HELVETICA_18, "u : move up");
    printText(-0.55f, -0.15f,GLUT_BITMAP_HELVETICA_18, "d : move down");
    printText(-0.55f, -0.25f,GLUT_BITMAP_HELVETICA_18, "q : quit");

    printText(-0.25f, -0.70f, GLUT_BITMAP_HELVETICA_18, "for next press : c");
    glutSwapBuffers();
}
void drawEnvironment(){
    glBegin(GL_QUADS);
    glColor3f(0.5f,0.9f,1.0f);
    glVertex2f(-1,-0.80f);
    glVertex2f(1,-0.80f);
    glVertex2f(1,1);
    glVertex2f(-1,1);
    glEnd();
//Ground
    glBegin(GL_QUADS);
    glColor3f(0,0.6f,0);
    glVertex2f(-1,-1);
    glVertex2f(1,-1);
    glVertex2f(1,-0.80f);
    glVertex2f(-1,-0.80f);
    glEnd();
}

//HELICOPTER
void drawHelicopter(){
    glPushMatrix();
    glTranslatef(heliX, heliY, 0);

    glScalef(0.55f, 0.55f, 1.0f);
    glScalef(-1.0f, 1.0f, 1.0f);

    glColor3f(1.0, 0.95, 0.0);
    glBegin(GL_POLYGON);
    glVertex2f(-0.25f, 0.02f);
    glVertex2f( 0.10f, 0.02f);
    glVertex2f( 0.10f, 0.16f);
    glVertex2f(-0.18f, 0.16f);
    glEnd();

    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_POLYGON);
    glVertex2f(0.10f,0.02f);
    glVertex2f(0.22f,0.02f);
    glVertex2f(0.34f,0.08f);
    glVertex2f(0.22f,0.16f);
    glVertex2f(0.10f,0.16f);
    glEnd();

    glColor3f(0,0,0);
    glBegin(GL_POLYGON);
    glVertex2f(-0.23f,0.02f);
    glVertex2f(-0.02f,0.02f);
    glVertex2f( 0.05f,0.14f);
    glVertex2f(-0.12f,0.14f);
    glEnd();

    glColor3f(0,0,0);
    glBegin(GL_QUADS);
    glVertex2f(0.00f,0.12f);
    glVertex2f(0.07f,0.12f);
    glVertex2f(0.07f,0.07f);
    glVertex2f(0.00f,0.07f);
    glEnd();

    glColor3f(1.0,0.9,0.0);
    glBegin(GL_QUADS);
    glVertex2f(-0.22f,0.05f);
    glVertex2f(0.15f,0.05f);
    glVertex2f(0.15f,0.03f);
    glVertex2f(-0.22f,0.03f);
    glEnd();

    glColor3f(1,0,0);
    glBegin(GL_POLYGON);
    glVertex2f(0.34f,0.08f);
    glVertex2f(0.50f,0.10f);
    glVertex2f(0.52f,0.13f);
    glVertex2f(0.50f,0.07f);
    glEnd();

    glColor3f(0,0,0);
    glBegin(GL_LINE_LOOP);
    for(int i=0; i<360; i++){
        float a=i*3.14/180;
        glVertex2f(0.50f + 0.06*cos(a), 0.10f + 0.06*sin(a));
    }
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(0.50f,0.16f);
    glVertex2f(0.50f,0.04f);
    glVertex2f(0.44f,0.10f);
    glVertex2f(0.56f,0.10f);
    glEnd();

    glPushMatrix();
    glTranslatef(0.05f,0.18f,0);

    if(rotorOn)
        glRotatef(rotorAngle,0,0,1);

    glColor3f(0,0,0);
    glBegin(GL_QUADS);
    glVertex2f(-0.60f,-0.02f);
    glVertex2f(0.60f,-0.02f);
    glVertex2f(0.60f,0.02f);
    glVertex2f(-0.60f,0.02f);
    glEnd();
    glPopMatrix();

    glColor3f(0,0,0);
    glBegin(GL_LINES);
    glVertex2f(-0.12f,0.00f);
    glVertex2f(0.12f,0.00f);
    glVertex2f(-0.10f,0.00f);
    glVertex2f(-0.05f,-0.05f);
    glVertex2f(0.10f, 0.00f);
    glVertex2f(0.05f,-0.05f);
    glEnd();

    glPopMatrix();
}

//MAIN GAME DRAW
void drawGame(){
    glClear(GL_COLOR_BUFFER_BIT);
    drawEnvironment();
    drawHelicopter();
    glutSwapBuffers();
}
void timer(int v){
    if(rotorOn) rotorAngle += 12;
    glutPostRedisplay();
    glutTimerFunc(30,timer,0);
}
void keyboard(unsigned char key,int x,int y){
    if(screen==0 && key=='n') screen=1;
    else if(screen==1 && key=='c') screen=2;
    else if(screen==2)
    {
        if(key=='q') exit(0);
        if(key=='s') rotorOn = !rotorOn;
        if(key=='m') moveOn  = !moveOn;
        if(key=='h') speed += 0.01;
        if(key=='l' && speed>0.01) speed -= 0.01;

        if(moveOn)
        {
            if(key=='r') heliX += speed;
            if(key=='b') heliX -= speed;
            if(key=='u') heliY += speed;
            if(key=='d') heliY -= speed;
        }
    }
    glutPostRedisplay();
}

//DISPLAY SELECTOR
void display(){
    if(screen==0) drawIntro();
    else if(screen==1) drawInstructions();
    else drawGame();
}

int main(int argc,char **argv){
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);
    glutInitWindowSize(900,600);
    glutCreateWindow("CGV MINI PROJECT - Helicopter");

    glClearColor(0.5f,0.9f,1.0f,1);
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutTimerFunc(0,timer,0);

    glutMainLoop();
}
