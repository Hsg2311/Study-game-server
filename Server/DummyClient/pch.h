#ifndef PCH_H
#define PCH_H

#define WIN32_LEAN_AND_MEAN             // ���� ������ �ʴ� ������ Windows ������� �����մϴ�.

#ifdef _DEBUG
#pragma comment(lib, "Debug/ServerCore.lib")
#else
#pragma comment(lib, "Release/ServerCore.lib")
#endif

#include "CorePch.h"

#endif //PCH_H