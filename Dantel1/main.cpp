#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <math.h>
#include <algorithm>


int radius= 100 , smallradius=20 ,stroke=115 , smallstroke= 22 , MinicircleRadius=3,Cx=267,Cy=270, EllipseRadiusLarge = 80 , EllipseRadiusSmall=30,EllipseRadiusLargeStroke = 90 , EllipseRadiusSmallStroke=40;
int p1x=185,p1y=350,p2x=267,p2y=350,p3x=350,p3y=350,p4x=350,p4y=270,p5x=350,p5y=190,p6x=267,p6y=190,p7x=185,p7y=190,p8x=185,p8y=270;
int pattern=radius/5;

void init(void) {
    glClearColor(0.0,0.0,0.0,1);
    glMatrixMode(GL_PROJECTION);
   // glMatrixMode(GL_MODELVIEW);
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


void EllipseLace(int y, int x, int Rx ,int Ry, char orientation){

if(orientation=='H'){
     glColor3f(1,1,1);
         myEllipse(y , x ,0, 180 , EllipseRadiusLargeStroke,EllipseRadiusSmallStroke );// Stroke
}
else if (orientation=='V')
{
      glColor3f(1,1,1);
         myEllipse(y , x ,0, 180 , EllipseRadiusSmallStroke, EllipseRadiusLargeStroke);// Stroke
}


         glColor3f(0.35,0.35, 0.67);
         myEllipse(y , x ,0, 180 , Rx,Ry); // Ellipse


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
            for(int i=pattern ; i<=pattern*4 ; i=i+pattern){ //Line circles to create the internal pattern
            LineCircle(i,x,y);}
                break;
        case 'T':
            glColor3f(0.35,0.35, 0.67); // violet-blue for Tiny Circles
            DrawCircle(radius,x,y);//Draw Tiny Circles
                break;
     }
}


void Andandiyosh(){


CircleLace(radius, stroke, p1x, p1y , 'L'); //LeftTopCircle + stroke + Pattern
CircleLace(radius, stroke, p7x, p7y , 'L'); //LeftBottomCircle + stroke + Pattern
CircleLace(radius, stroke, p3x, p3y , 'L'); //RightTopCircle + stroke + Pattern
CircleLace(radius, stroke, p5x, p5y, 'L'); //RightBottomCircle + stroke + Pattern


EllipseLace(p8x, p8y,EllipseRadiusLarge,EllipseRadiusSmall,'H');//Left
EllipseLace(p4x, p4y,EllipseRadiusLarge,EllipseRadiusSmall,'H');//Right
EllipseLace(p2x, p2y ,EllipseRadiusSmall,EllipseRadiusLarge,'V');//Top
EllipseLace(p6x, p6y,EllipseRadiusSmall,EllipseRadiusLarge,'V');//Bottom

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

void translate(float tx, float ty){
   glClear(GL_COLOR_BUFFER_BIT);
  p1x= p1x + tx;  p1y= p1y + ty;
  p2x= p2x + tx;  p2y= p2y + ty;
  p3x= p3x + tx;  p3y= p3y + ty;
  p4x= p4x + tx;  p4y= p4y + ty;
  p5x= p5x + tx;  p5y= p5y + ty;
  p6x= p6x + tx;  p6y= p6y + ty;
  p7x= p7x + tx;  p7y= p7y + ty;
  p8x= p8x + tx;  p8y= p8y + ty;
  Cx = Cx + tx ;  Cy=Cy+ty;
  Andandiyosh();
}



void Scale(float sx, float sy , float fixedx , float fixedy){
 glClear(GL_COLOR_BUFFER_BIT);

  radius= radius*sx;
  smallradius=smallradius*sx;
  stroke=stroke *sx;
  smallstroke= smallstroke*sx;
   MinicircleRadius=MinicircleRadius*sx;
pattern=radius/5;
EllipseRadiusLarge = EllipseRadiusLarge*sx;
 EllipseRadiusSmall=EllipseRadiusSmall*sx;
 EllipseRadiusLargeStroke = EllipseRadiusLargeStroke*sx;
  EllipseRadiusSmallStroke=EllipseRadiusSmallStroke*sx;

 p1x = (sx*p1x) + (sx * (-1 * fixedx) + fixedx);
 p1y = (sy*p1y) + (sy * (-1 * fixedy) + fixedy);

  p2x = (sx*p2x) + (sx * (-1 * fixedx) + fixedx);
 p2y = (sy*p2y) + (sy * (-1 * fixedy) + fixedy);

  p3x = (sx*p3x) + (sx * (-1 * fixedx) + fixedx);
 p3y = (sy*p3y) + (sy * (-1 * fixedy) + fixedy);

  p4x = (sx*p4x) + (sx * (-1 * fixedx) + fixedx);
 p4y = (sy*p4y) + (sy * (-1 * fixedy) + fixedy);

  p5x = (sx*p5x) + (sx * (-1 * fixedx) + fixedx);
 p5y = (sy*p5y) + (sy * (-1 * fixedy) + fixedy);

  p6x = (sx*p6x) + (sx * (-1 * fixedx) + fixedx);
 p6y = (sy*p6y) + (sy * (-1 * fixedy) + fixedy);

  p7x = (sx*p7x) + (sx * (-1 * fixedx) + fixedx);
 p7y = (sy*p7y) + (sy * (-1 * fixedy) + fixedy);

  p8x = (sx*p8x) + (sx * (-1 * fixedx) + fixedx);
 p8y = (sy*p8y) + (sy * (-1 * fixedy) + fixedy);

  Cx = (sx*Cx) + (sx * (-1 * fixedx) + fixedx);
 Cy = (sy*Cy) + (sy * (-1 * fixedy) + fixedy);
 Andandiyosh();
}


void Dantel(){

//Andandiyosh();

//for(int i=0;i<12;i+=i++){
//
////translate(i,i);
////Sleep(100);
////glFlush();
////}
//Sleep(1000);
//Scale(1.2,1.2,p7x,p7y);

//Sleep(1000);
//Scale(0.8,0.8,p7x,p7y);
//
//Sleep(1000);
//Scale(0.6,0.6,p7x,p7y);
//
Sleep(1000);
Scale(2,2,p7x,p7y);



//}
}



int main(int argc, char *argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(1000,1000);
    glutInitWindowPosition(0,0);

    glutCreateWindow("Dantel");

    init();
    glutDisplayFunc(Dantel);




    glutMainLoop();
}
