/*
*	本程序名称：EasyX 绘图库硬核实现 颜色诱捕器（鼠标移动获取电脑像素点各颜色值）
*	编译环镜：Microsoft Visual Studio Community 2019或2022版本 16.10.0
*	绘图库：EasyX_20221109
*	电脑系统：Win10 1809
*	作者：思奈理&奈叶敬 2734596919@qq.com
*	程序起始时间：2022 - 7 - 10
*	程序最后结束修改时间：2022 - 8 - 14 0:19
*
*	目的：实现用 EasyX 绘图库做一个简单的获取桌面各种图像的颜色值，给需要编写 GUI 程序按钮等有配色的需求的小伙伴们一个硬核参考。
*	历史：本是一个为输入框和按钮协同作战例子，改为一个猎取桌面颜色的小程序。
*	编译调试建议：无。
*
*	代码函数定义位置顺序排列如下：
*	lnitial_drawing -> settextzise - > CaptureImagb - > RGBfillrec - > RGBToLAB - >RGBtoCMYK
*	- >putcolorvalue
*/
#define WINVER 0x0A00
#define _WIN32_WINNT 0x0A00
//EasyX (EasyX Graphics Library, https://easyx.cn/)
#include <easyxgraphics.h>  //<graphics.h>

#include <string.h>
#include <windows.h>
//#pragma comment(lib, "libEasyX libgdi32 libole32")
#include <conio.h>					// 基本头文件
#include <algorithm>					// 针对设置该进程不受系统 DPI 设置影响 的头文件



#include <stdio.h>      // for printf
#include <string.h>     // for strnlen
#include <stdlib.h>     // for _countof, _itoa fns, _MAX_COUNT macros


#include <math.h>
// 引用头文件
#pragma comment(lib, "Shcore.lib")	// 链接库文件

void lnitial_drawing();																			// 初始化函数
void settextzise(int zise);																// 字体大小设置函数
void CaptureImagb(struct textbox_xy* color_data1, int* r, int* g, int* b, IMAGE* img1, IMAGE* img2, IMAGE* img3,
	IMAGE* img4, int x1, int y1, int x2, int y2, int w, int h, bool bl);
void RGBfillrec(int* r, int* g, int* b, int x1, int y1, int x2, int y2);
void RGBtoCMYK(COLORREF rgb, double* c, double* m, double* y, double* k);
void putcolorvalue(struct textbox_xy* color_data1, int* r, int* g, int* b, int x1, int y1, int x2, int y2);
int button(int x1, int y1, int x2, int y2, int mouse_x, int mouse_y, int textsize1, int textsize2,
	LPCTSTR button_string1, LPCTSTR button_string2, int click_1);
TCHAR* textbox1(TCHAR* STRING1, TCHAR* STRING0, int x1, int y1, int x2, int y2, int mouse_x, int mouse_y, int textsize1,
	int click_1, bool GETIMAGE);
int textboxparm(int mouse_x, int mouse_y, struct textbox_xy* textbox_xy, int click, int click_1, bool kk);
int button_x(int x111, int y111, int x222, int y222, int mouse_x, int mouse_y, int click_1);
int button_i(int x111, int y111, int x222, int y222, int mouse_x, int mouse_y, int click_1);
int f1 = 2;
int f = 2;
int xX = 7;
int white = 217;
int hite = 38;
int hwite = 315 - xX;

struct textbox_xy {
	int Y2 = 30;
	int r2 = 0;
	int g2 = 0;
	int b2 = 0;

	float s = 0, h0 = 0, l = 0, s1 = 0, h1 = 0, v1 = 0;

	double l2 = 0, a2 = 0, b12 = 0;
	double cc, mm, yy, kk;

	TCHAR A1[8][40 * 5] = {
		0
	};

	TCHAR R1[50 * 2] = { 0 };
	TCHAR B1[20] = { 0 };
	TCHAR G1[20] = { 0 };

	TCHAR H1[20] = { 0 };
	TCHAR S1[20] = { 0 };
	TCHAR L1[20] = { 0 };

	TCHAR H2[20] = { 0 };
	TCHAR S2[20] = { 0 };
	TCHAR V2[20] = { 0 };

	TCHAR RX[20] = { 0 };
	TCHAR GX[20] = { 0 };
	TCHAR BX[20] = { 0 };

	TCHAR CC[20] = { 0 };
	TCHAR MM[20] = { 0 };
	TCHAR YY[20] = { 0 };
	TCHAR GETIMAGE[20] = { 0 };

	TCHAR LL[20] = { 0 };
	TCHAR AA[20] = { 0 };
	TCHAR BB[20] = { 0 };

	int xk0 = 1, xk1 = 1, yg1 = 2, yg2 = 3;


	int ss = 4;
	HDC hDC = GetDC(NULL);
	// 获取桌面 DC
	HDC srcDC1 = GetDC(NULL);
	HDC srcDC2 = GetDC(NULL);
	HDC srcDC3 = GetDC(NULL);
	HDC srcDC4 = GetDC(NULL);

	HDC dstDC1;
	HDC dstDC2;
	HDC dstDC3;
	HDC dstDC4;
	HDC hDC0 = GetDC(NULL);
	POINT pt;

	int addg[11][3] = {
		{3, 1},
		{7, 4},
		{15, 8},
		{26, 14},
		{38, 20},
		{48, 20},
		{54, 28},

	};

	//HWND h1=NULL;
	// 诱捕鼠标移动的放大图像，并可视化输出在圆角矩形内
	int xxdd = 1, yydd = 1;
	int xxd = 53 + xxdd, yyd = 28 + yydd;

	int f2 = 0;

	TCHAR textbox_stringchar1[7][8][15] = {
		{ _T("X_Y") },
		{ _T("RGB") },
		{ _T("HSV")},
		{ _T("HEX1") },
		{ _T("HEX2") },
		{ _T("CMYK") },
	};

	int textbox_int[7][15]
		= {			// 三维数组的巧妙应用于，鼠标移动到输入框位置发生不一样选择，原始按的钮坐标，输入框文本，字体大小数据用于生成模版配置文件。
			{4 + xk0, 5 + hite - yg1, 134 + 10 + 4 - xk1, 25 + hite - yg2, 11},
			{4 + xk0, 25 + hite - yg1, 134 + 10 + 4 - xk1, 45 + hite - yg2, 11},
			{4 + xk0, 45 + hite - yg1, 134 + 10 + 4 - xk1, 65 + hite - yg2, 11},
			{4 + xk0, 65 + hite - yg1, 134 + 10 + 4 - xk1, 85 + hite - yg2, 11},
			{4 + xk0, 85 + hite - yg1, 134 + 10 + 4 - xk1, 105 + hite - yg2, 11},
			{4 + xk0, 105 + hite - yg1, 134 + 10 + 4 - xk1, 125 + hite - yg2, 11},
	};

};

void SetDataToClip(LPCTSTR ADD) {
	// 打开剪贴板
	if (!OpenClipboard(NULL) || !EmptyClipboard()) {
		printf("打开或清空剪切板出错！/n");
		return;
	}
	size_t i1;
	//TCHAR 转 char
	HGLOBAL hMen;
	char strText[500 * 4] = { 0 };
	strcpy(strText, ADD);
	//	wcstombs_s(strText, ADD, strlen(ADD));
//	wcstombs_s( strText, (size_t)500 * 4, ADD, strlen(ADD));
	// 分配全局内存
	hMen = GlobalAlloc(GMEM_MOVEABLE, ((strlen(strText) + 1) * sizeof(TCHAR)));
	if (!hMen) {
		printf("分配全局内存出错！/n");
		// 关闭剪切板
		CloseClipboard();
		return;
	}
	// 把数据拷贝考全局内存中
	// 锁住内存区
	LPSTR lpStr = (LPSTR)GlobalLock(hMen);
	if (lpStr == NULL)
		return;
	// 内存复制
	memcpy(lpStr, strText, ((strlen(strText)) * sizeof(TCHAR)));
	// 字符结束符
	lpStr[strlen(strText)] = (TCHAR)0;
	// 释放锁
	GlobalUnlock(hMen);
	// 把内存中的数据放到剪切板上
	SetClipboardData(CF_TEXT, hMen);
	CloseClipboard();
	return;
}

