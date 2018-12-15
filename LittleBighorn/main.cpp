#include <iomanip>
#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <windows.h>
#include <fstream>
#include "glm.h"
#include "letters.h"

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#ifdef WIN32
#include <GL/glut.h>
#else
#include <GL/glut.h>
#endif
#endif

using namespace std;

struct xy{
    int x, y;
};

xy movement[50][32];

void read();
void write();
void status();
void unitcolor(int);

void display(void);
static void idle(void);
void resizeWindow(int, int);
void keyboard(unsigned char key,int x,int y);

void orthogonalStart();
void orthogonalEnd();
void background(GLuint, int, int);
GLuint LoadTexture(char*, int, int);

int window_id;
int win_width = 952, win_height = 700;
int back_width = 1152, back_height = 900;
float leg_width = 1633 , leg_height = 955;
int frame = 0, framerate = 250, frame_mul = 1;
int maxframe = 31 * frame_mul;

bool leg = false;
bool pause = false;

double start;
GLuint texture = 0;
GLuint legend = 0;

int main( int argc, char *argv[] )
{
  //
  // arguments to main are width and height of window if on console
  //
  if (argc == 3)
    {
      win_width = atoi( argv[1] );
      win_height = atoi( argv[2] );
    }

    read();
    //write();

  glutInitDisplayMode( GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE );

  glutInit(&argc, argv);
  glutInitWindowPosition(0, 0);
  glutInitWindowSize(win_width, win_height);

  window_id = glutCreateWindow(argv[0]);
  start = glutGet(GLUT_ELAPSED_TIME);
  texture = LoadTexture("lb.ppm",back_width,back_height);
  legend = LoadTexture("legend.ppm",leg_width,leg_height);

  glutReshapeFunc(resizeWindow);
  glutKeyboardFunc(keyboard);
  glutDisplayFunc(display);
  glutIdleFunc(idle);

  glutMainLoop();
  return 0;
}

void read() {
    ifstream input;
    input.open("input.txt");
    if (!input) {
        cout << "Cannot open file.";
    }

    //initialize
    for (int i = 0; i<=49; i++) {
        for (int j = 0; j<=31; j++) {
            movement[i][j].x = -3;
            movement[i][j].y = -3;
        }
    }

    char c;
    int i = 0, j = 0, number = 0;
    bool isY = false;
    while (input >> c) {

        if ((c >= '0') and (c <= '9')) {
            number = number * 10 + ((int) c - 48);
        }
        else
        switch (c) {
            case ';':
                if (isY) {
                    movement[i][j].y = back_height - number;
                    number = 0;
                    isY = false;
                }
                else {
                    movement[i][j].x = movement[i][j-1].x;
                    movement[i][j].y = movement[i][j-1].y;
                }
                j++;
                break;
            case '#':
                movement[i][j].x = -1;
                movement[i][j].y = -1;
                break;
            case '$':
                movement[i][j].x = -2;
                movement[i][j].y = -2;
                break;
            case ',':
                movement[i][j].x = number;
                number = 0;
                isY = true;
                break;
        }
        if (input.peek() == '\n') {
            i++;
            j = 0;
        }
    }

    input.close();
}

void write() {
    for (int i = 18; i<=18; i++) {
        for (int j = 0; j<=31; j++) {
            cout << "a[" << i << "]" << "[" << j << "] = " << movement[i][j].x << "," << movement[i][j].y << ";" << endl;
        }
        cout << endl;
    }
}

void status() {
    system("CLS");
    cout << "Esc: Quit" << endl
         << "P: pause/resume" << endl
         << "Spacebar: toggle legend On/Off" << endl
         << "+/-: increase/decrease speed" << endl
         << "A/D: previous/next frame" << endl
         << "W/S: increase/decrease smooth rate" << endl
         << setprecision(2) << "Speed: " << (float)1000/framerate << " frame per second" << endl
         << "Smooth rate: " << frame_mul << endl
         << "Frame #" << frame << endl;
}

static void idle(void)
{
    glutPostRedisplay();
}

void unitcolor(int number) {
    switch (number) {
        case 1: glColor3f(0.0, 0.5, 0.0);
                break;
        case 2: glColor3f(0.0, 0.0, 1.0);
                break;
        case 3: glColor3f(0.0, 1.0, 1.0);
                break;
        case 4: glColor3f(1.0, 0.4, 0.4);
                break;
        default: glColor3f(1.0, 0.0, 0.0);
                 break;
    }
}

