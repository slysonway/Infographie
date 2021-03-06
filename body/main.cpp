
/*********************************************************/
/*        TP1: primitives 2D et transformations          */
/*********************************************************/
/*                                                         */
/*       ESGI: Algorithmiques pour l'infographies         */
/*                                                         */
/*********************************************************/
/*                                                         */
/*  Objectif: afficher des formes 2D et les transformer  */
/*                                                         */
/*********************************************************/



//#ifdef __APPLE__
#include <GLUT/glut.h>
//#else
//#include <GL/glut.h>
//#endif


#include <stdlib.h>
#include <stdio.h>
#include <math.h>


void update(int value);

void drawQuads(float height, float width, float thickness);
void drawChin();




float angle = 0.0f; //angle bras
float angle2 = 0.0f;//angle avant bras

float angleT = 0.0f; //angle tête
float angleJ = 0.0f; //angle jambes
float angleJ2 = 0.0f; //angle bas jambes
float lightAngle = 0.0f;
float cameraAngle = 10.0;
//float X0 = 1;
float R = 15;
float beta = 0;
float teta = 0;
//float x0 = R * sin(teta) * beta;
//float Y0 = R * sin(beta);
//float z0 = R * cos(teta) * cos(beta);
float x0 = 0;
float Y0 = 0;
float z0 = 15;


/* prototypes de fonctions */
void initRendering();                           // Initialisation du rendu
void display();                             // modÈlisation
void reshape(int w,int h);                      // visualisation
void update(int value);                         // mise ‡ jour: appelle Timer pour l'animation de la scËne
void keyboard(unsigned char key, int x, int y); // fonction clavier


/* Programme principal */
int main(int argc,       // argc: nombre d'arguments, argc vaut au moins 1
         char **argv){  // argv: tableau de chaines de caractËres, argv[0] contient le nom du programme lancÈ (plus un Èventuel chemin)
    
    
    /* Initialisation de glut et creation de la fenetre */
    glutInit(&argc, argv);                       // Initialisation
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH); // mode d'affichage RGB, et test prafondeur
    glutInitWindowSize(500, 500);                // dimension fenÍtre
    glutInitWindowPosition (100, 100);           // position coin haut gauche
    glutCreateWindow("TP1: formes 2D et transformation");  // nom
    
    /* Initialisation d'OpenGL */
    initRendering();
    
    /* Enregistrement des fonctions de rappel
     => initialisation des fonctions callback appelÈes par glut */
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutTimerFunc (20,update, 0);
    glutKeyboardFunc(keyboard);
    
    //glutTimerFunc(20, update, 0);
    
    /* rq: le callback de fonction (fonction de rappel) est une fonction qui est passÈe en argument ‡ une
     autre fonction. Ici, le main fait usage des deux fonctions de rappel (qui fonctionnent en mÍme temps)
     alors qu'il ne les connaÓt pas par avance.*/
    
    
    /* EntrÈe dans la boucle principale de glut, traitement des ÈvËnements */
    glutMainLoop();         // lancement de la boucle de rÈception des ÈvËnements
    return 0;               // pour finir
}


/* Initialisation d'OpenGL pour le rendu de la scËne */
void initRendering() {
    
    /* Active le z-buffer */
    glEnable(GL_DEPTH_TEST);
    
    /* Activation des couleurs */
    glEnable(GL_COLOR_MATERIAL);
    
    /* dÈfinit la couleur d'effacement et la couleur de fond */
    glClearColor(0.0, 0.0, 0.0, 0.0);
    
    glEnable(GL_NORMALIZE);
    
    glShadeModel(GL_SMOOTH);
    /*  dÈfinit la taille d'un pixel*/
    glPointSize(2.0);
    
}