// 将诱捕的颜色值转为 CMYK 色值数据函数
void RGBtoCMYK(COLORREF rgb, double* c, double* m, double* y, double* k)


{
	BYTE R = GetRValue(rgb);

	BYTE G = GetGValue(rgb);

	BYTE B = GetBValue(rgb);

	////	*k = (int)(min(min(255 - R, 255 - G), 255 - B) / 2.55);

	double MyR = R / 2.55;

	double Div = 100 - *k;

	if (Div == 0)
		Div = 1;

	*c = ((100 - MyR - *k) / Div) * 100;

	int MyG = (int)(G / 2.55);

	*m = ((100 - (double)MyG - (double)*k) / Div) * 100;

	int MyB = (int)(B / 2.55);

	*y = ((100 - (double)MyB - (double)*k) / Div) * 100;

}

// 初始化函数
void lnitial_drawing() {
	// 设置该进程不受系统 DPI 设置影响
////	SetProcessDpiAwareness(PROCESS_PER_MONITOR_DPI_AWARE);
	initgraph(white, hwite, 1);
	setbkmode(RGB(61, 68, 89));
	cleardevice();

	setbkcolor(RGB(61, 68, 89));

	cleardevice();
	settextcolor(RGB(0, 132, 132));
}

void CaptureImagb(struct textbox_xy* color_data1, int* r, int* g, int* b, IMAGE* img1, IMAGE* img2, IMAGE* img3,

	IMAGE* img4, int x1, int y1, int x2, int y2, int w, int h, bool bl) {
	IMAGE img;

	int white1 = 3;

	GetCursorPos(&color_data1->pt);
	// 获取当前鼠标点像素值
	COLORREF clr1 = GetPixel(color_data1->hDC0, color_data1->pt.x, color_data1->pt.y);

	int r1 = GetRValue(clr1);	// 分解出红色值
	int g1 = GetGValue(clr1);	// 分解出绿色值
	int b1 = GetBValue(clr1);	// 分解出蓝色值

	setfillcolor(RGB(53, 53, 53));
	setlinecolor(RGB(61, 68, 89));
	roundrect(x1, y1 - white1, x2, y2, 10, 10);

	setfillcolor(RGB(53, 53, 53));
	fillroundrect(x1 + 1, y1 + 1 - white1, x2 - 1, y2 - 1, 10, 10);

	setfillcolor(RGB(53, 53, 53));
	fillroundrect(x1 + 1, y1 + 1 - white1, x2 - 1, y2 - 1, 8, 8);

	putimage(x1 + 2, y1 + 25 - 0, img1);
	putimage(x1 + 106 + 1 + 1, y1 + 25 - 0, img2);
	putimage(x1 + 2, y1 + 25 + 55, img3);
	putimage(x1 + 106 + 1 + 1, y1 + 25 + 55, img4);

	roundrect(x1 + 1, y1 + 1 - white1, x2 - 1, y2 - 1, 10, 10);
	roundrect(x1 + 1, y1 + 1 - white1, x2 - 1, y2 - 1, 8, 8);

	setlinecolor(RGB(61, 68, 89));
	line(x1 + 2, y1 + 25 - 2, x2 - 2, y1 + 25 - 2);
	line(x1 + 2, y1 + 25 - 1, x2 - 2, y1 + 25 - 1);

	setlinecolor(RED);
	line(x1 + 107, y1 + 80, x1 + 107, y1 + 80 - 5);
	line(x1 + 107, y1 + 80, x1 + 107 + 5, y1 + 80);
	line(x1 + 107, y1 + 80, x1 + 107, y1 + 80 + 5);
	line(x1 + 107, y1 + 80, x1 + 107 - 5, y1 + 80);




	if (bl == true)
		setlinecolor(RGB(r1, g1, b1));
	if (bl == true)
		line(x1 + 107, y1 + 80, x1 + 107 + 20, y1 + 80 - 20);
	if (bl == true)
		line(x1 + 107, y1 + 80, x1 + 107 + 20, y1 + 80 + 20);
	if (bl == true)
		line(x1 + 107, y1 + 80, x1 + 107 - 20, y1 + 80 + 20);
	if (bl == true)
		line(x1 + 107, y1 + 80, x1 + 107 - 20, y1 + 80 - 20);

	if (bl == true)
		circle(x1 + 106, y1 + 80, 15);

	color_data1->dstDC1 = GetImageHDC(img1);
	color_data1->dstDC2 = GetImageHDC(img2);
	color_data1->dstDC3 = GetImageHDC(img3);
	color_data1->dstDC4 = GetImageHDC(img4);
	// 得到当前鼠标所在位置
	//POINT pt;
	//GetCursorPos(&pt);
	// 获取当前鼠标点像素值
	//COLORREF clr1 = GetPixel(hDC, pt.x, pt.y);

	*r = GetRValue(clr1);	// 分解出红色值
	*g = GetGValue(clr1);	// 分解出绿色值
	*b = GetBValue(clr1);	// 分解出蓝色值
	color_data1->r2 = *r;
	color_data1->g2 = *g;
	color_data1->b2 = *b;
	TCHAR XY[250] = { 0 };
	if (bl == true)
		sprintf(XY, _T("%d x %d"), color_data1->pt.x, color_data1->pt.y);
	if (bl == true)
		_tcscpy_s(color_data1->A1[0], XY);

	RGBtoHSL(RGB(*r, *g, *b), &color_data1->s, &color_data1->h0, &color_data1->l);
	RGBtoHSV(RGB(*r, *g, *b), &color_data1->s1, &color_data1->h1, &color_data1->v1);

	sprintf(color_data1->R1, _T("%d"), color_data1->r2);
	sprintf(color_data1->G1, _T("%d"), color_data1->g2);
	sprintf(color_data1->B1, _T("%d"), color_data1->b2);

	sprintf(color_data1->S1, _T("%.3f"), color_data1->s);
	sprintf(color_data1->H1, _T("%.3f"), color_data1->h0);
	sprintf(color_data1->L1, _T("%.3f"), color_data1->l);

	int ss = 0, hh = 0, vv = 0;
	int ss1 = 0, hh1 = 0, vv1 = 0;

	if ((ss = (int)color_data1->s1) == color_data1->s1) {
		sprintf(color_data1->S2, _T("%d"), (int)color_data1->s1);
	}
	else {
		sprintf(color_data1->S2, _T("%d"), (int)color_data1->s1);
	}
	if ((hh = (int)color_data1->h1) == color_data1->h1) {
		sprintf(color_data1->H2, _T("%d"), (int)color_data1->h1);
	}
	else {
		sprintf(color_data1->H2, _T("%d"), hh = (long)round((long)color_data1->h1 * 100));
	}

	if ((vv = (int)color_data1->v1) == color_data1->v1) {
		sprintf(color_data1->V2, _T("%d"), (int)color_data1->v1);
	}
	else {
		sprintf(color_data1->V2, _T("%d"), vv = (long)round((long)color_data1->v1 * 100));
	}

	TCHAR HEX[600] = { _T("#") };
	TCHAR HEX2[600] = { _T("0x") };

	itoa(*r, color_data1->RX, 16);
	itoa(*g, color_data1->GX, 16);
	itoa(*b, color_data1->BX, 16);
	if (strlen(color_data1->RX) == 1) {
		TCHAR RX1[100] = { 0 };
		strcpy(RX1, color_data1->RX);
		strcpy(color_data1->RX, _T("\0"));

		strcat(color_data1->RX, _T("0"));
		strcat(color_data1->RX, RX1);
	}
	if (strlen(color_data1->GX) == 1) {
		TCHAR GX1[100] = { 0 };
		strcpy(GX1, color_data1->GX);
		strcpy(color_data1->GX, _T("\0"));

		strcat(color_data1->GX, _T("0"));
		strcat(color_data1->GX, color_data1->GX);
	}
	if (strlen(color_data1->BX) == 1) {
		TCHAR BX1[100] = { 0 };
		strcpy(BX1, color_data1->BX);
		strcpy(color_data1->BX, _T("\0"));
		if (bl == true)
			strcat(HEX, color_data1->RX);
		if (bl == true)
			strcat(HEX, color_data1->GX);
		;

		strcat(color_data1->BX, _T("0"));
		strcat(color_data1->BX, BX1);
	}
	if (bl == true)
		strcat(HEX, color_data1->BX);
	if (bl == true)
		strcat(HEX, color_data1->GX);
	if (bl == true)
		strcat(HEX, color_data1->BX);

	if (bl == true)
		strcat(HEX2, color_data1->RX);
	if (bl == true)
		strcat(HEX2, color_data1->GX);
	if (bl == true)
		strcat(HEX2, color_data1->BX);

	if (bl == true)
		_tcscpy_s(color_data1->A1[3], HEX);
	if (bl == true)
		_tcscpy_s(color_data1->A1[4], HEX2);

	RGBtoCMYK(RGB(*r, *g, *b), &color_data1->cc, &color_data1->mm, &color_data1->yy, &color_data1->kk);

	sprintf(color_data1->CC, _T("%d"), (long)color_data1->cc);
	sprintf(color_data1->MM, _T("%d"), (long)color_data1->mm);
	sprintf(color_data1->YY, _T("%d"), (long)color_data1->yy);
	sprintf(color_data1->GETIMAGE, _T("%d"), (long)color_data1->kk);

	sprintf(color_data1->LL, _T("%.3f"), color_data1->l2);
	sprintf(color_data1->AA, _T("%.3f"), color_data1->a2);
	sprintf(color_data1->BB, _T("%.3f"), color_data1->b12);

	if (bl == true) {
		StretchBlt(color_data1->dstDC1, 0, 0, w, h, color_data1->srcDC1, color_data1->pt.x - color_data1->xxd,
			color_data1->pt.y - color_data1->yyd, color_data1->xxd, +color_data1->yyd, SRCCOPY);
		StretchBlt(color_data1->dstDC2, 0, 0, w, h, color_data1->srcDC2, color_data1->pt.x,
			color_data1->pt.y - color_data1->yyd, +color_data1->xxd, +color_data1->yyd, SRCCOPY);
		StretchBlt(color_data1->dstDC3, 0, 0, w, h, color_data1->srcDC3, color_data1->pt.x - color_data1->xxd,
			color_data1->pt.y, +color_data1->xxd, +color_data1->yyd, SRCCOPY);
		StretchBlt(color_data1->dstDC4, 0, 0, w, h, color_data1->srcDC4, color_data1->pt.x, color_data1->pt.y, color_data1->xxd,
			color_data1->yyd, SRCCOPY);
	}
	settextcolor(RGB(109, 160, 160));
	settextzise(10);
	outtextxy(0 + 14, 131 + hite + 5 - xX + 2, _T("Press any key"));
	outtextxy(0 + 3, 131 + hite + 5 - xX + 2 + 2 + 8, _T("to lock the color"));
}

