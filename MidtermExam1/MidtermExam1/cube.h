#pragma once
#include <Windows.h>

HRGN Drawcube(HWND hWnd, HDC hdc, POINT MINPOINT, POINT MAXPOINT);// ť��׸��� 

void Movecube(POINT* minPoint, POINT* maxPoint, int deltaX, int deltaY);//ť���̵�

void ScaleCube(LPARAM lParam, POINT* minPoint, POINT* maxPoint, POINT standard);//ť��ũ������(���� ũ�⸦ ���̰� ���� Ű��� ť���� ������ �޶���)