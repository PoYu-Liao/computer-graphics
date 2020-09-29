#include <GL/glut.h>
#include <stdio.h>
#include "glm.h"
#include <mmsystem.h>
#include "CMP3_MCI.h"

FILE * fout=NULL;
FILE * fin=NULL;
GLMmodel * pmodel =NULL;
GLMmodel * pmodel1 =NULL;
GLMmodel * pmodel2 =NULL;
GLMmodel * pmodel3 =NULL;
GLMmodel * pmodel4 =NULL;
GLMmodel * pmodel5 =NULL;
GLMmodel * pmodel6 =NULL;
CMP3_MCI myMP3;
float angle[10]= {0,0,0,0,0,0,0,0,0,0 };
float oldAngle[10],newAngle[10];
int oldX=0, oldY=0,  now=0;


void timer(int t)
{
    glutTimerFunc(5,timer,t+1);
    if(t%5==0)
    {
        if(fin==NULL) fin=fopen("output.txt","r");
        for(int i=0; i<10; i++)
        {
            oldAngle[i] = newAngle[i];
            fscanf(fin,"%f", &newAngle[i]);
        }
    }
    float alpha = (t%5)/5.0;
    for(int i=0; i<10; i++)
    {
        angle[i] = newAngle[i]*alpha + oldAngle[i]*(1-alpha);
    }
    glutPostRedisplay();
}
void keyboard(unsigned char key, int x, int y)
{
    if (key=='1') now=1;
    if (key=='2') now=2;



    if(key=='p' || key=='P')
    {

        myMP3.Play();
        if(fin==NULL) fin=fopen("output.txt", "r");
        for(int i=0; i<10; i++)
        {
            fscanf(fin, "%f", &newAngle[i]);
        }
        angle[1]=0.0;
        angle[2]=0.0;
        glutTimerFunc(0.000000000001, timer, 0);


    }

    glutPostRedisplay();

}
void mouse(int button, int state, int x, int y)
{
    if(button==2 && state==0)
    {
        myMP3.Pause();
    }
    if(button==1 && state==0)
    {
        myMP3.Stop();
    }


    oldX=x;
    oldY=y;
}
void resize(int width, int height)
{
    const float ar = (float) width / (float) height;

    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-ar, ar, -1.0, 1.0, 2.0, 100.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0,1,-3,  0,0,0, 0,1,0);
}

void motion(int x, int y)
{

    angle[now] += x-oldX;
    oldX=x;
    if(fout==NULL) fout=fopen("output.txt","w+");
    for(int i=0;i<10;i++){
    printf("%.1f",angle[i]);
    fprintf(fout,"%.1f \n",angle[i]);
    }
    printf("\n");fprintf(fout,"\n");

    glutPostRedisplay();
}