void RGBfillrec(int r, int g, int b, int x1, int y1, int x2, int y2) {
	setlinecolor(RGB(61, 61, 61));

	setlinestyle(PS_SOLID | PS_JOIN_BEVEL, 1);
	roundrect(x1 + 1, y1 + 1, x2 - 1, y2 - 1, 11, 11);
	roundrect(x1 + 1, y1 + 1, x2 - 1, y2 - 1, 10, 10);
	roundrect(x1 + 1, y1 + 1, x2 - 1, y2 - 1, 9, 9);
	setlinecolor(RGB(85, 85, 85));

	setfillcolor(RGB(r, g, b));
	fillroundrect(x1 + 3, y1 + 3, x2 - 3, y2 - 3, 11, 11);
	fillroundrect(x1 + 3, y1 + 3, x2 - 3, y2 - 3, 10, 10);
	setlinestyle(PS_SOLID | PS_JOIN_BEVEL, 1);
}

void text_color(int x1, int y1, int x2, int y2, bool GETIMAGE) {
	setfillcolor(RGB(61, 68, 89));
	setlinecolor(RGB(61, 61, 61));
	setlinestyle(PS_SOLID | PS_JOIN_BEVEL, 1);

	roundrect(x1 + 1, y1 + 1, x2 - 1, y2 - 1, 11, 11);
	roundrect(x1 + 1, y1 + 1, x2 - 1, y2 - 1, 10, 10);

	roundrect(x1 + 1, y1 + 1, x2 - 1, y2 - 1, 9, 9);

	setlinestyle(PS_SOLID | PS_JOIN_BEVEL, 1);

	setlinecolor(RGB(85, 85, 85));
	fillroundrect(x1 + 3, y1 + 3, x2 - 3, y2 - 3, 11, 11);
	fillroundrect(x1 + 3, y1 + 3, x2 - 3, y2 - 3, 10, 10);
	setlinestyle(PS_SOLID | PS_JOIN_BEVEL, 1);
	setlinestyle(PS_SOLID | PS_JOIN_BEVEL, 2);
	line(x1 + 3, y1 + 19, x2 - 3, y1 + 19);
	setlinestyle(PS_SOLID | PS_JOIN_BEVEL, 1);
	settextzise(12);
	settextcolor(RGB(131, 143, 165));

	outtextxy(154, 88 + hite - 1, _T(" click to"));
	outtextxy(153, 98 + hite - 1, _T(" copy the"));
	outtextxy(152, 111 + hite - 1, _T("  colo"));

	setfillcolor(RGB(61, 68, 89));
	setlinecolor(RGB(85, 85, 85));

	if (GETIMAGE == false) {
		setlinecolor(RGB(61, 61, 61));

		setlinestyle(PS_SOLID | PS_JOIN_BEVEL, 1);
		roundrect(192, 87, 207, 98, 5, 3);
		roundrect(192, 87, 207, 98, 6, 4);
		setlinecolor(RGB(85, 85, 85));
		roundrect(192 + 1, 87 + 1, 207 - 1, 98 - 1, 4, 4);
		setlinecolor(RGB(85, 85, 85));

		setlinestyle(PS_SOLID | PS_JOIN_BEVEL, 1);

		setlinecolor(RGB(61, 61, 61));
		setlinestyle(PS_ENDCAP_SQUARE, 2);
		arc(194, 79, 205, 95, 0, 40.62);
		setlinecolor(RGB(85, 85, 85));
		arc(194 + 1, 79 + 2, 205 - 1, 95 - 2, 0, 40.5);
		setlinestyle(PS_ENDCAP_SQUARE, 1);
		setlinecolor(RGB(61, 61, 61));

		setlinestyle(PS_SOLID | PS_JOIN_BEVEL, 1);
		roundrect(192, 87, 207, 98, 5, 3);
		roundrect(192, 87, 207, 98, 6, 4);

		settextcolor(RGB(244, 82, 82));
		outtextxy(164, 73 + hite - 1, _T("Locked"));
	}
	if (GETIMAGE == true) {
		setlinecolor(RGB(61, 61, 61));
		setfillcolor(RGB(61, 68, 89));
		roundrect(192, 87, 207, 98, 5, 3);
		roundrect(192, 87, 207, 98, 6, 4);
		setlinecolor(RGB(85, 85, 85));
		roundrect(192 + 1, 87 + 1, 207 - 1, 98 - 1, 4, 4);

		setlinecolor(RGB(61, 61, 61));
		setlinestyle(PS_ENDCAP_SQUARE, 2);
		arc(197 - 10, 79, 197, 95, 0, 41.1);

		setlinecolor(RGB(85, 85, 85));
		arc(197 - 9, 79 + 1, 197 - 1, 95 - 2, 0, 41.1);
		setlinestyle(PS_ENDCAP_SQUARE, 1);

		settextcolor(RGB(183, 80, 80));
		outtextxy(158, 73 + hite - 1, _T("Unlocked"));
	}

}

