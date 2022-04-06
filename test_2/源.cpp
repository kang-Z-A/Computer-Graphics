#include <stdio.h>
#include <math.h>
#include <GL\glut.h>


//�Ե�Ϊģ�͵���Dot
class Dot {
public :
	GLfloat x, y;

	void init(GLfloat x1, GLfloat y1) {
		x = x1;
		y = y1;
	}
};

//��������Ϊģ�͵���Triangle
class Triangle {
public:
	//dot1Ϊ���������Ϸ��Ķ��㣬dot2Ϊ��ߵĶ��㣬dot3Ϊ�ұߵĶ���
	Dot dot1, dot2, dot3;

	void init(Dot d1,Dot d2,Dot d3) {
		dot1 = d1;
		dot2 = d2;
		dot3 = d3;
	}
};


//�ܹ�����243��С������
Triangle Tr[243];


//�����������߳�������
void drawTriangle(Triangle T) {
	glBegin(GL_LINE_LOOP);
	glVertex2f(T.dot1.x,T.dot1.y);
	glVertex2f(T.dot2.x, T.dot2.y);
	glVertex2f(T.dot3.x, T.dot3.y);
	glEnd();
	glFlush();
}

//�������ζ���T�з�Ϊ3��С�����β��洢��Triangle������
void part(Triangle T,GLint temp, GLint i, GLint j) {

	/*
	�������������ߵ��е㣬�ɴ��齨�����µ�������
	leftΪ����е㣬rightΪ�ұ��е㣬bottomΪ�ײ��е�
	*/
	Dot left{}, right{}, bottom{};

	//indexΪ�����ɵ��������ڶ������еļ��
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

//��Ļ��Ⱦ����
void renderScene() {
	glClear(GL_COLOR_BUFFER_BIT);

	Dot D1{}, D2{}, D3{};
	GLint i = 0, j = 0;

	//��ʼ����������ε������������
	D1.init(0.0, 0.6);
	D2.init(-0.6, -0.6);
	D3.init(0.6, -0.6);

	//��ʼ�������������������
	Tr[i].init(D1, D2, D3);


	//ͨ��ѭ��ʵ��л����˹����Ȧ���ܹ�����4��Ƕ�׷ָ�
	for (i = 0; i < 4; i++) {

		//ÿ��ѭ������temp��ֵ��tempΪ��ǰTriangle��������ÿ��������֮��ļ��
		GLint temp = 243 / pow(3, i);

		//ͨ��pow(3,i)ȷ������Triangle�������������������θ�����Ҳ�����ѭ��Ҫ�ָ�������θ���
		for (j = 0; j<pow(3,i); j++) {
			part(Tr[temp*j],temp,i,j);
		}
	}
	

	//����Ļ���������������
	for (i = 0; i <= 242; i++) {
		drawTriangle(Tr[i]);
	}
	
}

void main(int argc,char* argv[]) {
	//��ʼ��glut
	glutInit(&argc, argv);
	//�������ڣ���ɫѡ��RGBģʽ����������
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	//ѡ�񴰿�����Ļ�е�λ��
	glutInitWindowPosition(100, 150);
	//���ô��ڴ�С
	glutInitWindowSize(640, 480);
	//��������
	glutCreateWindow("sierpinski gasket");
	//ʵ����Ļͼ����Ⱦ����renderScene
	glutDisplayFunc(renderScene);

	glutMainLoop();
}

//second git edit