///打光用
const GLfloat light_ambient[]  = { 0.2f, 0.2f, 0.2f, 0.8f };
const GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_specular[] = { 0.4f, 0.4f, 0.4f, 0.4f };
const GLfloat light_position[] = { 2.0f, 1.0f, 10.0f, 0.0f };
///x     y     z
const GLfloat mat_ambient[]    = { 0.8f, 0.8f, 0.8f, 1.0f };
const GLfloat mat_diffuse[]    = { 1.0f, 0.8f, 0.8f, 1.0f };
const GLfloat mat_specular[]   = { 1.0f, 1.0f, 3.0f, 1.0f };
const GLfloat high_shininess[] = { 10.0f };

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glEnd();
    glPushMatrix();
        //glScalef (0.5, 0.5, 0.5);
        glTranslatef(0,0.2,0);

    ///身體
    if (!pmodel) {
         pmodel = glmReadOBJ("2B/body.obj");
         if (!pmodel) exit(0);
         glmUnitize(pmodel);
         glmFacetNormals(pmodel);
         glmVertexNormals(pmodel, 90.0);
    }
    glmDraw(pmodel, GLM_SMOOTH | GLM_MATERIAL);
    glPopMatrix();

    glPushMatrix();
        glScalef (1.6, 1.6, 1.6);
        glTranslatef(-0.18,0.58,0);

    ///頭
    if (!pmodel1) {
         pmodel1 = glmReadOBJ("2B/head.obj");
         if (!pmodel1) exit(0);
         glmUnitize(pmodel1);
         glmFacetNormals(pmodel1);
         glmVertexNormals(pmodel1, 90.0);
    }
     glmDraw(pmodel1, GLM_SMOOTH | GLM_MATERIAL);
     glPopMatrix();

    glPushMatrix();
        //glScalef (0.4, 0.4, 0.4);
        glTranslatef(0,0.2,0);

    ///身體外裝
    if (!pmodel2) {
         pmodel2 = glmReadOBJ("2B/body2.obj");
         if (!pmodel2) exit(0);
         glmUnitize(pmodel2);
         glmFacetNormals(pmodel2);
         glmVertexNormals(pmodel2, 90.0);
    }
     glmDraw(pmodel2, GLM_SMOOTH | GLM_MATERIAL);
     glPopMatrix();

    ///左腳
    glPushMatrix();
        glScalef (0.7, 0.7, 0.7);
        glTranslatef(-0.5,-0.3,0);
        glRotatef(angle[4],0,0,1);
        //glTranslatef(-0.5,-0.3,0);
    if (!pmodel3) {
         pmodel3 = glmReadOBJ("2B/lfoot.obj");
         if (!pmodel3) exit(0);
         glmUnitize(pmodel3);
         glmFacetNormals(pmodel3);
         glmVertexNormals(pmodel3, 90.0);
    }
     glmDraw(pmodel3, GLM_SMOOTH | GLM_MATERIAL);
     glPopMatrix();

     ///右腳
    glPushMatrix();
        glScalef (0.7, 0.7, 0.7);
        glTranslatef(-0.4,-0.3,0);
        glRotatef(angle[5],0,0,1);
    if (!pmodel4) {
         pmodel4 = glmReadOBJ("2B/rfoot.obj");
         if (!pmodel4) exit(0);
         glmUnitize(pmodel4);
         glmFacetNormals(pmodel4);
         glmVertexNormals(pmodel4, 90.0);
    }
     glmDraw(pmodel4, GLM_SMOOTH | GLM_MATERIAL);
     glPopMatrix();

    ///右手
    glPushMatrix();
        //glScalef (0.5, 0.5, 0.5);
        glTranslatef(0.2,0.9,0);
        glRotatef(angle[1],0,0,1);
        glTranslatef(0.18,-0.75,0);
    if (!pmodel5) {
         pmodel5 = glmReadOBJ("2B/rhand.obj");
         if (!pmodel5) exit(0);
         glmUnitize(pmodel5);
         glmFacetNormals(pmodel5);
         glmVertexNormals(pmodel5, 90.0);
    }
     glmDraw(pmodel5, GLM_SMOOTH | GLM_MATERIAL);
     glPopMatrix();

     ///左手
    glPushMatrix();
        glScalef (1.7, 1.7, 1.7);
        glTranslatef(-0.1,0.6,0);
        glRotatef(angle[2],0,0,1);
        glTranslatef(-0.17,-0.15,0);
    if (!pmodel6) {
         pmodel6 = glmReadOBJ("2B/lhand.obj");
         if (!pmodel6) exit(0);
         glmUnitize(pmodel6);
         glmFacetNormals(pmodel6);
         glmVertexNormals(pmodel6, 90.0);
    }
     glmDraw(pmodel6, GLM_SMOOTH | GLM_MATERIAL);
     glPopMatrix();





    glutSwapBuffers();
}

int main(int argc, char *argv[])
{

    myMP3.Load("7.mp3");

    glutInit(&argc, argv);
    glutInitWindowSize(800,600);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    glutCreateWindow("05160461graphicsfinal");


    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutKeyboardFunc(keyboard);


    glutReshapeFunc(resize);
    glutDisplayFunc(display);


    glClearColor(1,1,1,1);


    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);

    glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);

    glutMainLoop();

    return EXIT_SUCCESS;
}
