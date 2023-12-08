#include <windows.h>
#include "yuhanCG.h"
#include "cube.h"

// ��ư���� L��ư�� Ŭ���� �Ǿ�� �׷����� ����
bool LbuttonPressed = false;
bool SpacePressed = false;
bool LbuttonCube = false;
int Shape = 0;
int isMoving = 0;

// �׸��µ� �ʿ��� �༮��
POINT startPoint = { 0 };
POINT endPoint = { 0 };
RECT rectangle1 = { 0,0,0,0 }; // �簢�� �ʱ�ȭ
RECT Eclip = { 0,0,0,0 }; // �� �ʱ�ȭ
RECT Box = { 8, 8, 792, 472 }; // �׵θ�
HRGN cube = NULL;
POINT standardPoint = { 0 };

HBRUSH hBrush_background = CreateSolidBrush(RGB(255, 240, 200)); // ���귯��
HBRUSH hBrush_background1 = CreateSolidBrush(RGB(255, 255, 255));// �� ��� �귯��

// ������ ���ν���
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	switch (message) {
	case WM_KEYDOWN:
		if (wParam == VK_SPACE)
		{
			if (SpacePressed == false) {
				SpacePressed = true;
			}

			InvalidateRect(hWnd, NULL, TRUE);
		}
		break;
	case WM_KEYUP:
		if (wParam == VK_SPACE) {
			if (SpacePressed == true) {
				SpacePressed = false;
			}
			InvalidateRect(hWnd, NULL, TRUE);
		}
		break;
	case WM_GETMINMAXINFO: {
		RECT rect = { 0, 0, 800, 480 }; // ���ϴ� Ŭ���̾�Ʈ ������ ũ��
		AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);

		MINMAXINFO* minmax = (MINMAXINFO*)lParam;
		minmax->ptMinTrackSize.x = rect.right - rect.left;
		minmax->ptMinTrackSize.y = rect.bottom - rect.top;
		minmax->ptMaxTrackSize.x = rect.right - rect.left;
		minmax->ptMaxTrackSize.y = rect.bottom - rect.top;
	}
						 return 0;
	case WM_COMMAND:
		if (LOWORD(wParam) == 1) {
			rectangle1 = { 0,0,0,0 };
			// ù ��° ��ư Ŭ��
			Shape = 1;
			SetFocus(hWnd);
			InvalidateRect(hWnd, NULL, TRUE);
		}
		else if (LOWORD(wParam) == 2) {
			Eclip = { 0,0,0,0 };
			// �� ��° ��ư Ŭ��
			Shape = 2;
			SetFocus(hWnd);
			InvalidateRect(hWnd, NULL, TRUE);
		}
		else if (LOWORD(wParam) == 3) {
			// �� ��° ��ư Ŭ��
			Shape = 3;
			SetFocus(hWnd);
			InvalidateRect(hWnd, NULL, TRUE);
		}
		else if (LOWORD(wParam) == 4) {
			// �� ��° ��ư Ŭ��
			startPoint = { 0 };
			endPoint = { 0 };
			Shape = 4;
			SetFocus(hWnd);
			InvalidateRect(hWnd, NULL, TRUE);
		}
		else if (LOWORD(wParam) == 5) {
			startPoint = { 0 };
			endPoint = { 0 };
			Shape = 5;
			SetFocus(hWnd);
			InvalidateRect(hWnd, NULL, TRUE);
		}
		break;
	case WM_PAINT: {
		RECT rect;
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);

		SelectObject(hdc, hBrush_background);
		Rectangle(hdc, Box.left, Box.top, Box.right, Box.bottom);

		EndPaint(hWnd, &ps);
		break;
	}
				 break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