/* CrÈation de la scËne */
void display(){
    
    /* Efface les tampons de couleur et de profondeur de l'image avec la couleur de fond.
     rq: buffer: mÈmoire tampon, c'est donc une surface en memoire utilisÈe pour stocker une image*/
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    
    /* la mat de visualisation-modÈlisation est modifiable par dÈfaut */
    glMatrixMode(GL_MODELVIEW);
    
    /* on charge l'identitÈ dans la matrice de modÈlisation-visualisation*/
    glLoadIdentity();
    
    
    /* Permet de crÈer un point de vue. DÈfinit une matrice de modÈlisation-visualisation et la multiplie
     ‡ droite de lma matrice active, ici l'identitÈ*/
    //glRotatef(cameraAngle, 0.1, -0.1, 1.0);
    
    GLfloat ambientColor[] = {0.2f, 0.2f, 0.2f, 1.0f};   // Color (0.2, 0.2, 0.2)

    
    // Ajout lumiËre positionnelle L0
    GLfloat lightColor0[] = {1.0f, 1.0f, 1.0f, 1.0f};    // Color (0.5, 0.5, 0.5)
    GLfloat lightPos0[] = {-3.0f, 0.0f, 0.0f, 1.0f};      // Positioned at (4, 0, 8)
    
    gluLookAt(x0, Y0, z0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);     // vecteur d'orientation camÈra

    // Ajout lumiËre ambiante
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor);
    
    
    
    //cube file fer qui tourne lumiere
    glPushMatrix();
    glRotated(lightAngle, 0.0f, 1.0f, 0.0f);
    glTranslated(0.0f, 0.0f, -3.0f);
    glutWireCube(0.2f);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor0);        // lumiËre diffuse
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);
    glPopMatrix();
    
       // position
    
    //body
    drawQuads(6.0f, 4.0f, 1.0f);
    
    //right arm
    glPushMatrix();
    glTranslatef(0.0f, 3.0f, 0.0f);
    glRotatef(angle, -1.0f, 0.0f, 0.0f);
    glTranslatef(0.0f, -3.0f, 0.0f);
    glTranslated(2.5f, 1.5f, 0.0f);
    drawQuads(3.0f, 1.0f, 1.0f);
    //avant bras
    glTranslatef(0.0f, -1.5f, 0.0f);
    glRotatef(angle2, -1.0f, 0.0f, 0.0f);
    glTranslatef(0.0f, 1.5f, 0.0f);
    glTranslated(0.0f, -2.75f, 0.0f);
    drawQuads(2.5f, 1.0f, 1.0f);
    glPopMatrix();
    
    //left arm
    glPushMatrix();
    glTranslatef(0.0f, 3.0f, 0.0f);
    glRotatef(angle, -1.0f, 0.0f, 0.0f);
    glTranslatef(0.0f, -3.0f, 0.0f);
    glTranslated(-2.5f, 1.5f, 0.0f);
    drawQuads(3.0f, 1.0f, 1.0f);
    //avant bras
    glTranslatef(0.0f, -1.5f, 0.0f);
    glRotatef(angle2, -1.0f, 0.0f, 0.0f);
    glTranslatef(0.0f, 1.5f, 0.0f);
    glTranslated(0.0f, -2.75f, 0.0f);
    drawQuads(2.5f, 1.0f, 1.0f);
    glPopMatrix();

    
    //right leg
    glPushMatrix();
    glTranslatef(0.0f, -3.0f, 0.0f);
    glRotatef(angleJ, -1.0f, 0.0f, 0.0f);
    glTranslatef(0.0f, 3.0f, 0.0f);
    glTranslated(1.05f, -4.5f, 0.0f);
    drawQuads(3.0f, 1.9f, 1.0f);
    
    //bas jambe
    glTranslatef(0.0f, -1.5f, 0.0f);
    glRotatef(angleJ2, 1.0f, 0.0f, 0.0f);
    glTranslatef(0.0f, 1.5f, 0.0f);
    glTranslated(0.0f, -3.0f, 0.0f);
    drawQuads(3.0f, 1.8f, 1.0f);
    glPopMatrix();
    
    //left leg
    glPushMatrix();
    glTranslatef(0.0f, -3.0f, 0.0f);
    glRotatef(angleJ, -1.0f, 0.0f, 0.0f);
    glTranslatef(0.0f, 3.0f, 0.0f);
    glTranslated(-1.05f, -4.5f, 0.0f);
    drawQuads(3.0f, 1.9f, 1.0f);
    //bas jambe
    glTranslatef(0.0f, -1.5f, 0.0f);
    glRotatef(angleJ2, 1.0f, 0.0f, 0.0f);
    glTranslatef(0.0f, 1.5f, 0.0f);
    glTranslated(0.0f, -3.0f, 0.0f);
    drawQuads(3.0f, 1.8f, 1.0f);
    glPopMatrix();
    
    
    /*-----HEAD-------*/
    glPushMatrix();
    
    glRotatef(angleT, 0.0f, 1.0f, 0.0f);
    
    glTranslatef(0.0f, 5.0f, 0.5f);
    drawQuads(2.0f, 2.0f, 2.0f);
    
    //nose
    glTranslatef(0.0f, 0.0f, 1.05f);
    drawQuads(0.25f, 0.10f, 0.1f);
    glTranslatef(0.0f, -0.2f, 0.0f);
    drawQuads(0.1f, 0.25f, 0.1f);
    
    //hear
    glTranslatef(1.1f, 0.1f, -1.0f);
    drawQuads(0.5f, 0.25f, 0.1);
    glTranslatef(-2.2f, 0.0f, 0.0f);
    drawQuads(0.5f, 0.25f, 0.1);
    
    //Chin
    glTranslatef(1.1f, -1.9f, -0.05f);
    drawChin();
    glTranslatef(0.0f, -0.25, 1.0f);
    drawQuads(0.5f, 1.0f, 1.0f);
    
    //neck
    glTranslatef(0.0f, 1.25f, -1.5f);
    glRotatef(90.0f, 0.0f, 0.0f, 0.0f);
    gluCylinder(gluNewQuadric(), 0.5f, 0.5f, 1.0f, 10.0f, 10.0f);
    glPopMatrix();
    
    glutSwapBuffers();
    
    /* On force l'affichage */
    glFlush(); // nettoie les fenÍtres prÈcÈdentes
}

