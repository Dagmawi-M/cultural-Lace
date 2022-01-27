#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <math.h>
#include <algorithm>


int radius= 100 , smallradius=20 ,stroke=115 , smallstroke= 22 , MinicircleRadius=3,Cx=267,Cy=270;
int p1x=185,p1y=350,p2x=267,p2y=350,p3x=350,p3y=350,p4x=350,p4y=270,p5x=350,p5y=190,p6x=267,p6y=190,p7x=185,p7y=190,p8x=185,p8y=270;

void init(void) {
    glClearColor(0.0,0.0,0.0,1);
    glMatrixMode(GL_PROJECTION);
    glMatrixMode(GL_MODELVIEW);
    gluOrtho2D(0.0,500.0,0.0,500.0);
}

void initRendering()
{
glEnable(GL_DEPTH_TEST);
}


void myLineEllipse(int x,int y,float StAngle,float EndAngle,int RX, int RY)
{
	double i;
	glBegin(GL_LINE_LOOP);
	//  glColor3f(0.35,0.35, 0.67);
	i=StAngle;
	while(i<=EndAngle)
	{
		glVertex2f(int((RX*cos(i)+x)+.5),int((RY*sin(i)+y)+.5));
		i=i+.001;
	}
		glEnd();
}

void myEllipse(int x,int y,float StAngle,float EndAngle,int RX, int RY)
{
	double i;
	glBegin(GL_POLYGON);
	//  glColor3f(0.35,0.35, 0.67);
	i=StAngle;
	while(i<=EndAngle)
	{
		glVertex2f(int((RX*cos(i)+x)+.5),int((RY*sin(i)+y)+.5));
		i=i+.001;
	}
		glEnd();
}


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


void DrawLine(int x, int y, int a, int b){
     glColor3f(0.8,0.8,0.8);
    glBegin(GL_LINES);
        glVertex2i(x,y);
        glVertex2i(a,b);
    glEnd();
    glFlush();
}

void DrawFold(int Ex, int Ey,int orientation){
     if (orientation=='H'){
        DrawLine(Cx,Cy,(Cx-((Cx-Ex)*2)),Cy);
        DrawLine(Cx,Cy+1,(Cx-((Cx-Ex)*2)),Cy);}
         else if (orientation=='V'){
         DrawLine(Cx,Cy,Cx,(Cy-((Cy-Ey)*2)));
         DrawLine(Cx+1,Cy,Cx,(Cy-((Cy-Ey)*2)));}
}


void EllipseLace(int y, int x, int Rx ,int Ry){


        glColor3f(1,1,1);
         myEllipse(y , x ,0, 180 , Rx,Ry );// Stroke

         glColor3f(0.35,0.35, 0.67);
         myEllipse(y , x ,0, 180 , Rx-10,Ry-10 ); // Ellipse


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

//CircleLace(radius, stroke, 185, 350 , 'L'); //LeftTopCircle + stroke + Pattern
//CircleLace(radius, stroke, 185, 190 , 'L'); //LeftBottomCircle + stroke + Pattern
//CircleLace(radius, stroke, 350, 350 , 'L'); //RightTopCircle + stroke + Pattern
//CircleLace(radius, stroke, 350, 190, 'L'); //RightBottomCircle + stroke + Pattern
//
//EllipseLace(185,270,90,40);//Left
//EllipseLace(350,270,90,40);//Right
//EllipseLace(267,350 ,40,90);//Top
//EllipseLace(267,190,40,90);//Bottom
//
//DrawFold(185,270,'H');//Folded illusion Line
//DrawFold(350,270,'H');
//DrawFold(267,350,'V');
//DrawFold(267,190,'V');
//
//CircleLace(smallradius, smallstroke, 185,350, 'S'); //(S)SmallRightBottomCircle + stroke
//CircleLace(smallradius, smallstroke, 185,190, 'S'); //(S)SmallRightBottomCircle + stroke
//CircleLace(smallradius, smallstroke, 350,350, 'S'); //(S)SmallRightBottomCircle + stroke
//CircleLace(smallradius, smallstroke, 350,190, 'S'); //(S)SmallRightBottomCircle + stroke
//
//
//CircleLace(MinicircleRadius, 0, 185,350, 'T'); //(T)TinyRightBottomCircle
//CircleLace(MinicircleRadius, 0, 185,190, 'T'); //(T)TinyRightBottomCircle
//CircleLace(MinicircleRadius, 0, 350,350, 'T'); //(T)TinyRightBottomCircle
//CircleLace(MinicircleRadius, 0, 350,190, 'T'); //(T)TinyRightBottomCircle
//
//
//CircleLace(smallradius, smallstroke, 267,270, 'S'); //Small Center Circle
//CircleLace(MinicircleRadius, 0, 267,270, 'T'); //(T)TinyRightBottomCircleforCenter
CircleLace(radius, stroke, p1x, p1y , 'L'); //LeftTopCircle + stroke + Pattern
CircleLace(radius, stroke, p7x, p7y , 'L'); //LeftBottomCircle + stroke + Pattern
CircleLace(radius, stroke, p3x, p3y , 'L'); //RightTopCircle + stroke + Pattern
CircleLace(radius, stroke, p5x, p5y, 'L'); //RightBottomCircle + stroke + Pattern

EllipseLace(p8x, p8y,90,40);//Left
EllipseLace(p4x, p4y,90,40);//Right
EllipseLace(p2x, p2y ,40,90);//Top
EllipseLace(p6x, p6y,40,90);//Bottom

DrawFold(p8x, p8y,'H');//Folded illusion Line
DrawFold(p4x, p4y,'H');
DrawFold(p2x, p2y ,'V');
DrawFold(p6x, p6y,'V');

CircleLace(smallradius, smallstroke, p1x, p1y, 'S'); //(S)SmallTopLeftCircle + stroke
CircleLace(smallradius, smallstroke, p7x, p7y, 'S'); //(S)SmallBottomLeftCircle + stroke
CircleLace(smallradius, smallstroke, p3x, p3y, 'S'); //(S)SmallTopRightCircle + stroke
CircleLace(smallradius, smallstroke, p5x, p5y, 'S'); //(S)SmallBottomRightCircle + stroke


CircleLace(MinicircleRadius, 0, p1x, p1y, 'T'); //(T)TinyRightBottomCircle
CircleLace(MinicircleRadius, 0, p7x, p7y, 'T'); //(T)TinyRightBottomCircle
CircleLace(MinicircleRadius, 0, p3x, p3y, 'T'); //(T)TinyRightBottomCircle
CircleLace(MinicircleRadius, 0, p5x, p5y, 'T'); //(T)TinyRightBottomCircle


CircleLace(smallradius, smallstroke, Cx,Cy, 'S'); //Small Center Circle
CircleLace(MinicircleRadius, 0, Cx,Cy, 'T'); //(T)TinyRightBottomCircleforCenter

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
