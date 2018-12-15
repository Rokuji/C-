#include <windows.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <direct.h>q

static int slices = 16;
static int stacks = 16;
static GLuint texid;

/* GLUT callback Handlers */

static void resize(int width, int height)
{
    const float ar = (float) width / (float) height;

    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-ar, ar, -1.0, 1.0, 2.0, 100.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity() ;
}

GLubyte* glmReadPPM(char* filename, int* width, int* height) {
  FILE* fp;
  int i, w, h, d;
  unsigned char* image;
  char head[70]; /* max line <= 70 in PPM (per spec). */

/*char *workingDir =_getcwd(NULL, 0);
std::cout << workingDir;*/
  fp = fopen(filename, "rb");
  if (!fp) {
    perror(filename);
    return NULL;
  }

  /* grab first two chars of the file and make sure that it has the
   correct magic cookie for a raw PPM file. */
  fgets(head, 70, fp);
  if (strncmp(head, "P6", 2)) {
    fprintf(stderr, "%s: Not a raw PPM file\n", filename);
    return NULL;
  }

  /* grab the three elements in the header (width, height, maxval). */
  i = 0;
  while (i < 3) {
    fgets(head, 70, fp);
    if (head[0] == '#') /* skip comments. */
      continue;
    if (i == 0)
      i += sscanf(head, "%d %d %d", &w, &h, &d);
    else if (i == 1)
      i += sscanf(head, "%d %d", &h, &d);
    else if (i == 2)
      i += sscanf(head, "%d", &d);
  }

  /* grab all the image data in one fell swoop. */
  image = (unsigned char*)malloc(sizeof(unsigned char)*w*h*3);
  fread(image, sizeof(unsigned char), w*h*3, fp);
  fclose(fp);

  *width = w;
  *height = h;
  return image;
}

void initialize_textures( void )
{
    int w, h;
    GLubyte *data = 0;
    data = glmReadPPM( "lb.ppm", &w, &h );
    std::cout << "Read lb.ppm, width = " << w << ", height = " << h << std::endl;
    glGenTextures(1, &texid);

glBindTexture(GL_TEXTURE_2D, texid);
glTexEnvi(GL_TEXTURE_2D, GL_TEXTURE_ENV_MODE, GL_MODULATE);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

glEnable(GL_TEXTURE_2D);
}

static void display(void)
{
        const double t = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
    const double a = t*90.0;
       glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3d(1,0,0);

/*glPushMatrix();
        glTranslated(-2.4,1.2,-6);
        glRotated(60,1,0,0);
        glRotated(a,0,0,1);
        glutSolidSphere(1,slices,stacks);
    glPopMatrix();*/

/*glBegin(GL_QUADS);
glVertex3f(-20.0, 20.0, -50.0);
glVertex3f(20.0, 20.0, -50.0);
glVertex3f(20.0, -20.0, -50.0);
glVertex3f(-20.0, -20.0, -50.0);
glEnd();*/



        glutSwapBuffers();
}


static void key(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 27 :
        case 'q':
            exit(0);
            break;
    }

    glutPostRedisplay();
}

static void idle(void)
{
    glutPostRedisplay();
}

const GLfloat light_ambient[]  = { 0.0f, 0.0f, 0.0f, 1.0f };
const GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_position[] = { 2.0f, 5.0f, 5.0f, 0.0f };

const GLfloat mat_ambient[]    = { 0.7f, 0.7f, 0.7f, 1.0f };
const GLfloat mat_diffuse[]    = { 0.8f, 0.8f, 0.8f, 1.0f };
const GLfloat mat_specular[]   = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat high_shininess[] = { 100.0f };

/* Program entry point */

int test3(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(800,600);
    glutInitWindowPosition(100,100);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    glutCreateWindow("Little Bighorn");

    initialize_textures();

    glutReshapeFunc(resize);
    glutDisplayFunc(display);
    glutKeyboardFunc(key);
    glutIdleFunc(idle);

    glClearColor(1,1,1,1);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

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
