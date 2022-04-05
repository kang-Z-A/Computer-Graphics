#include <Windows.h>
#include <GL/glut.h>

void display() {
	glClearColor(1, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT);

	//������ã�ͨ��push()��pop()����ˢ�¾���
	glLoadIdentity();
	glPushMatrix();

	//��һ�����
	//�����ƶ�0.5����λ������y����ת180��
	glTranslatef(-0.5, 0, 0);
	glRotatef(180, 0, 1, 0);
	glColor3f(0, 1, 0);
	glutWireTeapot(0.3);

	glPopMatrix();
	glPushMatrix();

	//�ڶ������
	//�����ƶ�0.5����λ
	glTranslatef(0, 0.5, 0);
	//��СΪԭ����һ��
	glScalef(0.5, 0.5, 0.5);
	glColor3f(0, 0, 1);
	glutSolidTeapot(0.3);

	glPopMatrix();

	//���������
	//�����ƶ�0.5����λ
	glTranslatef(0.5, 0, 0);
	glColor3f(1, 0, 0);
	glutWireTeapot(0.3);

	glutSwapBuffers();
}

void main(int argc, char* argv[]) {
	//��ʼ��glut
	glutInit(&argc, argv);
	//�������ڣ���ɫѡ��RGBģʽ��˫������
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	//ѡ�񴰿�����Ļ�е�λ��
	glutInitWindowPosition(100, 150);
	//���ô��ڴ�С
	glutInitWindowSize(640, 480);
	//��������
	glutCreateWindow("Teapots");
	//ʵ����Ļͼ����Ⱦ����renderScene
	glutDisplayFunc(display);

	glutMainLoop();
}