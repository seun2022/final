#include "test.h"
#include <Windows.h>

//�߾� 400, 240 392 233

void Drawcube1(HWND hWnd, HDC hdc, POINT start, POINT end) {// �»�
	POINT MINPOINT = { 0 };
	POINT MAXPOINT = { 0 };

	MINPOINT.x = min(start.x, end.x);
	MINPOINT.y = min(start.y, end.y);
	MAXPOINT.x = max(start.x, end.x);
	MAXPOINT.y = max(start.y, end.y);


	MoveToEx(hdc, 376, 0, NULL);
	LineTo(hdc, 376, 480);
	MoveToEx(hdc, 0, 184, NULL);
	LineTo(hdc, 800, 184);



	int width = abs(MINPOINT.x - MAXPOINT.x);
	int height = abs(MINPOINT.y - MAXPOINT.y);
	int centerX = width / 2;
	int centerY = height / 2;
	POINT centerPoint = { MINPOINT.x + centerX, MINPOINT.y + centerY };

	MoveToEx(hdc, MINPOINT.x, MAXPOINT.y, NULL); //�ظ� �ݽð��
	LineTo(hdc, MAXPOINT.x - centerX / 2, MAXPOINT.y);
	LineTo(hdc, MAXPOINT.x, MAXPOINT.y - centerY / 2);
	LineTo(hdc, MINPOINT.x + centerX / 2, MAXPOINT.y - centerY / 2);
	LineTo(hdc, MINPOINT.x, MAXPOINT.y);

	MoveToEx(hdc, MAXPOINT.x, MAXPOINT.y - centerY / 2, NULL); // �ո� �ݽð��
	LineTo(hdc, MAXPOINT.x, MINPOINT.y);
	LineTo(hdc, MINPOINT.x + centerX / 2, MINPOINT.y);
	LineTo(hdc, MINPOINT.x + centerX / 2, MAXPOINT.y - centerY / 2);

	MoveToEx(hdc, MINPOINT.x + centerX / 2, MINPOINT.y, NULL); // ���� ���Ͻ��� �ݽð�
	LineTo(hdc, MINPOINT.x, MINPOINT.y + centerY / 2);
	LineTo(hdc, MINPOINT.x, MAXPOINT.y);
}
//1 ��

void Drawcube2(HWND hWnd, HDC hdc, POINT start, POINT end) {// ����
	POINT MINPOINT = { 0 };
	POINT MAXPOINT = { 0 };

	MINPOINT.x = min(start.x, end.x);
	MINPOINT.y = min(start.y, end.y);
	MAXPOINT.x = max(start.x, end.x);
	MAXPOINT.y = max(start.y, end.y);

	int width = abs(MINPOINT.x - MAXPOINT.x);
	int height = abs(MINPOINT.y - MAXPOINT.y);
	int centerX = width / 2;
	int centerY = height / 2;
	POINT centerPoint = { MINPOINT.x + centerX, MINPOINT.y + centerY };

	MoveToEx(hdc, MINPOINT.x, MINPOINT.y, NULL); //�ظ�
	LineTo(hdc, MINPOINT.x + centerX / 2, MINPOINT.y + centerY / 2);
	LineTo(hdc, MAXPOINT.x, MINPOINT.y + centerY / 2);
	LineTo(hdc, MAXPOINT.x - centerX / 2, MINPOINT.y);
	LineTo(hdc, MINPOINT.x, MINPOINT.y);//����

	MoveToEx(hdc, MINPOINT.x + centerX / 2, MINPOINT.y + centerY / 2, NULL); // �ո�
	LineTo(hdc, MINPOINT.x + centerX / 2, MAXPOINT.y);
	LineTo(hdc, MAXPOINT.x, MAXPOINT.y);
	LineTo(hdc, MAXPOINT.x, MINPOINT.y + centerY / 2);
	LineTo(hdc, MINPOINT.x + centerX / 2, MINPOINT.y + centerY / 2);//�ϳ��� �̹� ������ �׷��� ����

	MoveToEx(hdc, MINPOINT.x, MINPOINT.y, NULL); // ����
	LineTo(hdc, MINPOINT.x, MAXPOINT.y - centerY / 2);
	LineTo(hdc, MINPOINT.x + centerX / 2, MAXPOINT.y);
}
//2��

