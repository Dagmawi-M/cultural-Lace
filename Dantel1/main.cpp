#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <math.h>
#include <algorithm>


int radius= 100 , smallradius=20 ,stroke=115 , smallstroke= 22 , MinicircleRadius=3;

void init(void) {
    glClearColor(0.0,0.0,0.0,1);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0,500.0,0.0,500.0);
}

//void myEllipse(int x,int y,float StAngle,float EndAngle,int RX, int RY)
//{
//	double i;
//	glBegin(GL_LINE_STRIP);
//	glColor3f(0,1,0);
//	i=StAngle;
//	while(i<=EndAngle)
//	{
//		glVertex2f(int((RX*cos(i)+y)+.5),int((RY*sin(i)+x)+.5));
//		i=i+.001;
//	}
//		glEnd();
//}

void DrawCircle(int radius , int x, int y) {
    float theta;

    glBegin(GL_POLYGON);
        for(int i=0;i<360;i++){
            theta= i*3.142/180;
            glVertex2f(x+radius*cos(theta),y+radius*sin(theta));
        }
    glEnd();
    glFlush();
}

void LineCircle(int radius , int x, int y) {
    float theta;
glColor3f(1,1,1);
    glBegin(GL_LINE_LOOP);
        for(int i=0;i<360;i++){
            theta= i*3.142/180;
            glVertex2f(x+radius*cos(theta),y+radius*sin(theta));
        }
    glEnd();
    glFlush();
}


void CircleLace(int radius,int stroke, int x , int y , char type){

    glColor3f(1,1,1); //white stroke For large and small circles
    DrawCircle(stroke,x,y);

     switch(type){

         case 'S' :
            glColor3f(0.8,0.8,0.8); //Grey For Emboss look
            DrawCircle(radius,x,y); // Draws small circle
                break;
        case 'L':
            glColor3f(0.35,0.35, 0.67); // violet-blue for Large Circles
            DrawCircle(radius,x,y);//Draw large
            for(int i=40 ; i<=85 ; i=i+15){ //Line circles to create the internal pattern
            LineCircle(i,x,y);}
                break;
        case 'T':
            glColor3f(0.35,0.35, 0.67); // violet-blue for Tiny Circles
            DrawCircle(radius,x,y);//Draw Tiny Circles
                break;
     }
}


void Dantel(){

CircleLace(radius, stroke, 185, 350 , 'L'); //LeftTopCircle + stroke + Pattern
CircleLace(radius, stroke, 185, 190 , 'L'); //LeftBottomCircle + stroke + Pattern
CircleLace(radius, stroke, 350, 350 , 'L'); //RightTopCircle + stroke + Pattern
CircleLace(radius, stroke, 350, 190, 'L'); //RightBottomCircle + stroke + Pattern


CircleLace(smallradius, smallstroke, 185,350, 'S'); //(S)SmallRightBottomCircle + stroke
CircleLace(smallradius, smallstroke, 185,190, 'S'); //(S)SmallRightBottomCircle + stroke
CircleLace(smallradius, smallstroke, 350,350, 'S'); //(S)SmallRightBottomCircle + stroke
CircleLace(smallradius, smallstroke, 350,190, 'S'); //(S)SmallRightBottomCircle + stroke
CircleLace(smallradius, smallstroke, 267,270, 'S'); //(S)SmallRightBottomCircleforcenter + stroke


CircleLace(MinicircleRadius, 0, 185,350, 'T'); //(T)TinyRightBottomCircle
CircleLace(MinicircleRadius, 0, 185,190, 'T'); //(T)TinyRightBottomCircle
CircleLace(MinicircleRadius, 0, 350,350, 'T'); //(T)TinyRightBottomCircle
CircleLace(MinicircleRadius, 0, 350,190, 'T'); //(T)TinyRightBottomCircle
CircleLace(MinicircleRadius, 0, 267,270, 'T'); //(T)TinyRightBottomCircleforCenter
//glColor3f(0,1,0);
//DrawEllipse(100,270,50,60,10);
}

int main(int argc, char *argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500,500);
    glutInitWindowPosition(0,0);
    glutCreateWindow("Dantel");
    init();
    glutDisplayFunc(Dantel);
    glutMainLoop();
}