void drawArms() {
    glPushMatrix();
    gluCylinder(gluNewQuadric(), 0.5f, 0.4f, 2.0f, 20, 20);
    glPopMatrix();
}

void drawQuads(float height, float width, float thickness) {
    
    glPushMatrix();
    glBegin(GL_QUADS);
    glColor3f(1.0f, 1.0f, 0.0f);
    
    //front
    //glColor3f(1.0f, 0.0f, 0.0f);
    glNormal3f(0.0f, 0.0f, 1.0f);
    glVertex3f(width / 2.0f, height / 2.0f, thickness / 2.0f);
    glVertex3f(width / 2.0f, -height / 2.0f, thickness / 2.0f);
    glVertex3f(-width / 2.0f, -height / 2.0f, thickness / 2.0f);
    glVertex3f(-width / 2.0f, height / 2.0f, thickness / 2.0f);
    
    //back
    //glColor3f(0.0f, 1.0f, 0.0f);
    glNormal3f(0.0f, 0.0f, -1.0f);
    glVertex3f(width / 2.0f, height / 2.0f, -thickness / 2.0f);
    glVertex3f(width / 2.0f, -height / 2.0f, -thickness / 2.0f);
    glVertex3f(-width / 2.0f, -height / 2.0f, -thickness / 2.0f);
    glVertex3f(-width / 2.0f, height / 2.0f, -thickness / 2.0f);
    
    //right
    //glColor3f(0.0f, 0.0f, 1.0f);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(width / 2.0f, height / 2.0f, thickness / 2.0f);
    glVertex3f(width / 2.0f, height / 2.0f, -thickness / 2.0f);
    glVertex3f(width / 2.0f, -height / 2.0f, -thickness / 2.0f);
    glVertex3f(width / 2.0f, -height / 2.0f, thickness / 2.0f);
    
    //left
    //glColor3f(1.0f, 1.0f, 0.0f);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(-width / 2.0f, height / 2.0f, thickness / 2.0f);
    glVertex3f(-width / 2.0f, height / 2.0f, -thickness / 2.0f);
    glVertex3f(-width / 2.0f, -height / 2.0f, -thickness / 2.0f);
    glVertex3f(-width / 2.0f, -height / 2.0f, thickness / 2.0f);
    
    //top
    //glColor3f(0.0f, 1.0f, 1.0f);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(width / 2.0f, height / 2.0f, thickness / 2.0f);
    glVertex3f(width / 2.0f, height / 2.0f, -thickness / 2.0f);
    glVertex3f(-width / 2.0f, height / 2.0f, -thickness / 2.0f);
    glVertex3f(-width / 2.0f, height / 2.0f, thickness / 2.0f);
    
    //bot
    //glColor3f(1.0f, 0.0f, 1.0f);
    glNormal3f(0.0f, -1.0f, 0.0f);
    glVertex3f(width / 2.0f, -height / 2.0f, thickness / 2.0f);
    glVertex3f(width / 2.0f, -height / 2.0f, -thickness / 2.0f);
    glVertex3f(-width / 2.0f, -height / 2.0f, -thickness / 2.0f);
    glVertex3f(-width / 2.0f, -height / 2.0f, thickness / 2.0f);
    
    glEnd();
    glPopMatrix();
    
}

