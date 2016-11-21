//opengl cross platform includes
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>


#ifdef __APPLE__
#  include <OpenGL/gl.h>
#  include <OpenGL/glu.h>
#  include <GLUT/glut.h>
#else
#  include <GL/gl.h>
#  include <GL/glu.h>
#  include <GL/freeglut.h>
#endif

int main_id;
int subMenu_id;
int subMenu_id2;
int subMenu_id3;
int size;
void drawGrid10();
void turnRobot(int dir);
void moveRobot(int dir);
void drawTail();
int randomNum();
void drawHead();
void drawTail();
void refresh();
bool outBounds();
void resetRobot();
int tailX;
int tailY;
int headX;
int headY;
static int initialTailX;
static int initialTailY;
static int initialHeadX;
static int initialHeadY;
unsigned char option;
bool sideways=false;
bool upside=false;



int randomNum(){//random number function 
  int num=rand()%(size-2);
  num+=1;
  return num;
}


void menuProc(int value){
	if(value == 1)
		printf("Move was clicked\n");
	if(value == 2)
		printf("Turn was clicked\n");
}

void subMenuMove(int value){
	if(value == 1){
		printf("Moving Up\n");
		moveRobot(1);	
	}if(value == 2){
		printf("Moving Down\n");
		moveRobot(2);	
	}if(value == 3){
		printf("Moving Left\n");
		moveRobot(3);	
	}if(value == 4){
		printf("Moving Right\n");
		moveRobot(4);	
	}
	
}


//moves the robot up,down,left,right
void moveRobot(int dir){
	if (dir == 1 && headY+1!=size && tailY+1!=size){//up
		if(headY>tailY){
			headY+=1;tailY+=1;
			refresh();drawHead();drawTail();
		}else if(tailY>headY){
			headY+=1;tailY+=1;
			refresh();drawHead();drawTail();
		}
		else if(tailX>headX){
			headY+=1;tailY+=1;
			refresh();drawHead();drawTail();
		}else if(headX>tailX){
			headY+=1;tailY+=1;
			refresh();drawHead();drawTail();
		}
	}else if (dir == 2 && headY-1>=0 && tailY-1>=0){//down
		if(headY>tailY){
			headY-=1;tailY-=1;
			refresh();drawHead();drawTail();
		}
		else if(tailY>headY){
			headY-=1;tailY-=1;
			refresh();drawHead();drawTail();
		}
		else if(tailX>headX){
			headY-=1;tailY-=1;
			refresh();drawHead();drawTail();
		}else if(headX>tailX){
			headX-=1;tailX-=1;
			refresh();drawHead();drawTail();
		}
	}else if (dir == 3 && headX-1>=0 && tailX-1>=0){//left
		if(headY>tailY){
			headX-=1;tailX-=1;
			refresh();drawHead();drawTail();
		}
		else if(tailY>headY){
			headX-=1;tailX-=1;
			refresh();drawHead();drawTail();
		}
		else if(tailX>headX){
			headX-=1;tailX-=1;
			refresh();drawHead();drawTail();
		}else if(headX>tailX){
			headX-=1;tailX-=1;
			refresh();drawHead();drawTail();
		}
	}else if (dir == 4 && headX+1!=size && tailX+1!=size){//right
		if(headY>tailY){
			headX+=1;tailX+=1;
			refresh();drawHead();drawTail();
		}
		else if(tailY>headY){
			headX+=1;tailX+=1;
			refresh();drawHead();drawTail();
		}
		else if(tailX>headX){
			headX+=1;tailX+=1;
			refresh();drawHead();drawTail();
		}else if(headX>tailX){
			headX+=1;tailX+=1;
			refresh();drawHead();drawTail();
		}
		
	}

}
//refreshes the screen ans displays grid only
void refresh(){
		glClearColor(1,1,0,0);//clear board
		glClear(GL_COLOR_BUFFER_BIT);//clear board
		drawGrid10();//redraw grid
}

void subMenuTurn(int value){
	if(value == 1){
		printf("Turning Left\n");
		glClearColor(1,1,0,0);//clear board
		glClear(GL_COLOR_BUFFER_BIT);//clear board
		drawGrid10();//redraw grid
		//drawTail();
		turnRobot(1);
	}if(value == 2){
		printf("Turning Right\n");
		glClearColor(1,1,0,0);//clear board
		glClear(GL_COLOR_BUFFER_BIT);//clear board
		drawGrid10();//redraw grid
		//drawTail();
		turnRobot(2);
	}
}

//resets robot to the initial position
void resetRobot(){
	headX=initialHeadX;
	tailX=initialTailX;
	headY=initialHeadY;
	tailY=initialTailY;
	glClearColor(1,1,0,0);//clear board
	glClear(GL_COLOR_BUFFER_BIT);//clear board
	drawGrid10();
	drawTail();
	drawHead();

}

