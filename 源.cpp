#include <Windows.h>
#include <GL/glut.h>

void display() {
	glClearColor(1, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT);

	//矩阵调用，通过push()和pop()进行刷新矩阵
	glLoadIdentity();
	glPushMatrix();

	//第一个茶壶
	//向左移动0.5个单位，并沿y轴旋转180度
	glTranslatef(-0.5, 0, 0);
	glRotatef(180, 0, 1, 0);
	glColor3f(0, 1, 0);
	glutWireTeapot(0.3);

	glPopMatrix();
	glPushMatrix();

	//第二个茶壶
	//向上移动0.5个单位
	glTranslatef(0, 0.5, 0);
	//缩小为原来的一半
	glScalef(0.5, 0.5, 0.5);
	glColor3f(0, 0, 1);
	glutSolidTeapot(0.3);

	glPopMatrix();

	//第三个茶壶
	//向右移动0.5个单位
	glTranslatef(0.5, 0, 0);
	glColor3f(1, 0, 0);
	glutWireTeapot(0.3);

	glutSwapBuffers();
}

void main(int argc, char* argv[]) {
	//初始化glut
	glutInit(&argc, argv);
	//创建窗口，颜色选定RGB模式，双缓冲区
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	//选择窗口在屏幕中的位置
	glutInitWindowPosition(100, 150);
	//设置窗口大小
	glutInitWindowSize(640, 480);
	//创建窗口
	glutCreateWindow("Teapots");
	//实现屏幕图像渲染函数renderScene
	glutDisplayFunc(display);

	glutMainLoop();
}