void drawChin(){
    glPushMatrix();
    glBegin(GL_QUADS);
    //front
    //glColor3f(1.0f, 0.0f, 0.0f);
    glNormal3f(0.0f, 0.0f, 1.0f);
    glVertex3f(1.0f, 1.0f, 1.0f);
    glVertex3f(0.5f, 0.0f, 1.0f);
    glVertex3f(-0.5f, 0.0f, 1.0f);
    glVertex3f(-1.0f, 1.0f, 1.0f);
    
    //back
    //glColor3f(0.0f, 1.0f, 0.0f);
    glNormal3f(0.0f, 0.0f, -1.0f);
    glVertex3f(1.0f, 1.0f, 0.5f);
    glVertex3f(0.5f, 0.0f, 0.5f);
    glVertex3f(-0.5f, 0.0f, 0.5f);
    glVertex3f(-1.0f, 1.0f, 0.5f);
    
    //right
    //glColor3f(0.0f, 0.0f, 1.0f);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(1.0f, 1.0f, 1.0f);
    glVertex3f(1.0f, 1.0f, 0.5f);
    glVertex3f(0.5f, 0.0f, 0.5f);
    glVertex3f(0.5f, 0.0f, 1.0f);
    
    //left
    //glColor3f(1.0f, 1.0f, 0.0f);
    glNormal3f(-1, 0, 0);
    glVertex3f(-1.0f, 1.0f, 1.0f);
    glVertex3f(-1.0f, 1.0f, 0.5f);
    glVertex3f(-0.5f, 0.0f, 0.5f);
    glVertex3f(-0.5f, 0.0f, 1.0f);
    
    //bot
    //glColor3f(1.0f, 0.0f, 1.0f);
    glNormal3f(0.0f, -1.0f, 0.0f);
    glVertex3f(0.5f, 0.0f, 1.0f);
    glVertex3f(0.5f, 0.0f, 0.5f);
    glVertex3f(-0.5f, 0.0f, 0.5f);
    glVertex3f(-0.5f, 0.0f, 1.0f);
    
    
    glEnd();
    glPopMatrix();
}

void update(int value) {      cameraAngle = 0;
    
    lightAngle += 1;
    if (lightAngle > 360){
        lightAngle -= 360;
    }
    
    
    glutPostRedisplay();
    glutTimerFunc(1, update, 0);
}