void settextzise(int zise) {
	LOGFONT f;
	gettextstyle(&f);									// 获取当前字体设置。
	f.lfHeight = zise;									// 设置字体高度为 48。

	_tcscpy_s(f.lfFaceName, _T("宋体"));
	//f.lfQuality = ANTIALIASED_QUALITY;					// 设置输出效果为抗锯齿。

	settextstyle(&f);
	setbkmode(TRANSPARENT);								// 设置透明的背景。
}

void Conversion(struct textbox_xy* color_data1) {
	_tcscat_s(color_data1->R1, _T(","));
	_tcscat_s(color_data1->G1, _T(","));

	TCHAR RGB11[200] = { 0 };
	_tcscat_s(RGB11, color_data1->R1);
	_tcscat_s(RGB11, color_data1->G1);
	_tcscat_s(RGB11, color_data1->B1);

	_tcscpy_s(color_data1->A1[1], RGB11);

	_tcscat_s(color_data1->S1, _T(","));
	_tcscat_s(color_data1->H1, _T(","));
	_tcscat_s(color_data1->S1, color_data1->H1);
	_tcscat_s(color_data1->S1, color_data1->L1);

	_tcscat_s(color_data1->S2, _T(","));
	_tcscat_s(color_data1->H2, _T(","));
	_tcscat_s(color_data1->S2, color_data1->H2);
	_tcscat_s(color_data1->S2, color_data1->V2);
	_tcscpy_s(color_data1->A1[2], color_data1->S2);

	_tcscat_s(color_data1->CC, _T(","));
	_tcscat_s(color_data1->MM, _T(","));
	_tcscat_s(color_data1->YY, _T(","));
	_tcscat_s(color_data1->CC, color_data1->MM);
	_tcscat_s(color_data1->CC, color_data1->YY);
	_tcscat_s(color_data1->CC, color_data1->GETIMAGE);
	_tcscpy_s(color_data1->A1[5], color_data1->CC);

	_tcscat_s(color_data1->LL, _T(","));
	_tcscat_s(color_data1->AA, _T(","));
	_tcscat_s(color_data1->LL, color_data1->AA);
	_tcscat_s(color_data1->LL, color_data1->BB);
}

// 输出各种颜色值的函数
void putcolorvalue(struct textbox_xy* color_data1, int* r, int* g, int* b, int x1, int y1, int x2, int y2) {
	setlinecolor(RGB(61, 61, 61));
	setfillcolor(RGB(53, 53, 53));
	fillrectangle(x1 + 3, y1 + 3, x2 - 3, y2 - 3);
	Conversion(color_data1);
}