void display(void)
{
    //glClearColor(0.2, 0.2, 0.5, 0.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  int width = glutGet(GLUT_WINDOW_WIDTH);
  int height = glutGet(GLUT_WINDOW_HEIGHT);
  float rw = back_width / (float)width;
  float rh = back_height / (float)height;

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0, width, 0, height, -1, 1);

  glEnable(GL_DEPTH_TEST);
  glDisable(GL_LIGHTING);

  //
  // Draw Code can go here
  //
    //asterisk(500 / rw, 500 / rh);

    status();

    if (!pause) {
    const double current = glutGet(GLUT_ELAPSED_TIME);
    if (current - start >= framerate) {
        start = current;
        frame++;
        if (frame > maxframe) {
            frame = 0;
        }
    }
    }

    float x_coor, y_coor;
    int real_frame;

    for (int i = 0; i <= 49; i++) {
        real_frame = (int)frame/frame_mul;
        if (movement[i][real_frame].x >0) {

        x_coor = movement[i][real_frame].x / rw;
        y_coor = movement[i][real_frame].y / rh;

        if (movement[i][real_frame+1].x >0) {
            x_coor += (((movement[i][real_frame+1].x / rw) - (movement[i][real_frame].x / rw)) / frame_mul) * (frame % frame_mul);
            y_coor += (((movement[i][real_frame+1].y / rh) - (movement[i][real_frame].y / rh)) / frame_mul) * (frame % frame_mul);
            /*cout << frame % frame_mul << endl;
            cout << setprecision(2) << x_coor << " " << y_coor << " " << movement[i][real_frame].x << " " << movement[i][real_frame].y << " " << movement[i][real_frame+1].x << " " << movement[i][real_frame+1].x << endl;*/
        }

        switch (i) {
            //first unit
            case 0: unitcolor(1);
                    asterisk(x_coor, y_coor);
                    break;
            case 1: unitcolor(1);
                    letterF(x_coor, y_coor);
                    break;
            case 2: unitcolor(1);
                    letterC(x_coor, y_coor);
                    break;
            case 3: unitcolor(1);
                    letterE(x_coor, y_coor);
                    break;
            case 4: unitcolor(1);
                    letterI(x_coor, y_coor);
                    break;
            case 5: unitcolor(1);
                    letterL(x_coor, y_coor);
                    break;
            //second unit
            case 6: unitcolor(2);
                    letterA(x_coor, y_coor);
                    break;
            case 7: unitcolor(2);
                    letterM(x_coor, y_coor);
                    break;
            case 8: unitcolor(2);
                    letterG(x_coor, y_coor);
                    break;
            //third unit
            case 9: unitcolor(3);
                    letterH(x_coor, y_coor);
                    break;
            case 10: unitcolor(3);
                     letterD(x_coor, y_coor);
                     break;
            case 11: unitcolor(3);
                     letterK(x_coor, y_coor);
                     break;
            //pack-train
            case 12: unitcolor(4);
                     letterB(x_coor, y_coor);
                     break;
            case 13: unitcolor(4);
                     pluss(x_coor, y_coor);
                     break;
            //Indian units
            case 14: unitcolor(99);
                     letterC(x_coor, y_coor);
                     break;
            case 15: unitcolor(99);
                     letterG(x_coor, y_coor);
                     break;
            default: unitcolor(99);
                     glPointSize(4.0);
                     glBegin(GL_POINTS);
                     glVertex2f(x_coor, y_coor);
                     glEnd();
                     break;
        }
        //cout << frame << endl;
        }
    }

    if (leg) {
    glEnable( GL_TEXTURE_2D );
        glColor3f(1.0, 1.0, 1.0);
        glPushMatrix();
        background(legend, width/3.5, height/4);
        glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    }

    glEnable( GL_TEXTURE_2D );
        glColor3f(1.0, 1.0, 1.0);
        glPushMatrix();
        background(texture, width, height);
        glPopMatrix();
    glDisable(GL_TEXTURE_2D);

  //
  // Draw code should be completed by this point
  //

  glutSwapBuffers();
}

void resizeWindow(int width, int height)
{
    glViewport(0,0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //gluPerspective( 45.0, ratio, 1, 500 );
    glOrtho(0, width, 0, height, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void keyboard(unsigned char key,int x,int y)
{
    switch (key) {
        case 27: glutDestroyWindow(window_id);
                 exit(0);
                 break;
        case 'p': case 'P': pause = not pause;
                            break;
        case '+': if (framerate >50) {framerate += -50;}
                  break;
        case '-': if (framerate <10000) {framerate += +50;}
                  break;
        case 32: leg = not leg;
                 break;
        case 'a': case 'A': if (frame >0) {
                                frame--;
                            }
                            else {frame = maxframe;}
                            break;
        case 'd': case 'D': if (frame <maxframe) {
                                frame++;
                            }
                            else {frame = 0;}
                            break;
        case 'w': case 'W': if (frame_mul <20) {
                                frame_mul++;
                                maxframe = 31 * frame_mul;
                            }
                            break;
        case 's': case 'S': if (frame_mul >1) {
                                frame_mul--;
                                maxframe = 31 * frame_mul;
                            }
                            break;
    }
  /*if (key==27)  // the escape key
    {
      glutDestroyWindow(window_id);
      exit(0);
    }*/
}

void background(GLuint texture, int iw, int ih)
{
    glBindTexture( GL_TEXTURE_2D, texture );

    /*int iw = glutGet(GLUT_WINDOW_WIDTH);
    int ih = glutGet(GLUT_WINDOW_HEIGHT);*/

    glBegin(GL_QUADS);
        glTexCoord2i(0,1); glVertex2i(0, 0);
        glTexCoord2i(1,1); glVertex2i(iw, 0);
        glTexCoord2i(1,0); glVertex2i(iw, ih);
        glTexCoord2i(0,0); glVertex2i(0, ih);
    glEnd();
}

GLuint LoadTexture(char * filename, int width, int height)
{
    GLubyte *data = 0;
    GLuint texture = 0;

    //The following code will read in our RAW file
    data = glmReadPPM( filename, &width, &height );

    glGenTextures( 1, &texture );
    glBindTexture( GL_TEXTURE_2D, texture );
    glTexEnvi(GL_TEXTURE_2D, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

    glEnable(GL_TEXTURE_2D);
    return texture; //return whether it was successful
}