LRESULT CALLBACK drawingViewWndProc(HWND drawingView, UINT message, WPARAM wParam, LPARAM lParam) {
	switch (message) {
	case WM_PAINT: {
		RECT rect;
		GetClientRect(drawingView, &rect);
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(drawingView, &ps);
		FillRect(hdc, &rect, hBrush_background1);

		if (Shape == 1) {
			Rectangle(hdc, rectangle1.left, rectangle1.top, rectangle1.right, rectangle1.bottom);
		}
		if (Shape == 2) {
			Ellipse(hdc, Eclip.left, Eclip.top, Eclip.right, Eclip.bottom);
		}
		if (Shape == 3) {
			int blink = SpacePressed;
			DrawBonobono(drawingView, hdc, blink);
		}
		if (Shape == 4) {
			int left = startPoint.x;
			int top = startPoint.y;
			int right = endPoint.x;
			int bottom = endPoint.y;

			DrawRyan(drawingView, hdc, left, top, right, bottom);
		}
		if (Shape == 5) {
			cube = Drawcube(drawingView, hdc, startPoint, endPoint);
		}

		EndPaint(drawingView, &ps);
		break;
	}
				 break;
	case WM_LBUTTONDOWN: {
		if (PtInRegion(cube, LOWORD(lParam), HIWORD(lParam))) {
			LbuttonCube = true;
			//startpoint�� ť�� ������ Ŭ���� ��ǥ����
		}
		else {
			LbuttonPressed = true;
		}
		if (Shape == 1 || Shape == 2 || Shape == 4) {
			startPoint.x = LOWORD(lParam);
			startPoint.y = HIWORD(lParam);
		}
		if (Shape == 5) {
			if (LbuttonCube == true) {
				standardPoint.x = LOWORD(lParam);
				standardPoint.y = HIWORD(lParam);
			}
			else {
				startPoint.x = LOWORD(lParam);
				startPoint.y = HIWORD(lParam);
			}
		}

	}break;
	case WM_LBUTTONUP: {
		LbuttonPressed = false;
		if (LbuttonCube)
		{
			LbuttonCube = false;
		}
	}break;

	case WM_RBUTTONDOWN:
	{
		if (PtInRect(&rectangle1, { LOWORD(lParam), HIWORD(lParam) })) // ���� �������ο��� Ŭ���ϸ�
		{
			// �������ο� Ŭ���� ������ �������� �簢���� �̵���Ŵ
			isMoving = 1;
			startPoint.x = LOWORD(lParam);
			startPoint.y = HIWORD(lParam);
		}
		if (PtInRegion(cube, LOWORD(lParam), HIWORD(lParam))) {
			// cube�� lParam���� startpoint�� �����ϸ� ũ�Ⱑ ���� �׷��� ���ο� �����͸� �����
			isMoving = 2;
			standardPoint.x = LOWORD(lParam);
			standardPoint.y = HIWORD(lParam);
		}
	}
	return 0;

	case WM_RBUTTONUP:
	{
		if (isMoving > 0)
		{
			isMoving = 0;
		}
	}
	return 0;

	case WM_MOUSEMOVE:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(drawingView, &ps);
		POINT currentPoint = { 0 };

		currentPoint.x = LOWORD(lParam);
		currentPoint.y = HIWORD(lParam);

		// standardPoint(������)�� currentPoint ������ ���̸� ���
		int deltaX = 0;
		int deltaY = 0;
		deltaX = currentPoint.x - standardPoint.x;
		deltaY = currentPoint.y - standardPoint.y;

		if (LbuttonPressed) {
			endPoint.x = LOWORD(lParam);
			endPoint.y = HIWORD(lParam);
			if (Shape == 1 || Shape == 2)
			{
				rectangle1 = Drawrect(rectangle1, startPoint, endPoint);
				Eclip = Drawrect(Eclip, startPoint, endPoint);
				// WM_PAINT �޽����� �����Ͽ� ȭ�鿡 �׸��ϴ�.
			}
			InvalidateRect(drawingView, NULL, TRUE);
		}

		if (isMoving == 1)
		{
			rectangle1 = MoveRactangle(lParam, rectangle1, startPoint);
			Eclip = ScaleCircle(lParam, Eclip, startPoint);

			int mouseX = LOWORD(lParam);
			int mouseY = HIWORD(lParam);
			startPoint.x = mouseX;
			startPoint.y = mouseY;

			// WM_PAINT �޽����� �����Ͽ� ������ ȭ�鿡 �׸��ϴ�.
			InvalidateRect(drawingView, NULL, TRUE);
		}
		else if (isMoving == 2) {
			// ť�� �̵�
			Movecube(&startPoint, &endPoint, deltaX, deltaY);
			cube = Drawcube(drawingView, hdc, startPoint, endPoint);

			standardPoint = currentPoint;// �巡������ ���� ��ǥ�� �������� �����Ѵ�.(�������� �̵��� ��)
			// WM_PAINT �޽����� �����Ͽ� ������ ȭ�鿡 �׸��ϴ�.
			InvalidateRect(drawingView, NULL, TRUE);
		}
		if (LbuttonCube) {
			// �������� stardPoint�� ���۰� ���� �������ִ�.
			// ť�� ũ�� ����
			ScaleCube(lParam, &startPoint, &endPoint, standardPoint);
			cube = Drawcube(drawingView, hdc, startPoint, endPoint);

			standardPoint = currentPoint;
			// �巡������ ���� ��ǥ�� �������� �����Ѵ�.(�������� �̵��� ��)
			// WM_PAINT �޽����� �����Ͽ� ������ ȭ�鿡 �׸��ϴ�.
			InvalidateRect(drawingView, NULL, TRUE);
		}

	}
	return 0;

	default:
		return CallWindowProc(DefWindowProc, drawingView, message, wParam, lParam);
	}
	return 0;
}

