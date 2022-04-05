#include <stdio.h>
#include <math.h>
#include <GL\glut.h>


//以点为模型的类Dot
class Dot {
public :
	GLfloat x, y;

	void init(GLfloat x1, GLfloat y1) {
		x = x1;
		y = y1;
	}
};

//以三角形为模型的类Triangle
class Triangle {
public:
	//dot1为三角形最上方的顶点，dot2为左边的顶点，dot3为右边的顶点
	Dot dot1, dot2, dot3;

	void init(Dot d1,Dot d2,Dot d3) {
		dot1 = d1;
		dot2 = d2;
		dot3 = d3;
	}
};


//总共生成243个小三角形
Triangle Tr[243];


//三个顶点连线成三角形
void drawTriangle(Triangle T) {
	glBegin(GL_LINE_LOOP);
	glVertex2f(T.dot1.x,T.dot1.y);
	glVertex2f(T.dot2.x, T.dot2.y);
	glVertex2f(T.dot3.x, T.dot3.y);
	glEnd();
	glFlush();
}

//将三角形对象T切分为3个小三角形并存储进Triangle对象组
void part(Triangle T,GLint temp, GLint i, GLint j) {

	/*
	找三角形三条线的中点，由此组建三个新的三角形
	left为左边中点，right为右边中点，bottom为底部中点
	*/
	Dot left{}, right{}, bottom{};

	//index为新生成的三角形在对象组中的间隔
	GLint index = 243 / pow(3, i + 1);

	left.x = (T.dot1.x + T.dot2.x) / 2;
	left.y = (T.dot1.y + T.dot2.y) / 2;
	right.x = (T.dot1.x + T.dot3.x) / 2;
	right.y = (T.dot1.y + T.dot3.y) / 2;
	bottom.x = (T.dot3.x + T.dot2.x) / 2;
	bottom.y = (T.dot3.y + T.dot2.y) / 2;

	Tr[j * temp].init(left, right, T.dot1);
	Tr[j * temp +index].init(left, bottom, T.dot2);
	Tr[j * temp + index * 2].init(right, bottom, T.dot3);
}

//屏幕渲染函数
void renderScene() {
	glClear(GL_COLOR_BUFFER_BIT);

	Dot D1{}, D2{}, D3{};
	GLint i = 0, j = 0;

	//初始化最大三角形的三个顶点对象
	D1.init(0.0, 0.6);
	D2.init(-0.6, -0.6);
	D3.init(0.6, -0.6);

	//初始化最大的三角形这个对象
	Tr[i].init(D1, D2, D3);


	//通过循环实现谢尔宾斯基垫圈，总共进行4次嵌套分割
	for (i = 0; i < 4; i++) {

		//每次循环更新temp的值，temp为当前Triangle对象组中每个三角形之间的间隔
		GLint temp = 243 / pow(3, i);

		//通过pow(3,i)确认现在Triangle对象组中已填充的三角形个数，也即这个循环要分割的三角形个数
		for (j = 0; j<pow(3,i); j++) {
			part(Tr[temp*j],temp,i,j);
		}
	}
	

	//在屏幕上描绘所有三角形
	for (i = 0; i <= 242; i++) {
		drawTriangle(Tr[i]);
	}
	
}

void main(int argc,char* argv[]) {
	//初始化glut
	glutInit(&argc, argv);
	//创建窗口，颜色选定RGB模式，单缓冲区
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	//选择窗口在屏幕中的位置
	glutInitWindowPosition(100, 150);
	//设置窗口大小
	glutInitWindowSize(640, 480);
	//创建窗口
	glutCreateWindow("sierpinski gasket");
	//实现屏幕图像渲染函数renderScene
	glutDisplayFunc(renderScene);

	glutMainLoop();
}