// 如果输入框没有被鼠标选中就返回 0。
/// @brief textboxparm 输入框传输参数函数
/// @param mouse_x	传入鼠标 x 坐标
/// @param mouse_y	传入鼠标 y 坐标
/// @param click		选择功能参数：1.启用鼠标点击功能 33.单纯的输入框功能
/// @param click_1		输入框点击特效参数: 1.启动 0.不启动
/// @return			可以通过 if 来返回其他参数来帮助程序退出
int textboxparm(int mouse_x, int mouse_y, struct textbox_xy* textbox_xy, int click, int click_1, bool GETIMAGE) {
	int a = 0;
	//	FlushBatchDraw();	// 批量绘图的开始处。
	for (int i = 0; i < 6; i++) {
		// 这个是打印读取了配置文件里的输入框数据数组，并通过 输入框功能函数 textbox_function 判断输入框点击后对应设置的功能。
		textbox1(textbox_xy->A1[i], textbox_xy->textbox_stringchar1[i][0], textbox_xy->textbox_int[i][0],
			textbox_xy->textbox_int[i][1], textbox_xy->textbox_int[i][2], textbox_xy->textbox_int[i][3], mouse_x, mouse_y,
			textbox_xy->textbox_int[i][4], click_1, GETIMAGE);
	}
	//EndBatchDraw();		// 批量绘图的结束处。
	return 0;
}
/// <summary>
/// </summary>
/// <param name="传入一个字符数组 STRING1"></param>
/// <param name="传入一个宽起始坐标 x1"></param>
/// <param name="传入一个高起始坐标 y1"></param>
/// <param name="传入一个宽结尾坐标 x2"></param>
/// <param name="传入一个高结尾坐标 y2"></param>
/// <param name="传入鼠标时实 X 坐标 mouse_x"></param>
/// <param name="传入鼠标时实 Y 坐标 mouse_y"></param>
/// <param name="传入一个字体大小的数值 textsize1"></param>
/// <param name="传入一个控制启用是否绘制输入框界面的数值 click_1"></param>
/// <returns></returns>
TCHAR* textbox1(TCHAR* STRING1, TCHAR* STRING0, int x1, int y1, int x2, int y2, int mouse_x, int mouse_y, int textsize1,

	int click_1, bool GETIMAGE) {
	if (STRING1 == NULL) {
		return NULL;
	};	// 判断传进来的指针数组是否为空。

	setlinecolor(DARKGRAY);					// 绘制低亮边框
	roundrect(x1, y1, x2, y2, 5, 5);
	int chenwidth = 1;						// 中英文输入框字符宽边变换变量

	settextzise(textsize1);				// 设置字体大小函数。
	TCHAR charwidth[4][55] = { {_T("奈")}, {'N'}, {'n'}, {'0'} };

	setlinecolor(DARKGRAY);
	roundrect(x1, y1, (textwidth(charwidth[0]) * 5) - 4, y2, 5, 5);
	line((textwidth(charwidth[0]) * 5) - 4, y1 + 2, (textwidth(charwidth[0]) * 5) - 4, y2 - 2);

	if (click_1 == 0) {
		if (mouse_x > x1 && mouse_y > y1 && mouse_x < x2 && mouse_y < y2) {
			setlinecolor(RGB(63, 62, 67));
			roundrect(x1, y1, (textwidth(charwidth[0]) * 5) - 4, y2, 5, 5);
			line((textwidth(charwidth[0]) * 5) - 4, y1 + 2, (textwidth(charwidth[0]) * 5) - 4, y2 - 2);
		}
		if (mouse_x > x1 && mouse_y > y1 && mouse_x < (textwidth(charwidth[0]) * 5) - 4 && mouse_y < y2) {
			setlinecolor(RGB(187, 148, 170));
			roundrect(x1, y1, (textwidth(charwidth[0]) * 5) - 4, y2, 5, 5);
			line((textwidth(charwidth[0]) * 5) - 4, y1 + 2, (textwidth(charwidth[0]) * 5) - 4, y2 - 2);
			//	fillroundrect(x1+50, y1, x2, y2, 5, 5);
		}
	}

	settextzise(15);
	settextcolor(RGB(132, 132, 132));
	outtextxy(((((textwidth(charwidth[0]) * 2) - x1) / 2) + x1) - (textwidth(STRING0[0]) / 2),
		(((y2 - y1) / 2) + y1) - (textheight(STRING0[0]) / 2), STRING0);
	float temp = textwidth(charwidth[0]) * (float)3.5;
	long temp1 = (long)temp;
	x1 = temp1;
	settextzise(textsize1);
	// 当鼠标点击了输入框就启动输入相关的

	if (click_1 == 0) {
		int cursor_xy = x1 + 5;
		int strlen1 = 0;

		setfillcolor(RGB(63, 62, 67));
		solidroundrect(x1, y1, x2, y2, 5, 5);
		setlinecolor(DARKGRAY);
		roundrect(x1, y1, x2, y2, 5, 5);
		if (click_1 == 0) {
			if (mouse_x > x1 && mouse_y > y1 && mouse_x < x2 && mouse_y < y2) {
				setlinecolor(RGB(93, 138, 154));
				roundrect(x1, y1, x2, y2, 5, 5);
			}
		}
		// 打印录入的数据
		if (strlen(STRING1) != 0) {
			if (strlen(STRING1) == 13) {

				settextzise(9);
			}
			else if (strlen(STRING1) == 14) {

				settextzise(9);
			}
			else if (strlen(STRING1) == 15) {

				settextzise(8);
			}

			for (size_t i = 0; i < strlen(STRING1); i++) {
				if (textwidth(charwidth[1]) == textwidth(STRING1[i]))
					chenwidth = 1;			// 英文
				else if (textwidth(charwidth[3]) == textwidth(STRING1[i]))
					chenwidth = 3;	// 数字
				else if (textwidth(charwidth[2]) == textwidth(STRING1[i]))
					chenwidth = 2;	// 小写
				else if (textwidth(charwidth[1]) == textwidth(STRING1[i]))
					chenwidth = 1;	// 大写
				else if (textwidth(STRING1[i]) == textwidth(charwidth[0]))
					chenwidth = 0;	// 中文

				if (STRING1[i] == 13) {
					setlinecolor(WHITE);
					line(cursor_xy, y1 + ((y2 - y1) - textheight(charwidth[chenwidth])) / 2, cursor_xy,
						y2 - ((y2 - y1) - textheight(charwidth[chenwidth])) / 2);
					break;
				}
				if (cursor_xy >= x2 - (textwidth(charwidth[chenwidth]) * 2))
					continue;
				settextcolor(RGB(175, 172, 191));
				outtextxy(cursor_xy, (((y2 - y1) / 2) + y1) - (textheight(charwidth[chenwidth]) / 2), STRING1[i]);
				cursor_xy = cursor_xy + textwidth(charwidth[chenwidth]) + 1;
			}
		}
	}
	if (x1 == 0 || x2 == 0 || y1 == 0 || y2 == 0) {
		x1 = 10;
		x2 = 10;
		y1 = 30;
		y2 = 40;
	}
	if (x1 != 0 && x2 != 0 && y1 != 0 && y2 != 0) {
		if ((x2 - x1) < 40)
			x2 = x2 + (40 - (x2 - x1));
		if ((y2 - y1) < 15)
			y2 = y2 + (15 - (y2 - y1));
	}
	if (textheight(charwidth[0]) > (y2 - y1)) {
		settextzise((y2 - y1) - 4);
		textsize1 = (y2 - y1) - 4;
	}

	if (click_1 == 1) {
		if (mouse_x > x1 && mouse_y > y1 && mouse_x < x2 && mouse_y < y2) {
			if (GETIMAGE == false)
				FlushBatchDraw();
			setlinecolor(RGB(187, 148, 170));
			roundrect(x1 + 2, y1 + 2, x2 - 2, y2 - 2, 5, 5);
			saveimage(_T("color.bmp"));
			SetDataToClip(STRING1);
			Sleep(200);
			//clearroundrect(x1 - 2, y1 - 2, x2 + 2, y2 + 2, 5, 5);
		}
	}
	// 返回 1 说明，鼠标点到了该输入框，可以通过 if 函数来判断返回值 1 要干什么。
	return NULL;
	//}
}

int button(int x1, int y1, int x2, int y2, int mouse_x, int mouse_y, int textsize1, int textsize2,
	LPCTSTR button_string1, LPCTSTR button_string2, int click_1) {
	settextzise(textsize1);																// 设置字体大小函数。
	setlinecolor(RGB(83, 99, 105));				// 设置按钮颜色的外框线体函数。
	settextcolor(RGB(207, 143, 143));																	// 设置按钮白色的字体函数。
	setfillcolor(RGB(83, 99, 105));				// 使用修改颜色的 RGB 数组，可改变数组从而来自由改变颜色。
	fillroundrect(x1, y1, x2, y2, 10,
		10);													// 画按钮矩形，有圆角 20，对接按钮的前四个坐标数组。																						// 设置居中显示按钮的文字。
	outtextxy((((x2 - x1) / 2) + x1) - (textwidth(button_string1) / 2),
		(((y2 - y1) / 2) + y1) - (textheight(button_string1) / 2), button_string1);
	// 特制按钮，字体居中算法，不知是否比自带的效率高？但失去了一些强大的功能。

	if (mouse_x > x1 && mouse_y > y1 && mouse_x < x2

		&& mouse_y < y2) {					// 判断鼠标是否在按钮内部，如果是就执行高亮按钮代码。
	//	setlinestyle(PS_ENDCAP_FLAT);
		setlinecolor(RGB(72, 105, 93));			// 选中按钮后把线条变颜色。
		settextcolor(RGB(255, 153, 164));																// 选中按钮后，把文字变成白色。
		setfillcolor(RGB(134, 152, 163));			// 使用修改颜色的 RGB 数组，可改变数组从而来自由改变颜色。
		setbkmode(TRANSPARENT);																// 把文字背景设置成透明的。
		fillroundrect(x1, y1, x2, y2, 10, 10);												// 填充的矩形，画选中的，按钮的意思。
		outtextxy((((x2 - x1) / 2) + x1) - (textwidth(button_string2) / 2),
			(((y2 - y1) / 2) + y1) - (textheight(button_string2) / 2), button_string2);
		// 特制按钮，字体居中算法：按钮长度减按钮起点除一半得没有起点的一半，再加上起点得按钮宽度中心点减字符串宽度的一半得居左右中字体
		if (click_1 == 1) {}																	// 如果点击等于 1 就启动点击按钮特效。
		return 1;																			// 返回 1 说明，鼠标点到了该按钮，可以通过 if 函数来判断返回值 1 要干什么。
	}
	return 0;																				// 如果按钮没有被鼠标选中就返回 0。
}

