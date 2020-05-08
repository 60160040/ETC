#include <GL/glut.h>
#include <stdio.h>

float anglez = 0;					//degree
int animateMode = 0;				//'0' is stop, '1' is animate


void setupWindowView()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-5, 5, -5, 5);
}

void drawLines()					//crate bord
{
	glBegin(GL_LINES);				//horizontal line
	glVertex2f(-5, 0);
	glVertex2f(5, 0);
	glEnd();

	glBegin(GL_LINES);				//Vertical line
	glVertex2f(0, 5);
	glVertex2f(0, -5);
	glEnd();
}

void teapot()							//Just test
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
	glColor3ub(255, 0, 0);				//Red color

	glBegin(GL_LINE_LOOP);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(2.0, 2.0, 0.0);

	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(2.0, -2.0, 0.0);


	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(-2.0, -2.0, 0.0);

	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(-2.0, 2.0, 0.0);
	//glutWireCube(4.0);
	glEnd();
}

void skyLift()
{
	glRotatef(-anglez, 0, 0, 1);		//try comment this
	glColor3ub(255, 255, 255);
	glutWireCube(2.0);
}

void stand()
{
	glPointSize(1);

	glBegin(GL_LINE_LOOP);
	glColor3ub(255, 255, 0);
	glVertex3f(0.0, 0.0, -1.5);
	glVertex3f(1.0, -4.0, -1.5);
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
	glRotatef(anglez, 0, 0, 1);		//For rotate Ferris wheel

	glPushMatrix();
	//glScalef(1, 1, 0.2);
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
	stand();						//crate stand
	glPopMatrix();

	glFlush();
}

void setupTopView()								//Top left
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-5, 5, -5, 5, -10, 10);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0, 4, 0, 0, 0, 0, 0, 0, -1);

}

void setupFrontView()							//Top right
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-5, 5, -8, 5, -10, 10);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(4, 0, 0, 0, 2, 0, 0, 1, 0);
}

void setupSideView()							//Bottom left
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-5, 5, -5, 5, -10, 10);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0, 0, 4, 0, 0, 0, 0, 1, 0);

}

void setupView()								//Bottom right
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-5, 5, -5, 5, -10, 10);				//field of show of the object
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(2, 2, 3, 0, 0, 0, 0, 1, 0);		//(Ax,Ay,Az,Bx,By,Bz,Cx,Cy,Cz)  A is Camera, B is Aim

}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);

	setupWindowView();
	drawLines();					//crate bord

	glViewport(0, 0, 150, 150);
	setupSideView();				//Set Bottom Left
	all();

	glViewport(150, 0, 150, 150);
	setupView();
	all();							//Set Bottom Right

	glViewport(150, 150, 150, 150);
	setupFrontView();
	all();							//Set Top right

	glViewport(0, 150, 150, 150);
	setupTopView();
	all();							//Set Top Left

	glFlush();
}

void animate1() {
	printf("Animate");

	anglez = anglez + 0.05;				//increass degrees

	glutPostRedisplay();				// Re-display

}

void keyboard(unsigned char key, int x, int y)
{
	//printf("%c,%d \n", key, key);
	printf("\n");


	switch (key) {
	case 'r':
	case 'R':							//Star animate
		glutIdleFunc(animate1);
		animateMode = 1;
		break;

	case 's':
	case 'S':							//Stop animate
		animateMode = 0;
		glutIdleFunc(NULL);
		break;

		//glClear(GL_COLOR_BUFFER_BIT);
		//glutPostRedisplay();

	}
}

int main(int argc, char** argv)
{
	glutCreateWindow("Final");			//name window
	printf("'R' to animate/n");
	printf("'S' to stop/n");

	glutDisplayFunc(display);
	drawLines();					//create bord
	glutKeyboardFunc(keyboard);			//use keybord
	glutMainLoop();
}