void moveCam() {
    x0 = R * sin(teta) * cos(beta);
    Y0 = R * sin(beta);
    z0 = R * cos(teta) * cos(beta);
    
    glutPostRedisplay();
}


/*  Mise en forme de la scËne pour l'affichage */
void reshape(int w,  // w: largeur fenÍtre
             int h)  // h: hauteur fenÍtre
{
    /* Viewport: cadrage. SpÈcifie la rÈgion (position et taille en px) que l'image observÈe de la scËne occupe
     ‡ l'Ècran => rÈduction et agrandissement de l'image possible*/
    glViewport(0, 0,(GLsizei) w, (GLsizei) h);
    
    /* SpÈcifie que la matrice de projection va Ítre modifiÈe  */
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();             // matrice courante: l'identitÈ
    //glOrtho(-2.0, 2.0, -2.0, 2.0, 1.5, 20.0);
    //glFrustum(-1.0, 1.0, -1.0, 1.0, 1.5, 20.0);
    
    /* Perspective avec point de fuite */
    gluPerspective(60.0,                       // angle d'ouverture vertical camÈra
                   (GLfloat) w / (GLfloat) h,  // ratio largeur-hauteur
                   1.0,                           // plan proche z=1
                   200.0);                     // plan ÈloignÈ z=200
    
    
}

/* Fonction de gestion du clavier */
void keyboard(unsigned char key,       // Touche qui a ÈtÈ pressÈe
              int x, int y) {    // CoordonnÈes courante de la souris
    
    switch (key){
            
        case 'p':   /* affichage du carrÈ plein*/
            glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
            glutPostRedisplay();
            break;
            
        case 'f':   /* affichage en mode fil de fer*/
            glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
            glutPostRedisplay();
            break;
            
        case 'd':
            teta += 0.1;
            if (teta > (2 * M_PI) ) {
                teta -= (2 * M_PI);
            }
            moveCam();
            break;
        
        case 'q':
            teta -= 0.1;
            if (teta < (-2 * M_PI) ) {
                teta += (2 * M_PI);
            }
            moveCam();
            break;
        
        case 'z':
            beta += 0.1;
            if (beta > (2 * M_PI) ) {
                beta -= (2 * M_PI);
            }
            moveCam();
            break;
            
        case 's':
            beta -= 0.1;
            if (beta < (-2 * M_PI) ) {
                beta += (2 * M_PI);
            }
            moveCam();
            break;
            
        case '+':
            R -= 1.0f;
            moveCam();
            break;
        
        case '-':
            R += 1.0f;
            moveCam();
            break;
        
        case 'l':
            glEnable(GL_LIGHTING);
            glEnable(GL_LIGHT0);
            glutPostRedisplay();
            break;
        
        case 'L':
            glDisable(GL_LIGHTING);
            glutPostRedisplay();
            break;
        
            //move bras
        case 'm':
            angle2 += 1.0f;
            if (angle2 > 150) {
                angle2 -= 150;
            }
            
            angle += 1.0f;
            if (angle > 150) {
                angle -= 150;
            }
            break;
            
            //reset bras
        case 'M':
            angle = 0.0f;
            angle2 = 0.0f;
            break;
            
            //move tête
        case 't':
            angleT += 1.0f;
            if (angleT > 360) {
                angleT -= 360;
            }
            break;
            
            //reset tête
        case 'T':
            angleT = 0.0f;
            break;
            
            //move jambes
        case 'j':
            angleJ += 1.0f;
            if (angleJ > 150) {
                angleJ -= 150;
                angleJ2 -= 45;
            }
            
            
            if (angleJ2 < 45) {
                angleJ2 += 1.0f;
            }
            break;
        
            //reset jambes
        case 'J':
            angleJ = 0.0f;
            angleJ2 = 0.0f;
            break;
            
        case 'b':
            break;
            
        case 'B':
            break;
            
        case 'x':/* Quitter le programme */
            exit(0);
            break;
    }
}


