// OpenGL_FrameWork.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include "pch.h"
#include "MainApp.h"
#include "Camera_Debug.h"

int		iWindow = 0;
void	Render();
void	ViewPort(int iWinX, int iWinY);
void	Release();
void	Update(int value);
void	Keyboard(unsigned char key, int x, int y);
_float	fTimeDelta = 0.f;

bool	IsCull = true;
bool	IsLine = false;
bool	IsReturn = false;
bool	IsCam = false;
_float timebase = 0.f;
CMainApp*	pMainApp = new CMainApp;
int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(200, 200);
	glutInitWindowSize(WINCX, WINCY);

	iWindow = glutCreateWindow("OpenGL_FrameWork");

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		cout << "Unalbe to init GLEW" << endl;
		exit(EXIT_FAILURE);
	}
	else
		cout << "GLEW Init" << endl;

	PlaySound(TEXT(SOUND_FILE), NULL, SND_ASYNC | SND_LOOP);

	pMainApp->Init();


	glutDisplayFunc(Render);
	glutReshapeFunc(ViewPort);
	glutTimerFunc(0, Update, 0);
	glutKeyboardFunc(Keyboard);
	glutCloseFunc(Release);

	glutMainLoop();
}

void Render() 
{
	glClearColor(0.f, 0.f, 1.f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
	 
	pMainApp->Render();

	glutSwapBuffers();
}

void ViewPort(int iWinX, int iWinY)
{
	glViewport(0, 0, iWinX, iWinY);
}

void Release()
{
	delete pMainApp;
}

void Update(int value)
{
	_float frame = 0.f;
	_int fTime = 0.f;
	frame++;
	fTime = glutGet(GLUT_ELAPSED_TIME);
	const int desiredFPS = 60;




	glutTimerFunc(1000 / desiredFPS, Update, ++value);
	pMainApp->Update(0.f);


	glutPostRedisplay();
}

void Keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 27:
		glutDestroyWindow(iWindow);
		break;
	case 'h':
	case 'H':
		IsCull ^= true;
		break;
	case 'w':
	case 'W':
		IsLine ^= true;
		break;
	case'c':
		break;
	}
}
