#include <GL/glut.h>
#include <stdio.h>

float anglez = 0;
int animateMode = 0;
int spinz = 1;

void setupView()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-5, 5, -5, 5, -10, 10);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(2, 2, 3, 0, 0, 0, 0, 1, 0);

}

void setupSideView()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-5, 5, -5, 5, -10, 10);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0, 0, 4, 0, 0, 0, 0, 1, 0);

}

void setupFrontView()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-5, 5, -8, 5, -10, 10);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(4, 0, 0, 0, 2, 0, 0, 1, 0);

}

void setupTopView()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-5, 5, -5, 5, -10, 10);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0, 4, 0, 0, 0, 0, 0, 0, -1);

}

void setupWindowView()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-5, 5, -5, 5);
}

void drawLines()
{
	glBegin(GL_LINES);
	glVertex2f(-5, 0);
	glVertex2f(5, 0);
	glEnd();

	glBegin(GL_LINES);
	glVertex2f(0, 5);
	glVertex2f(0, -5);
	glEnd();
}

void teapot()
{
	//glutWireTeapot(1.0);
	//glutWireCone(5.0,5.0,20,10);
	//glutWireSphere(1.0,20,30);
	glutWireCube(1.0);
	//glutWireTorus(0.5,1.0,20,40);

}


void weel()
{
	//glClear(GL_COLOR_BUFFER_BIT);
	glColor3ub(255, 0,0);

	glVertex3f(0.0, 0.0, -1.5);
	//glutWireCube(4.0);
}

void skyLift()
{
	glRotatef(-anglez, 0, 0, 1);
	glColor3ub(255, 255, 255);
	glutWireCube(2.0);
}

void stand()
{
	glPointSize(10);

	glBegin(GL_LINE_LOOP);
	glColor3ub(255, 255, 0);
	glVertex3f(0.0, 0.0,-1.5);
	glVertex3f(1.0,-4.0, -1.5);
	glVertex3f(-1.0, -4.0, -1.5);
	glVertex3f(0.0, 0.0, -1.5);
	
	glVertex3f(0.0, 0.0, 1.5);

	glVertex3f(1.0, -4.0, 1.5);
	glVertex3f(-1.0, -4.0, 1.5);
	glVertex3f(0.0, 0.0, 1.5);
	
	
	glEnd();
}

void all()
{	
	glPushMatrix();
		glRotatef(anglez, 0, 0, 1);

		glPushMatrix();
		glScalef(1, 1, 0.2);
		weel();
		glPopMatrix();

		glPushMatrix();
		glTranslatef(2, 2, 0);
		skyLift();
		glPopMatrix();

		glPushMatrix();
		glTranslatef(2, -2, 0);
		skyLift();
		glPopMatrix();

		glPushMatrix();
		glTranslatef(-2, -2, 0);
		skyLift();
		glPopMatrix();

		glPushMatrix();
		glTranslatef(-2, 2, 0);
		skyLift();
		glPopMatrix();
	glPopMatrix();

	glPushMatrix();
	stand();
	glPopMatrix();

	glFlush();
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);

	setupWindowView();
	drawLines();

	glViewport(0, 0, 150, 150);
	setupSideView();				//down Left
	all();

	glViewport(150, 0, 150, 150);
	setupView();
	all();						//down Right

	glViewport(150, 150, 150, 150);
	setupFrontView();
	all();						//up right

	glViewport(0, 150, 150, 150);
	setupTopView();
	all();						//up Left

	glFlush();
}

void animate1() {
	printf("Animate");

	anglez = anglez + 0.05;

	glutPostRedisplay();

}

void keyboard(unsigned char key, int x, int y)
{
	//printf("%c,%d \n", key, key);
	printf("\n");


	switch (key) {
	case 'r':
	case 'R':
		glutIdleFunc(animate1);			//On
		animateMode = 1;
		break;

	case 's':
	case 'S':
		animateMode = 0;
		glutIdleFunc(NULL);				//Off
		break;

		glClear(GL_COLOR_BUFFER_BIT);
		glutPostRedisplay();

	}
}

int main(int argc, char** argv)
{
	glutCreateWindow("Final");
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	drawLines();

	glutMainLoop();
}