void subMenuOptions(int value){
	if(value == 1){//user reset robot
		resetRobot();
	}if(value == 2){//User selected quit 
		printf("%s", "Have a nice day! :D \n");
		exit(0);
	}

}
//draws the tail(green square) of the robot
void drawTail(){
	glPushMatrix();
	glBegin(GL_POINTS);
		glColor3f(0,1,0);
		for(double i=tailX;i<=tailX+1;i+=0.001){//paint square horizontal
			for(double j=tailY;j<=tailY+1;j+=0.001){//paint square vertical
				glVertex2f(i,j);
			}
		}
	glEnd();
	glPopMatrix();
}

//draws the head(red square) of the robot
void drawHead(){
	glPushMatrix();
	glBegin(GL_POINTS);
		glColor3f(1,0,0);
		for(double i=headX;i<=headX+1;i+=0.001){//paint square horizontal
			for(double j=headY;j<=headY+1;j+=0.001){//paint square vertical
				glVertex2f(i,j);
			}
		}
	glEnd();
	glPopMatrix();
}

//turns the robot left and right 
void turnRobot(int dir){
	if (dir==1){
		if(headY>tailY){
			headX-=1;headY-=1;
			drawHead();drawTail();
			sideways=true;
		}else if(tailX>headX){
			headX+=1;headY-=1;
			drawTail();drawHead();upside=true;sideways=false;
		}else if(tailY>headY){
			headX+=1;headY+=1;
			drawTail();drawHead();upside=false;sideways=true;
		}else if(headX>tailX){
			headX-=1;headY+=1;
			drawTail();drawHead();upside=false;sideways=true;
		}
	}if (dir==2){
		if(headY>tailY){
			headX+=1;headY-=1;
			drawHead();drawTail();
			sideways=true;
		}else if(headX>tailX){
			headX-=1;headY-=1;
			drawTail();drawHead();upside=true;sideways=false;
		}else if(tailY>headY){
			headX-=1;headY+=1;
			drawTail();drawHead();upside=false;sideways=true;
		}else if(tailX>headX){
			headX+=1;headY+=1;
			drawTail();drawHead();upside=false;sideways=true;
		}
	}
	glEnd();

}
//handles the drawing of the head and tail of the robot
void drawRobot(){
	glPushMatrix();
	drawTail();
	int toss = rand()%4;//randomizes placement of the head.Can be left,right,up,down
	if(toss==0){headY+=1;}//randomize
	else if(toss==1){headX+=1;}//randomize
	else if(toss==2){headY-=1;}//randomize
	else if(toss==3){headX-=1;}//randomize
	initialHeadX=headX;
	initialHeadY=headY;
	drawHead();
	glEnd();
	glPopMatrix();
}


//draws grid of any size, determined by user 
void drawGrid10(){
	glPointSize(1.0);
	glColor3f(0,0,1);
	glBegin(GL_POINTS);
		for(double i=0; i<size;i+=0.001){//draws lines horizontal
			for(double j=0;j<size;j+=1){//move the y-axis up after line drawn left to right
				glVertex2f(i,j);
			}
		}//horizontal lines end

		for(double j=0; j<size;j+=0.001){//draws lines vertical
			for(double i=0;i<size;i+=1){//x-axis across after line drawn top to bottom
				glVertex2f(i,j);
			}
		}//up and down lines end
		glEnd();
}

bool begin=false;
void display(void)
{
	if(begin==false){
		glClearColor(1,1,0,0);
		glClear(GL_COLOR_BUFFER_BIT);
		drawGrid10();//keeps rendering
		drawRobot();
		begin=true;
	}
}

/* main function - program entry point */
int main(int argc, char** argv)
{
	glutInit(&argc, argv);		//starts up GLUT
	printf("%s\n","Welcome! Click the screen to display the menu after the window opens.\n" );
	printf("Enter the grid size: ");
	scanf("%d",&size);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutInitWindowSize(700,700);
	glutInitWindowPosition(0,0);
	glutCreateWindow("Assignment#1-Robot");
	gluOrtho2D(0,size,0,size); //for 10*10 Grid 
	tailX=randomNum();
	srand (time(NULL));
	tailY=randomNum();
	initialTailX=tailX;
	initialTailY=tailY;
	headX=tailX;
	headY=tailY;
	glutDisplayFunc(display);
	glClearColor(1, 1, 1, 1);
	subMenu_id=glutCreateMenu(subMenuMove);
	glutAddMenuEntry("Up",1);
	glutAddMenuEntry("Down",2);
	glutAddMenuEntry("Left",3);
	glutAddMenuEntry("Right",4);
	subMenu_id2=glutCreateMenu(subMenuTurn);
	glutAddMenuEntry("Left",1);
	glutAddMenuEntry("Right",2);
	subMenu_id3=glutCreateMenu(subMenuOptions);
	glutAddMenuEntry("Reset Robot",1);
	glutAddMenuEntry("Quit",2);
	main_id = glutCreateMenu(menuProc);
	glutAddSubMenu("Move", subMenu_id);
	glutAddSubMenu("Turn", subMenu_id2);
	glutAddSubMenu("Options", subMenu_id3);
	glutAttachMenu(GLUT_LEFT_BUTTON);
	glutMainLoop();				//starts the event loop
	return(0);					
}