int button_x(int x111, int y111, int x222, int y222, int mouse_x, int mouse_y, int click_1) {
	int x = x111 + 11, y = y111 + 11, x11 = 5, y11 = 5;
	// 红表
	setlinecolor(RGB(36, 39, 50));
	setfillcolor(RGB(171, 69, 76));
	fillroundrect(x111, y111, x222, y222, 10, 10);
	fillroundrect(x111, y111, x222, y222, 8, 8);
	fillroundrect(x111, y111, x222, y222, 9, 9);
	setlinestyle(PS_SOLID | PS_JOIN_BEVEL, 3);
	setlinecolor(RGB(36, 39, 50));
	line(x, y, x - x11, y - y11);
	line(x, y, x + x11, y - y11);
	line(x, y, x + x11, y + y11);
	line(x, y, x - x11, y + y11);
	setlinestyle(PS_SOLID | PS_JOIN_BEVEL, 1);

	if (mouse_x > x111 && mouse_y > y111 && mouse_x < x222

		&& mouse_y < y222) {					// 判断鼠标是否在按钮内部，如果是就执行高亮按钮代码。
		setfillcolor(RGB(153, 80, 85));
		fillroundrect(x111, y111, x222, y222, 10, 10);
		fillroundrect(x111, y111, x222, y222, 8, 8);
		fillroundrect(x111, y111, x222, y222, 9, 9);

		setlinecolor(RGB(129, 42, 48));
		// 红底
		setlinestyle(PS_SOLID | PS_JOIN_BEVEL, 3);
		line(x, y, x - x11, y - y11);
		line(x, y, x + x11, y - y11);
		line(x, y, x + x11, y + y11);
		line(x, y, x - x11, y + y11);
		line(x - 1, y - 1, x - x11 - 1, y - y11 - 1);
		line(x + 1, y - 1, x + x11 + 1, y - y11 - 1);
		line(x + 1, y + 1, x + x11 + 1, y + y11 + 1);
		line(x - 1, y + 1, x - x11 - 1, y + y11 + 1);
		setlinestyle(PS_SOLID | PS_JOIN_BEVEL, 1);
		if (click_1 == 1) {																// 如果点击等于 1 就启动点击按钮特效。
			return 1;
		}
		// 返回 1 说明，鼠标点到了该按钮，可以通过 if 函数来判断返回值 1 要干什么。
	}
	// 如果按钮没有被鼠标选中就返回 0。
	return 0;
}
int button_i(int x111, int y111, int x222, int y222, int mouse_x, int mouse_y, int click_1) {
	int x = 200, y = 15, x11 = 5, y11 = 5;
	setlinecolor(RGB(36, 39, 50));
	setfillcolor(RGB(80, 138, 80));
	fillroundrect(x111, y111, x222, y222, 10, 10);
	fillroundrect(x111, y111, x222, y222, 8, 8);
	fillroundrect(x111, y111, x222, y222, 9, 9);
	setfillcolor(RGB(71, 111, 71));
	setlinecolor(RGB(71, 111, 71));
	solidrectangle((x111 + ((x222 - x111) / 2)) - 1, y111 + 2 + 1, (x111 + ((x222 - x111) / 2)) + 1, y111 + 2 + 4);

	solidrectangle((x111 + ((x222 - x111) / 2)) - 1, y111 + 2 + 4 + 2, (x111 + ((x222 - x111) / 2)) + 1,
		y111 + 2 + 4 + 2 + 10);

	if (mouse_x > x111 && mouse_y > y111 && mouse_x < x222

		&& mouse_y < y222) {					// 判断鼠标是否在按钮内部，如果是就执行高亮按钮代码。
		setlinecolor(RGB(36, 39, 50));
		setfillcolor(RGB(70, 110, 70));
		fillroundrect(x111, y111, x222, y222, 10, 10);
		fillroundrect(x111, y111, x222, y222, 8, 8);
		fillroundrect(x111, y111, x222, y222, 9, 9);
		setfillcolor(RGB(48, 75, 48));
		setlinecolor(RGB(48, 75, 48));
		solidrectangle((x111 + ((x222 - x111) / 2)) - 1, y111 + 2 + 1, (x111 + ((x222 - x111) / 2)) + 1, y111 + 2 + 4);
		solidrectangle((x111 + ((x222 - x111) / 2)) - 1, y111 + 2 + 4 + 2, (x111 + ((x222 - x111) / 2)) + 1,
			y111 + 2 + 4 + 2 + 10);

		if (click_1 == 1) {																// 如果点击等于 1 就启动点击按钮特效。
			//	ShellExecuteW(NULL, _T("open"), _T("IEXPLORE"), _T("https://docs.easyx.cn/"), NULL, SW_SHOWMAXIMIZED);
			return 1;
		}
		// 返回 1 说明，鼠标点到了该按钮，可以通过 if 函数来判断返回值 1 要干什么。
	}
	// 如果按钮没有被鼠标选中就返回 0。
	return 0;
}

int button_mini(int x111, int y111, int x222, int y222, int mouse_x, int mouse_y, HWND h1, int click_1) {
	// 红表
	setlinecolor(RGB(36, 39, 50));
	setfillcolor(RGB(82, 104, 141));
	fillroundrect(x111, y111, x222, y222, 10, 10);
	fillroundrect(x111, y111, x222, y222, 8, 8);
	fillroundrect(x111, y111, x222, y222, 9, 9);
	setlinecolor(RGB(68, 73, 90));
	line(x111 + 3, y222 - 4, x222 - 3, y222 - 4);
	line(x111 + 3, y222 - 5, x222 - 3, y222 - 5);
	line(x111 + 3, y222 - 6, x222 - 3, y222 - 6);

	if (mouse_x > x111 && mouse_y > y111 && mouse_x < x222

		&& mouse_y < y222) {					// 判断鼠标是否在按钮内部，如果是就执行高亮按钮代码。
		setlinecolor(RGB(36, 39, 50));
		setfillcolor(RGB(71, 91, 123));
		fillroundrect(x111, y111, x222, y222, 10, 10);
		fillroundrect(x111, y111, x222, y222, 8, 8);
		fillroundrect(x111, y111, x222, y222, 9, 9);
		setlinecolor(RGB(51, 55, 69));
		// 红底

		line(x111 + 3, y222 - 4, x222 - 3, y222 - 4);
		line(x111 + 3, y222 - 5, x222 - 3, y222 - 5);
		line(x111 + 3, y222 - 6, x222 - 3, y222 - 6);

		if (click_1 == 1) {																// 如果点击等于 1 就启动点击按钮特效。
			ShowWindow(h1, SW_SHOWMINIMIZED);
			return 1;
		}
		// 返回 1 说明，鼠标点到了该按钮，可以通过 if 函数来判断返回值 1 要干什么。
	}
	// 如果按钮没有被鼠标选中就返回 0。
	return 0;
}

int button_add(int x111, int y111, int mouse_x, int mouse_y, int click_1) {
	// 红表
	setlinecolor(RGB(102, 108, 143));
	setfillcolor(RGB(102, 108, 143));
	fillcircle(x111, y111, 9);

	setlinestyle(PS_ENDCAP_SQUARE, 2); // 设置 2 的粗
	setlinecolor(RGB(36, 39, 50));
	/* 以圆中心 x y 轴 向东南西北分别绘制并组成十字 */
	line(x111, y111, x111 - 7, y111);
	line(x111, y111, x111, y111 - 7);
	line(x111, y111, x111 + 7, y111);
	line(x111, y111, x111, y111 + 7);

	setlinestyle(PS_SOLID | PS_JOIN_BEVEL, 1); // 返原 1 的粗

	if (mouse_x > x111 - 9 && mouse_y > y111 - 9 && mouse_x < x111 + 9

		&& mouse_y < y111 + 9) {					// 判断鼠标是否在按钮内部，如果是就执行高亮按钮代码。
		setfillcolor(RGB(73, 76, 101));
		setlinecolor(RGB(73, 76, 101));

		fillcircle(x111, y111, 9);

		setlinecolor(RGB(52, 54, 72));
		// 红底
		setlinestyle(PS_ENDCAP_SQUARE, 2);
		line(x111, y111, x111 - 5, y111);
		line(x111, y111, x111, y111 - 5);
		line(x111, y111, x111 + 5, y111);
		line(x111, y111, x111, y111 + 5);

		setlinestyle(PS_SOLID | PS_JOIN_BEVEL, 1);

		if (click_1 == 1) {																// 如果点击等于 1 就启动点击按钮特效。
			return 1;
		}
		// 返回 1 说明，鼠标点到了该按钮，可以通过 if 函数来判断返回值 1 要干什么。
	}
	// 如果按钮没有被鼠标选中就返回 0。
	return 0;
}