// ���α׷� ������
int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow) {

	HWND hButton1, hButton2, hButton3, hButton4, hButton5;

	HBRUSH hBrush_background = CreateSolidBrush(RGB(255, 240, 200));
	WNDCLASSEX wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(hBrush_background);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = L"ButtonWindowClass";
	wcex.hIconSm = LoadIcon(wcex.hInstance, IDI_APPLICATION);

	if (!RegisterClassEx(&wcex)) {
		exit(-1);
	}

	// Window viewport ���� ����
	RECT rect = { 0, 0, 800, 480 };
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, 0);
	int width = rect.right - rect.left;
	int height = rect.bottom - rect.top;

	// ������ ����
	HWND hWnd = CreateWindow(
		wcex.lpszClassName,
		TEXT("������"),
		WS_OVERLAPPEDWINDOW,
		0, 0,
		width, height,
		NULL, NULL,
		hInstance,
		NULL
	);

	WNDCLASSEX wcDrawing;
	wcDrawing.cbSize = sizeof(WNDCLASSEX);
	wcDrawing.style = CS_HREDRAW | CS_VREDRAW;
	wcDrawing.lpfnWndProc = drawingViewWndProc; // ����� ���� �޽��� ó�� �Լ�
	wcDrawing.cbClsExtra = 0;
	wcDrawing.cbWndExtra = 0;
	wcDrawing.hInstance = hInstance;
	wcDrawing.hIcon = NULL;
	wcDrawing.hCursor = LoadCursor(NULL, IDC_CROSS); // ���콺 �����͸� ���ڰ��� ����
	wcDrawing.hbrBackground = (HBRUSH)(GetStockObject(WHITE_BRUSH));
	wcDrawing.lpszMenuName = NULL;
	wcDrawing.lpszClassName = L"DrawingViewClass";
	wcDrawing.hIconSm = NULL;

	RegisterClassEx(&wcDrawing);


	HWND drawingView = CreateWindow(
		L"DrawingViewClass", L"", // Ŭ���� �̸��� â ����
		WS_CHILD | WS_VISIBLE,
		16, 88, 768, 376, // ��ġ�� ũ�� ����
		hWnd, NULL, // �θ� â�� �޴� �ڵ�
		hInstance, NULL
	);

	SetWindowLongPtr(drawingView, GWLP_USERDATA, (LONG_PTR)hWnd); // �θ� ������ �ڵ� ����
	SetWindowLongPtr(drawingView, GWLP_WNDPROC, (LONG_PTR)drawingViewWndProc); // Ŀ���� ������ ���ν��� ����

	if (!drawingView) {
		return -1;
	}

	if (!hWnd) {
		return FALSE;
	}

	hButton1 = CreateWindow(
		L"BUTTON", L"Box", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		16, 16, 140, 64, hWnd, (HMENU)1, hInstance, NULL);

	hButton2 = CreateWindow(
		L"BUTTON", L"Circle", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		172, 16, 140, 64, hWnd, (HMENU)2, hInstance, NULL);

	hButton3 = CreateWindow(
		L"BUTTON", L"Bonobono", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		328, 16, 140, 64, hWnd, (HMENU)3, hInstance, NULL);

	hButton4 = CreateWindow(
		L"BUTTON", L"Ryan", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		484, 16, 140, 64, hWnd, (HMENU)4, hInstance, NULL);

	hButton5 = CreateWindow(
		L"BUTTON", L"ť��", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		640, 16, 140, 64, hWnd, (HMENU)5, hInstance, NULL);

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	// �޽��� ����
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0)) { // get���� �޽��� �����
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return (int)msg.wParam;
}