void Drawcube3(HWND hWnd, HDC hdc, POINT start, POINT end) {// ���
	POINT MINPOINT = { 0 };
	POINT MAXPOINT = { 0 };

	MINPOINT.x = min(start.x, end.x);
	MINPOINT.y = min(start.y, end.y);
	MAXPOINT.x = max(start.x, end.x);
	MAXPOINT.y = max(start.y, end.y);

	int width = abs(MINPOINT.x - MAXPOINT.x);
	int height = abs(MINPOINT.y - MAXPOINT.y);
	int centerX = width / 2;
	int centerY = height / 2;
	POINT centerPoint = { MINPOINT.x + centerX, MINPOINT.y + centerY };

	MoveToEx(hdc, MINPOINT.x, MAXPOINT.y - centerY / 2, NULL); //�ظ� �ݽð��
	LineTo(hdc, MINPOINT.x + centerX / 2, MAXPOINT.y);
	LineTo(hdc, MAXPOINT.x, MAXPOINT.y);
	LineTo(hdc, MAXPOINT.x - centerX / 2, MAXPOINT.y - centerY / 2);
	LineTo(hdc, MINPOINT.x, MAXPOINT.y - centerY / 2);

	MoveToEx(hdc, MAXPOINT.x - centerX / 2, MAXPOINT.y - centerY / 2, NULL); // �ո� �ݽð��
	LineTo(hdc, MAXPOINT.x - centerX / 2, MINPOINT.y);
	LineTo(hdc, MINPOINT.x, MINPOINT.y);
	LineTo(hdc, MINPOINT.x, MAXPOINT.y - centerY / 2);

	MoveToEx(hdc, MAXPOINT.x, MAXPOINT.y, NULL); // ���� ���Ͻ��� �ݽð�
	LineTo(hdc, MAXPOINT.x, MINPOINT.y + centerY / 2);
	LineTo(hdc, MAXPOINT.x - centerX / 2, MINPOINT.y);
}

void Drawcube4(HWND hWnd, HDC hdc, POINT start, POINT end) {// ���� �ϼ�
	POINT MINPOINT = { 0 };
	POINT MAXPOINT = { 0 };

	MINPOINT.x = min(start.x, end.x);
	MINPOINT.y = min(start.y, end.y);
	MAXPOINT.x = max(start.x, end.x);
	MAXPOINT.y = max(start.y, end.y);

	int width = abs(MINPOINT.x - MAXPOINT.x);
	int height = abs(MINPOINT.y - MAXPOINT.y);
	int centerX = width / 2;
	int centerY = height / 2;
	POINT centerPoint = { MINPOINT.x + centerX, MINPOINT.y + centerY };

	MoveToEx(hdc, MINPOINT.x + centerX / 2, MINPOINT.y, NULL); //�ظ�
	LineTo(hdc, MINPOINT.x, MINPOINT.y + centerY / 2);
	LineTo(hdc, MAXPOINT.x - centerX / 2, MINPOINT.y + centerY / 2);
	LineTo(hdc, MAXPOINT.x, MINPOINT.y);
	LineTo(hdc, MINPOINT.x + centerX / 2, MINPOINT.y);

	MoveToEx(hdc, MINPOINT.x, MINPOINT.y + centerY / 2, NULL); // �ո�
	LineTo(hdc, MINPOINT.x, MAXPOINT.y);
	LineTo(hdc, MAXPOINT.x - centerX / 2, MAXPOINT.y);
	LineTo(hdc, MAXPOINT.x - centerX / 2, MINPOINT.y + centerY / 2);//�ϳ��� �̹� ������ �׷��� ����

	MoveToEx(hdc, MAXPOINT.x, MINPOINT.y, NULL); // ����
	LineTo(hdc, MAXPOINT.x, MAXPOINT.y - centerY / 2);
	LineTo(hdc, MAXPOINT.x - centerX / 2, MAXPOINT.y);
}