int button_addminus(int x111, int y111, int mouse_x, int mouse_y, int click_1) {
	// 红表
	setlinecolor(RGB(102, 108, 143));
	setfillcolor(RGB(102, 108, 143));
	fillcircle(x111, y111, 9);
	setlinestyle(PS_ENDCAP_SQUARE, 2);
	setlinecolor(RGB(36, 39, 50));
	line(x111, y111, x111 - 7, y111);
	line(x111, y111, x111 + 7, y111);

	setlinestyle(PS_SOLID | PS_JOIN_BEVEL, 1);

	if (mouse_x > x111 - 9 && mouse_y > y111 - 9 && mouse_x < x111 + 9

		&& mouse_y < y111 + 9) {					// 判断鼠标是否在按钮内部，如果是就执行高亮按钮代码。
		setfillcolor(RGB(73, 76, 101));
		setlinecolor(RGB(73, 76, 101));
		fillcircle(x111, y111, 9);

		setlinecolor(RGB(52, 54, 72));
		// 红底
		setlinestyle(PS_ENDCAP_SQUARE, 2);
		line(x111, y111, x111 - 5, y111);
		line(x111, y111, x111 + 5, y111);
		setlinestyle(PS_SOLID | PS_JOIN_BEVEL, 1);
		if (click_1 == 1) {																// 如果点击等于 1 就启动点击按钮特效。
			return 1;
		}
		// 返回 1 说明，鼠标点到了该按钮，可以通过 if 函数来判断返回值 1 要干什么。
	}
	// 如果按钮没有被鼠标选中就返回 0。
	return 0;
}

int button_triangle(struct textbox_xy* color_data1, int x111, int y111, int mouse_x, int mouse_y, int click_1) {

	int pts1[7] = { x111 - 5, y111 + 4, x111, y111 - 6,  x111 + 5, y111 + 4 };
	int pts[7] = { x111 - 5, y111 - 4, x111, y111 + 6,  x111 + 5, y111 - 4 };

	setlinecolor(RGB(102, 108, 143));
	setpolyfillmode(WINDING);
	setfillcolor(RGB(102, 108, 143));

	fillcircle(x111, y111, 9);

	setlinestyle(PS_ENDCAP_SQUARE, 2);
	setlinecolor(RGB(36, 39, 50));
	setpolyfillmode(WINDING);

	setfillcolor(RGB(36, 39, 50));

	if ((color_data1->f2 % 2) == 0) {
		solidpolygon((POINT*)pts, 3);
	}
	else if ((color_data1->f2 % 2) != 0) {
		solidpolygon((POINT*)pts1, 3);
	}
	setlinestyle(PS_SOLID | PS_JOIN_BEVEL, 1);

	if (mouse_x > x111 - 9 && mouse_y > y111 - 9 && mouse_x < x111 + 9
		&& mouse_y < y111 + 9) {					// 判断鼠标是否在按钮内部，如果是就执行高亮按钮代码。
		setfillcolor(RGB(73, 76, 101));
		setlinecolor(RGB(73, 76, 101));
		fillcircle(x111, y111, 9);

		setlinecolor(RGB(52, 54, 72));
		// 红底
		setlinestyle(PS_ENDCAP_SQUARE, 2);
		setpolyfillmode(WINDING);
		setfillcolor(RGB(52, 54, 72));

		if ((color_data1->f2 % 2) == 0) {
			solidpolygon((POINT*)pts, 3);
		}
		else if ((color_data1->f2 % 2) != 0) {
			solidpolygon((POINT*)pts1, 3);
		}
		setlinestyle(PS_SOLID | PS_JOIN_BEVEL, 1);

		if (click_1 == 2) {																// 如果点击等于 1 就启动点击按钮特效。
			setfillcolor(RGB(73, 76, 101));
			setlinecolor(RGB(73, 76, 101));
			fillcircle(x111, y111, 9);

			setlinecolor(RGB(52, 54, 72));
			// 红底
			setlinestyle(PS_ENDCAP_SQUARE, 2);
			setpolyfillmode(WINDING);
			setfillcolor(RGB(52, 54, 72));

			if ((color_data1->f2 % 2) == 0) {
				solidpolygon((POINT*)pts, 3);
				color_data1->f2++;
			}
			else if ((color_data1->f2 % 2) != 0) {
				solidpolygon((POINT*)pts1, 3);
				color_data1->f2++;
			}
			setlinestyle(PS_SOLID | PS_JOIN_BEVEL, 1);
			return 1;
		}
		// 返回 1 说明，鼠标点到了该按钮，可以通过 if 函数来判断返回值 1 要干什么。
	}
	// 如果按钮没有被鼠标选中就返回 0。
	return 0;
}

void inigra(int i) {
	int x = 200, y = 15, d = 2, x11 = 5, y11 = 5;
	int x1 = 0, y1 = 0, x2 = 228, y2 = 30;
	settextzise(16);
	/*			绘制标题标			*/
	if (i == 0) {
		setfillcolor(RGB(53, 58, 71));
		solidrectangle(0, 0, 228, 30);
	}
	if (i == 1) {
		setfillcolor(RGB(61, 68, 89));
		solidrectangle(0, 0, 228, 30);
	}
	setlinecolor(RGB(36, 39, 50));
	line(x1, y2, x2, y2);
	line(x1, y2 + 1, x2, y2 + 1);
	line(x1, y2 + 2, x2, y2 + 2);
	settextcolor(RGB(145, 109, 140));
	outtextxy(10, 10, _T("ColorPicker 1.0"));
	setfillcolor(RGB(197, 85, 89));

	button_x(189, 4, 211, 26, 0, 0, 1);
	button_i(165, 4, 187, 26, 0, 0, 1);
	button_mini(141, 4, 163, 26, 0, 0, NULL, 2);
}


void lnitial_drawing1(int a) {
	HWND hWnd = GetHWnd();

	SetWindowLong
	(
		hWnd,
		GWL_STYLE,
		GetWindowLong(hWnd, GWL_STYLE)
		& ~
		(WS_CAPTION | WS_DLGFRAME | WS_BORDER)
	);

	SetWindowLong(hWnd, GWL_EXSTYLE,
		GetWindowLong(hWnd, GWL_EXSTYLE) &
		~(WS_EX_WINDOWEDGE | WS_EX_CLIENTEDGE | WS_EX_DLGMODALFRAME));

	SetWindowPos(hWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_FRAMECHANGED);

	HRGN rgn = CreateRoundRectRgn(0, 0, white, hwite - 3 - a, 15, 15);
	SetWindowRgn(hWnd, rgn, true);
	inigra(1);
}

