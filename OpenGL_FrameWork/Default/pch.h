// 시작을 위한 팁: 
//   1. [솔루션 탐색기] 창을 사용하여 파일을 추가/관리합니다.
//   2. [팀 탐색기] 창을 사용하여 소스 제어에 연결합니다.
//   3. [출력] 창을 사용하여 빌드 출력 및 기타 메시지를 확인합니다.
//   4. [오류 목록] 창을 사용하여 오류를 봅니다.
//   5. [프로젝트] > [새 항목 추가]로 이동하여 새 코드 파일을 만들거나, [프로젝트] > [기존 항목 추가]로 이동하여 기존 코드 파일을 프로젝트에 추가합니다.
//   6. 나중에 이 프로젝트를 다시 열려면 [파일] > [열기] > [프로젝트]로 이동하고 .sln 파일을 선택합니다.

#ifndef PCH_H
#define PCH_H
#define SOUND_FILE		"../Sound/BGM.wav"
#define FOOD_SOUND_FILE		"../Sound/coin.wav"
#define RESTART_SOUND_FILE		"../Sound/restart.wav"
#pragma commnet(lib,"winmm.lib")
#include <Windows.h>
#include <mmsystem.h>
#include <iostream>
#include "GL/glew.h "
#include "GL/freeglut.h"
#include "GL/glm/glm/glm.hpp"
#include "GL/glm/glm/ext.hpp"
#include "GL/glm/glm/gtc/matrix_transform.hpp"
//#include "GL/glfw/glfw3.h"
//#include "GL/glfw/glfw3native.h"
#include <vector>
#include <list>
#include <map>
#include <string>
#include <fstream>
#include <algorithm>
#include <math.h>
#include <time.h>




using namespace std;
using namespace glm;

#include "d3d9.h"
#include "d3dx9.h"

#define DIRECTINPUT_VERSION 0x0800
#include "dinput.h"

#include "Define.h"
#include "Constant.h"
#include "Extern.h"
#include "Function.h"
#include "Typedef.h"
#include "Enum.h"
#include "Struct.h"

#include "ObjectMgr.h"
#include "Abstract_Factory.h"
#include "ShaderMgr.h"
#include "KeyMgr.h"
#include "CameraMgr.h"
#include "InputMgr.h"
#include "TextureMgr.h"
#include "CollisionMgr.h"




#endif //PCH_H
