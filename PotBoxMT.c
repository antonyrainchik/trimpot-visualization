#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#ifdef __APPLE_CC__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <stdbool.h>

static const int FPS = 60;

int old_i = 0;

int D=0;

static FILE *fp;

void reshape(GLint w, GLint h){
	glViewport(0,0,w,h);
	GLfloat aspect = (GLfloat)w / (GLfloat)h;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if(w<=h){
		glOrtho(-50.0,50.0,-50.0/aspect, 50.0/aspect, -1.0, 1.0);
	}
	else{
		glOrtho(-50.0*aspect, 50.0*aspect, -50.0, 50.0,-1.0,1.0);
	}
}

void display(){
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glRotatef(((GLfloat)D*(270.0/906.0)), 0.0, 0.0, 1.0);
	glRectf(-25.0,-25.0,25.0,25.0);
	glFlush();
	glutSwapBuffers();
}

void timer(int v){
	glutPostRedisplay();
	glutTimerFunc(1000/FPS,timer,v);
}

void *threadRunner()
{
  char buf[20];
  char *r;
  int temp_d;

   while(1){
      r = fgets(buf, sizeof(buf), fp);
      if (!r) {
        puts("gets returned an error");
        D = -1;
        return NULL;
      }

      if (sscanf(r, "%d", &temp_d) > 0 && sscanf(r, "%d", &temp_d) <= 910) {
        printf("scanned %d\n", temp_d);
        D = temp_d;
        old_i = D;
      }

   }

}


int main(int argc, char** argv){
  fp = fopen("/dev/cu.usbmodem1101","r");
  if (!fp) {
      puts("Error opening /dev/cu.usbmodem1101");
      return -1;
  }
  pthread_t thread_id;
  int old_D = -1;

  puts("Starting...");
  pthread_create(&thread_id, NULL, threadRunner, NULL);


  glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowPosition(80,80);
	glutInitWindowSize(800,500);
	glutCreateWindow("Spinning Square");
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutTimerFunc(100,timer,0);
	//glutMouseFunc(mouse);
  puts("Marker");
	glutMainLoop();

  fclose(fp);
    

  return 0;
}