// 主函数
int main() {
	lnitial_drawing();
	lnitial_drawing1(0);
	lnitial_drawing1(0);
	inigra(1);

	HWND h1;
	h1 = GetHWnd();

	struct textbox_xy color_data;
	struct textbox_xy* color_data1 = &color_data;

	int x = 200, y = 15, d = 2, x11 = 5, y11 = 5;
	int w = 106;
	int h = 55;
	int inigra_variable0 = 1;
	int inigra_variable01 = 2;
	int button_zoom_variable0 = 5, button_zoom_variable1 = 5;

	TCHAR ZOOM[200] = { 0 };
	BOOL TURE1 = true;
	BOOL TURE2 = true;
	BOOL GETIMAGE = true;

	// 主体循环函数的中断条件
	IMAGE img1;
	IMAGE img2;
	IMAGE img3;
	IMAGE img4;

	Resize(&img1, w, h);
	Resize(&img2, w, h);
	Resize(&img3, w, h);
	Resize(&img4, w, h);

	textboxparm(NULL, NULL, color_data1, 33, 3, NULL);

	ExMessage m;

	BeginBatchDraw();
	while (TURE2 && TURE1) {

		int r = 0, g = 0, b = 0;
		POINT pt11;
		GetCursorPos(&pt11);
		ScreenToClient(h1, &pt11);


		if (GETIMAGE) {
			cleardevice();
			CaptureImagb(color_data1, &r, &g, &b, &img1, &img2, &img3, &img4, 0, 167, 215, 267 + hite + 5 - xX, w, h, true);
			RGBfillrec(r, g, b, 150, hite + 1, 212, 80 + hite - 15);
			putcolorvalue(color_data1, 0, 0, 0, 3, hite, 149, 126 + hite - 1);
			setlinecolor(RGB(53, 53, 53));
		}
		else {
			CaptureImagb(color_data1, &r, &g, &b, &img1, &img2, &img3, &img4, 0, 167, 215, 267 + hite + 5 - xX, w, h, false);
		}

		if (peekmessage(&m, EM_KEY | EM_CHAR | EM_WINDOW, true)) {
			if (m.message == WM_ACTIVATE) {
				if ((inigra_variable01 % 2) == 0) {
					inigra_variable0 = 1;
					++inigra_variable01;

					flushmessage(-1);
				}
				else if ((inigra_variable01 % 2) != 0) {

					inigra_variable0 = 0;
					++inigra_variable01;
					flushmessage(-1);
				}
			}
			else if (m.message == WM_KEYDOWN) {
				if (m.vkcode == VK_ESCAPE) {

					if (MessageBox(h1, _T("是否退出软件颜色诱捕器？\n"), _T("颜色诱捕器-询问"), MB_YESNO | MB_ICONQUESTION) == IDYES) {
						flushmessage(-1);
						TURE2 = false;
						TURE1 = false;
					}
					else {
						flushmessage(-1);
						continue;
					}
				}

			}

			if (peekmessage(&m, EM_KEY | EM_CHAR, true)) {
				if ((f % 2) == 0) {
					++f;
					GETIMAGE = false;
					flushmessage(-1);
				}
				else if ((f % 2) != 0) {
					GETIMAGE = true;
					++f;
					flushmessage(-1);
				}

			}
			flushmessage(-1);
		}

		{
			inigra(inigra_variable0);
			sprintf(ZOOM, _T("ZOOM:%d"), button_zoom_variable1 * 10);
			text_color(150, 81 + hite - 15, 212, 126 + hite - 1, GETIMAGE);
			button(90, 168, 143, 187, pt11.x, pt11.y, 12, 13, ZOOM, ZOOM, 0);
			button_x(189, 4, 211, 26, pt11.x, pt11.y, 1);
			button_i(165, 4, 187, 26, pt11.x, pt11.y, 2);
			button_mini(141, 4, 163, 26, pt11.x, pt11.y, h1, 2);
			button_triangle(color_data1, 200, 178, pt11.x, pt11.y, 1);
			button_add(178, 178, pt11.x, pt11.y, 1);
			button_addminus(156, 178, pt11.x, pt11.y, 1);
		}
		// 鼠标移动输入框中的高亮边框绘制与鼠标离开输入框的恢复低亮边框。
		textboxparm(pt11.x, pt11.y, color_data1, 33, 0, GETIMAGE);

		while ((GetAsyncKeyState(VK_LBUTTON)) && TURE1) {

			button_i(165, 4, 187, 26, pt11.x, pt11.y, 1);
			button_mini(141, 4, 163, 26, pt11.x, pt11.y, h1, 1);
			button(90, 168, 143, 187, pt11.x, pt11.y, 12, 13, ZOOM, ZOOM, 0);

			if (button_x(189, 4, 211, 26, pt11.x, pt11.y, 1) == 1) {
				TURE2 = false;
				TURE1 = false;
			};

			if (button_add(178, 178, pt11.x, pt11.y, 1) == 1) {
				if (button_zoom_variable0 == 0 || button_zoom_variable1 == 0) {
					break;
				}
				if (color_data1->xxd != 0 || color_data1->yyd != 0) {
					if (color_data1->xxd > 0 || color_data1->yyd > 0) {
						button_zoom_variable0 -= 1;
						button_zoom_variable1 -= 1;
						color_data1->xxd = color_data1->addg[button_zoom_variable0][0];
						color_data1->yyd = color_data1->addg[button_zoom_variable0][1];
					}
					Sleep(40);
					break;
				}
			}

			if (button_addminus(156, 178, pt11.x, pt11.y, 1) == 1) {
				if (button_zoom_variable0 == 6 || button_zoom_variable1 == 6) {
					break;
				}
				if (abs(color_data1->xxd) != 0 || abs(color_data1->yyd) != 0) {
					button_zoom_variable0 += 1;
					button_zoom_variable1 += 1;
					color_data1->xxd = color_data1->addg[button_zoom_variable0][0];
					color_data1->yyd = color_data1->addg[button_zoom_variable0][1];
					Sleep(40);
					break;
				}
			}

			if (button_triangle(color_data1, 200, 178, pt11.x, pt11.y, 2) == 1) {
				if ((f1 % 2) == 0) {
					text_color(150, 81 + hite - 15, 212, 126 + hite - 1, GETIMAGE);
					button(90, 168, 143, 187, pt11.x, pt11.y, 12, 13, ZOOM, ZOOM, 1);
					lnitial_drawing1(114);
					Resize(NULL, white, hwite - 120);

					f1++;
					Sleep(100);
				}
				else if ((f1 % 2) != 0) {
					text_color(150, 81 + hite - 15, 212, 126 + hite - 1, GETIMAGE);
					button(90, 168, 143, 187, pt11.x, pt11.y, 12, 13, ZOOM, ZOOM, 1);
					lnitial_drawing1(0);
					Resize(NULL, white, hwite);

					f1++;
					Sleep(100);
				}
			}
			textboxparm(pt11.x, pt11.y, color_data1, 33, 1, GETIMAGE);
			if ((pt11.x > 0 && pt11.y > 0 && pt11.x < 140 && pt11.y < color_data1->Y2)) {
				while ((GetAsyncKeyState(VK_LBUTTON))) {
					inigra(1);

					POINT pt2;
					GetCursorPos(&pt2);
					MoveWindow(h1, pt2.x - pt11.x, pt2.y - pt11.y, 245, 340, true);
					//PostMessage(h1, WM_NCLBUTTONDOWN, HTCAPTION, MAKELPARAM(pt2.x, pt2.y));
				}
			}
		}
		saveimage(_T("color_miage.bmp"));
		FlushBatchDraw();
	}
	EndBatchDraw();
	closegraph();
	return 0;
}
