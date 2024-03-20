#define  _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <Windows.h> // GUI ���� ���
#include <math.h>

/////////////////////
// ���� ������
/////////////////////
HWND hwnd; // ���� ȭ��(�ܺ�, ������)
HDC hdc; // ���� ȭ�� (����, ����)

FILE* rfp, * wfp;
char fileName[200];
int inH, inW, outH, outW;
// �޸� Ȯ��
unsigned char** inImage = NULL, ** outImage = NULL;

/////////////////////
// �Լ� �����
/////////////////////
void loadImage(); int getIntValue(); void printImage();
void printMenu(); void printMenu1(); void printMenu2(); void printMenu3(); void printMenu4(); void menu1(); void menu2(); void menu3(); void menu4();
int getStartValue(); int getEndValue(); double getGamma();
void saveImage(); void freeInputMemory(); void freeOutputMemory();
void mallocInputMemory(); void mallocOutputMemory();
double** mallocDoubleMemory(int, int); void freeDoubleMemory(double**, int);

void equalImage(); void addImage(); void subImage(); void reverseImage(); void bwImage();
void gamImage(); void CAPparaImage(); void CUPparaImage(); void avgbwImage(); void midbwImage();
void stretchImage();  void posterImage(); void stressImage();

void zoutImage();; void zinImage(); void zinImage2(); void rotImage(); void rotImage2(); void moveImage(); void mirrorLR(); void mirrorUD(); void mirrorALL();
void histoStretch(); void endIn(); void histoEqual(); void emboss(); void blur(); void sharpning(); void hpfSharp(); void lpfSharp(); void smoothing();
void edge1(); void edge2(); void edge3(); void Rrow(); void Rcol(); void Srow(); void Scol(); void Prow(); void Pcol(); void lap1(); void lap2(); void lap3();

void main() {
	hwnd = GetForegroundWindow();
	hdc = GetWindowDC(NULL);  // Windows 10 : hwnd

	char inKey = 0;
	while (inKey != '9') {
		printMenu();
		inKey = _getch();

		if (inKey == '0') {
			loadImage();
		}
		else if (inKey == '1') {
			menu1();
		}
		else if (inKey == '2') {
			menu2();
		}
		else if (inKey == '3') {
			menu3();
		}
		else if (inKey == '4') {
			menu4();
		}
		else if (inKey == '7') {
			printMenu();
		}
		else if (inKey == '8') {
			saveImage();
		}
		else if (inKey == '9') {
			break;
		}
	}
	freeInputMemory();
	freeOutputMemory();
}

/////////////////////
// �Լ� ���Ǻ�
/////////////////////
/// ���� �Լ�
//////////////
void printMenu() {
	puts("\n ## GrayScale Image Processing (Beta 4) ##");
	puts("0.���� 8.���� 9.����");
	puts("1.ȭ���� ó�� 2.������ ó�� 3.������׷� ó�� 4.��輱 ����");
}

void printMenu1() {
	puts("\n ## GrayScale Image Processing (Beta 4) ##");
	puts("8.���� 9.�ڷ� ����");
	puts("1.ȭ���� ó��");
	puts("A.���� B.��� C.��Ӱ� D.���� E.��� F.���� G.CAP�Ķ󺼶� H.CUP�Ķ󺼶� I.���(��հ�) J.���(�߾Ӱ�) K.��ϴ��Ʈ��Ī L.�����Ͷ���¡ M.��������");
}

void printMenu2() {
	puts("\n ## GrayScale Image Processing (Beta 4) ##");
	puts("8.���� 9.�ڷ� ����");
	puts("2.������ ó��");
	puts("A.��� B.Ȯ��(������) C.Ȯ��(�����) D.ȸ��(�⺻) E.ȸ��(�߾�, �����) F.�̹��� �̵� G.�¿���� H.���Ϲ��� I.�����¿����");
}

void printMenu3() {
	puts("\n ## GrayScale Image Processing (Beta 4) ##");
	puts("8.���� 9.�ڷ� ����");
	puts("3.������׷� ó��");
	puts("A.������׷� ��Ʈ��Ī B.����-�� C.��Ȱȭ D.������ E.�� F.������ G.���������� ������ H.���������� ������ I.����þ� ������");
}

void printMenu4() {
	puts("\n ## GrayScale Image Processing (Beta 4) ##");
	puts("8.���� 9.�ڷ� ����");
	puts("4.��輱 ����");
	puts("A.��輱1(��������) B.��輱2(�������) C.��輱3(���翬����) D.�ι���(�� ����) E.�ι���(�� ����) F.�Һ�(�� ����) G.�Һ�(�� ����) H.������(�� ����) I.������(�� ����) J.���ö�þ�(1) K.���ö�þ�(2) L.���ö�þ�(3)");
}

void menu1() {
	char inKey = 0;
	printMenu1();
	while (inKey != '9') {
		inKey = _getch();

		switch (inKey) {
		case 'a': case 'A': equalImage(); printMenu1(); break;
		case 'b': case 'B': addImage(); printMenu1(); break;
		case 'c': case 'C': subImage(); printMenu1(); break;
		case 'd': case 'D': reverseImage(); printMenu1(); break;
		case 'e': case 'E': bwImage(); printMenu1(); break;
		case 'f': case 'F': gamImage(); printMenu1(); break;
		case 'g': case 'G': CAPparaImage(); printMenu1(); break;
		case 'h': case 'H': CUPparaImage(); printMenu1(); break;
		case 'i': case 'I': avgbwImage(); printMenu1(); break;
		case 'j': case 'J': midbwImage(); printMenu1(); break;
		case 'k': case 'K': stretchImage(); printMenu1(); break;
		case 'l': case 'L': posterImage(); printMenu1(); break;
		case 'm': case 'M': stressImage(); printMenu1();  break;
		case '8': saveImage(); printMenu1(); break;
		case '9': break;
		}
	}
}

void menu2() {
	char inKey = 0;
	printMenu2();
	while (inKey != '9') {
		inKey = _getch();

		switch (inKey) {
		case 'a': case 'A': zoutImage(); printMenu2(); break;
		case 'b': case 'B': zinImage(); printMenu2(); break;
		case 'c': case 'C': zinImage2(); printMenu2(); break;
		case 'd': case 'D': rotImage(); printMenu2(); break;
		case 'e': case 'E': rotImage2(); printMenu2(); break;
		case 'f': case 'F': moveImage(); printMenu2(); break;
		case 'g': case 'G': mirrorLR(); printMenu2(); break;
		case 'h': case 'H': mirrorUD(); printMenu2(); break;
		case 'i': case 'I': mirrorALL(); printMenu2(); break;
		case '8': saveImage(); printMenu2(); break;
		case '9': break;
		}
	}
}

void menu3() {
	char inKey = 0;
	printMenu3();
	while (inKey != '9') {
		inKey = _getch();

		switch (inKey) {
		case 'a': case 'A': histoStretch(); printMenu3(); break;
		case 'b': case 'B': endIn(); printMenu3(); break;
		case 'c': case 'C': histoEqual(); printMenu3(); break;
		case 'd': case 'D': emboss(); printMenu3(); break;
		case 'e': case 'E': blur(); printMenu3(); break;
		case 'f': case 'F': sharpning(); printMenu3(); break;
		case 'g': case 'G': hpfSharp(); printMenu3(); break;
		case 'h': case 'H': lpfSharp(); printMenu3(); break;
		case 'i': case 'I': smoothing(); printMenu3(); break;
		case '8': saveImage(); printMenu3(); break;
		case '9': break;
		}
	}
}

void menu4() {
	char inKey = 0;
	printMenu4();
	while (inKey != '9') {
		inKey = _getch();

		switch (inKey) {
		case 'a': case 'A': edge1(); printMenu4(); break;
		case 'b': case 'B': edge2(); printMenu4(); break;
		case 'c': case 'C': edge3(); printMenu4(); break;
		case 'd': case 'D': Rrow(); printMenu4(); break;
		case 'e': case 'E': Rcol(); printMenu4(); break;
		case 'f': case 'F': Srow(); printMenu4(); break;
		case 'g': case 'G': Scol(); printMenu4(); break;
		case 'h': case 'H': Prow(); printMenu4(); break;
		case 'i': case 'I': Pcol(); printMenu4(); break;
		case 'j': case 'J': lap1(); printMenu4(); break;
		case 'k': case 'K': lap2(); printMenu4(); break;
		case 'l': case 'L': lap3(); printMenu4(); break;
		case '8': saveImage(); printMenu4(); break;
		case '9': break;
		}
	}
}

void printImage() {
	system("cls");
	for (int i = 0; i < outH; i++) {
		for (int k = 0; k < outW; k++) {
			int px = outImage[i][k];
			SetPixel(hdc, k + 50, i + 250, RGB(px, px, px));
		}
	}
}

void loadImage() {
	char fullName[200] = "D:/my_RAW/";
	char tmpName[50];
	printf("���ϸ�-->"); // flower512, LENA256
	scanf("%s", tmpName);
	strcat(fullName, tmpName);
	strcat(fullName, ".raw");
	strcpy(fileName, fullName);

	// (�߿�!) �̹����� ���� ���̸� ����
	rfp = fopen(fileName, "rb");
	if (rfp == NULL) {
		printf("���ϸ��� Ȯ�����ּ���.");
		return 1;
	}
	fseek(rfp, 0L, SEEK_END); // ������ ������ �̵�
	long long fsize = ftell(rfp); // �� ���������?  262,144  --> 512
	fclose(rfp);
	// �޸� ����
	freeInputMemory();
	// �Է¿��� ����, �� ���ϱ�
	inH = inW = (int)sqrt(fsize);
	// �޸� �Ҵ�
	mallocInputMemory();

	// ���� --> �޸�
	rfp = fopen(fileName, "rb");
	for (int i = 0; i < inH; i++)
		fread(inImage[i], sizeof(unsigned char), inW, rfp);
	fclose(rfp);

	equalImage();
}

void saveImage() {
	if (outImage == NULL)
		return;
	char fullName[200] = "D:/RAW/Etc_Raw(squre)/";
	char tmpName[50];
	printf("���ϸ�-->"); // out01, out02......
	scanf("%s", tmpName);
	strcat(fullName, tmpName);
	strcat(fullName, ".raw");
	strcpy(fileName, fullName);

	wfp = fopen(fileName, "wb");
	// �޸� --> ���� (���྿)
	for (int i = 0; i < outH; i++)
		fwrite(outImage[i], sizeof(unsigned char), outW, wfp);
	fclose(wfp);
	// MessageBox(hwnd, L"���� �Ϸ�", L"���� â", NULL);
	printf("���� �Ϸ�");
}

int getIntValue() {
	int retValue;
	printf("������-->"); scanf("%d", &retValue);
	return retValue;
}

double getGamma() {
	double gamma;
	printf("���� �� --> "); scanf("%lf", &gamma);
	return gamma;
}

int getStartValue() {
	int start;
	printf("���� ��-->"); scanf("%d", &start);
	return start;
}

int getEndValue() {
	int end;
	printf("�� ��-->"); scanf("%d", &end);
	return end;
}

int getxValue() {
	int x;
	printf("x ��-->"); scanf("%d", &x);
	return x;
}

int getyValue() {
	int y;
	printf("y ��-->"); scanf("%d", &y);
	return y;
}

int compare(const int* a, const int* b) {
	return(*a - *b);
}

void freeInputMemory() {
	if (inImage == NULL)
		return;
	for (int i = 0; i < inH; i++)
		free(inImage[i]);
	free(inImage);
	inImage = NULL;
}
void mallocInputMemory() {
	inImage = (unsigned char**)malloc(sizeof(unsigned char*) * inH);
	for (int i = 0; i < inH; i++)
		inImage[i] = (unsigned char*)malloc(sizeof(unsigned char) * inW);
}

void freeOutputMemory() {
	if (outImage == NULL)
		return;
	for (int i = 0; i < outH; i++)
		free(outImage[i]);
	free(outImage);
	outImage = NULL;
}

void mallocOutputMemory() {
	outImage = (unsigned char**)malloc(sizeof(unsigned char*) * outH);
	for (int i = 0; i < outH; i++)
		outImage[i] = (unsigned char*)malloc(sizeof(unsigned char) * outW);
}

double** mallocDoubleMemory(int h, int w) {
	double** retMemory;
	retMemory = (double**)malloc(sizeof(double*) * h);
	for (int i = 0; i < h; i++)
		retMemory[i] = (double*)malloc(sizeof(double) * w);
	return retMemory;
}

void freeDoubleMemory(double** memory, int h) {
	if (memory == NULL)
		return;
	for (int i = 0; i < h; i++)
		free(memory[i]);
	free(memory);
	memory = NULL;
}

//////////////////
//  ����ó�� �Լ�
////////////////////
void equalImage() { // ���Ͽ��� �˰���
	// �޸� ����
	freeOutputMemory();
	// (�߿�!) ��� �̹����� ũ�⸦ ���� ---> �˰��� ����
	outH = inH;
	outW = inW;
	// �޸� �Ҵ�	
	mallocOutputMemory();
	// �Է� �迭 --> ��� �迭
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			outImage[i][k] = inImage[i][k];
		}
	}
	printImage();
}

void addImage() { // ���ϱ� �˰���
	// �޸� ����
	freeOutputMemory();
	// (�߿�!) ��� �̹����� ũ�⸦ ���� ---> �˰��� ����
	outH = inH;
	outW = inW;
	// �޸� �Ҵ�	
	mallocOutputMemory();

	// �Է� �迭 --> ��� �迭
	int val = getIntValue();
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			if (inImage[i][k] + val < 255)
				outImage[i][k] = inImage[i][k] + val;
			else
				outImage[i][k] = 255;
		}
	}
	printImage();
}

void subImage() { // ���� �˰���
	// �޸� ����
	freeOutputMemory();
	// (�߿�!) ��� �̹����� ũ�⸦ ���� ---> �˰��� ����
	outH = inH;
	outW = inW;
	// �޸� �Ҵ�	
	mallocOutputMemory();

	// �Է� �迭 --> ��� �迭
	int val = getIntValue();
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			if (inImage[i][k] - val > 0)
				outImage[i][k] = inImage[i][k] - val;
			else
				outImage[i][k] = 0;
		}
	}
	printImage();
}

void reverseImage() { // ���� �˰���
	// �޸� ����
	freeOutputMemory();
	// (�߿�!) ��� �̹����� ũ�⸦ ���� ---> �˰��� ����
	outH = inH;
	outW = inW;
	// �޸� �Ҵ�	
	mallocOutputMemory();

	// �Է� �迭 --> ��� �迭
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			outImage[i][k] = 255 - inImage[i][k];
		}
	}
	printImage();
}

void bwImage() { // ��� �˰���
	// �޸� ����
	freeOutputMemory();
	// (�߿�!) ��� �̹����� ũ�⸦ ���� ---> �˰��� ����
	outH = inH;
	outW = inW;
	// �޸� �Ҵ�	
	mallocOutputMemory();

	// �Է� �迭 --> ��� �迭
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			if (inImage[i][k] > 127)
				outImage[i][k] = 255;
			else
				outImage[i][k] = 0;
		}
	}
	printImage();
}

void gamImage() { // ����
	double gamma = getGamma();
	// �޸� ����
	freeOutputMemory();
	// (�߿�!) ��� �̹����� ũ�⸦ ���� ---> �˰��� ����
	outH = inH;
	outW = inW;
	// �޸� �Ҵ�
	mallocOutputMemory();

	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			outImage[i][k] = 255 * pow(inImage[i][k] / 255., 1 / gamma);
		}
	}
	printImage();
}

void CAPparaImage() { // CAP �Ķ󺼶�
	// �޸� ����
	freeOutputMemory();
	// (�߿�!) ��� �̹����� ũ�⸦ ���� ---> �˰��� ����
	outH = inH;
	outW = inW;
	// �޸� �Ҵ�
	mallocOutputMemory();

	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			outImage[i][k] = 255 * pow(inImage[i][k] / 127 - 1, 2);
		}
	}
	printImage();
}

void CUPparaImage() { // CUP �Ķ󺼶�
	// �޸� ����
	freeOutputMemory();
	// (�߿�!) ��� �̹����� ũ�⸦ ���� ---> �˰��� ����
	outH = inH;
	outW = inW;
	// �޸� �Ҵ�
	mallocOutputMemory();

	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			outImage[i][k] = 255 - 255 * pow(inImage[i][k] / 127 - 1, 2);
		}
	}
	printImage();
}

void avgbwImage() { // ���(��հ�)
	// �޸� ����
	freeOutputMemory();
	// (�߿�!) ��� �̹����� ũ�⸦ ���� ---> �˰��� ����
	outH = inH;
	outW = inW;
	// �޸� �Ҵ�
	mallocOutputMemory();

	int avg;
	int hap = 0;
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			hap += inImage[i][k];
			avg = hap / (inH * inW);
		}
	}
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			if (inImage[i][k] < avg)
				outImage[i][k] = 0;
			else
				outImage[i][k] = 255;
		}
	}
	printImage();
}

void midbwImage() { // ���(�߾Ӱ�)
	// �޸� ����
	freeOutputMemory();
	// (�߿�!) ��� �̹����� ũ�⸦ ���� ---> �˰��� ����
	outH = inH;
	outW = inW;
	// �޸� �Ҵ�
	mallocOutputMemory();
	int mid;
	int cnt = 0;
	int size = inH * inW;
	unsigned char* arr;
	arr = (unsigned char*)malloc(sizeof(unsigned char) * size);
	// unsigned char arr[height * width];

	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			arr[cnt] = inImage[i][k];
			cnt++;
		}
	}
	qsort(arr, cnt, sizeof(unsigned char), compare);
	mid = arr[size / 2];
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			if (inImage[i][k] < mid)
				outImage[i][k] = 0;
			else
				outImage[i][k] = 255;
		}
	}
	printImage();

	free(arr);
}

void stretchImage() { // ��� ��� ��Ʈ��Ī
	// �޸� ����
	freeOutputMemory();
	// (�߿�!) ��� �̹����� ũ�⸦ ���� ---> �˰��� ����
	outH = inH;
	outW = inW;
	// �޸� �Ҵ�
	mallocOutputMemory();

	int histogram[256];
	int min = 255, max = 0;
	unsigned char LUT[256];
	double scale, tmp;

	for (int i = 0; i < 256; i++) {
		histogram[i] = 0;
	}
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			histogram[inImage[i][k]]++;
		}
	}
	for (int i = 0; i < 256; i++) {
		if (histogram[i]) {
			min = i;
			break;
		}
	}
	for (int i = 255; i >= 0; i--) {
		if (histogram[i]) {
			max = i;
			break;
		}
	}
	for (int i = 0; i < min; i++) {
		LUT[i] = 0;
	}
	for (int i = max; i >= 0; i--) {
		LUT[i] = 255;
	}
	scale = 255. / (double)(max - min);
	for (int i = min; i < max; i++) {
		tmp = (i - min) * scale;

		if (tmp < 0)
			tmp = 0;
		else if (tmp > 255)
			tmp = 255;
		LUT[i] = (unsigned char)tmp;
	}
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			outImage[i][k] = LUT[inImage[i][k]];
		}
	}
	printImage();
}

void posterImage() { // �����Ͷ���¡
	// �޸� ����
	freeOutputMemory();
	// (�߿�!) ��� �̹����� ũ�⸦ ���� ---> �˰��� ����
	outH = inH;
	outW = inW;
	// �޸� �Ҵ�
	mallocOutputMemory();

	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			if (inImage[i][k] <= 0)
				outImage[i][k] = 0;
			else if ((0 < inImage[i][k]) && (inImage[i][k] <= 32))
				outImage[i][k] = 16;
			else if ((32 < inImage[i][k]) && (inImage[i][k] <= 64))
				outImage[i][k] = 48;
			else if ((64 < inImage[i][k]) && (inImage[i][k] <= 96))
				outImage[i][k] = 80;
			else if ((96 < inImage[i][k]) && (inImage[i][k] <= 128))
				outImage[i][k] = 112;
			else if ((128 < inImage[i][k]) && (inImage[i][k] <= 160))
				outImage[i][k] = 144;
			else if ((160 < inImage[i][k]) && (inImage[i][k] <= 192))
				outImage[i][k] = 176;
			else if ((192 < inImage[i][k]) && (inImage[i][k] <= 224))
				outImage[i][k] = 208;
			else if ((224 < inImage[i][k]) && (inImage[i][k] <= 255))
				outImage[i][k] = 240;
		}
	}
	printImage();
}

void stressImage() { // ���� ����
	// �޸� ����
	freeOutputMemory();
	// (�߿�!) ��� �̹����� ũ�⸦ ���� ---> �˰��� ����
	outH = inH;
	outW = inW;
	// �޸� �Ҵ�	
	mallocOutputMemory();
	// �Է� �迭 --> ��� �迭

	int start = getStartValue();
	int end = getEndValue();

	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			if (start <= inImage[i][k] && inImage[i][k] <= end)
				outImage[i][k] = 255;
			else
				outImage[i][k] = inImage[i][k];
		}
	}
	printImage();
}

void zoutImage() { // ���
	int scale = getIntValue();
	// �޸� ����
	freeOutputMemory();
	// (�߿�!) ��� �̹����� ũ�⸦ ���� ---> �˰��� ����
	outH = (int)(inH / scale);
	outW = (int)(inW / scale);
	// �޸� �Ҵ�
	mallocOutputMemory();

	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			outImage[(int)(i / scale)][(int)(k / scale)] = inImage[i][k];
		}
	}
	printImage();
}

void zinImage() { // Ȯ��(������)
	int scale = getIntValue();
	// �޸� ����
	freeOutputMemory();
	// (�߿�!) ��� �̹����� ũ�⸦ ���� ---> �˰��� ����
	outH = (int)(inH * scale);
	outW = (int)(inW * scale);
	// �޸� �Ҵ�
	mallocOutputMemory();

	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			outImage[(int)(i * scale)][(int)(k * scale)] = inImage[i][k];
		}
	}
	printImage();
}

void zinImage2() { // Ȯ��(�����)
	int scale = getIntValue();
	// �޸� ����
	freeOutputMemory();
	// (�߿�!) ��� �̹����� ũ�⸦ ���� ---> �˰��� ����
	outH = (int)(inH * scale);
	outW = (int)(inW * scale);
	// �޸� �Ҵ�
	mallocOutputMemory();

	for (int i = 0; i < outH; i++) {
		for (int k = 0; k < outW; k++) {
			outImage[i][k] = inImage[(int)(i / scale)][(int)(k / scale)];
		}
	}
	printImage();
}

void rotImage() { // ȸ��(�⺻)
	// �޸� ����
	freeOutputMemory();
	// (�߿�!) ��� �̹����� ũ�⸦ ���� ---> �˰��� ����
	outH = inH;
	outW = inW;
	// �޸� �Ҵ�	
	mallocOutputMemory();
	// �Է� �迭 --> ��� �迭
	int degree = getIntValue();
	double radian = degree * 3.141592 / 180.0;
	// xd = cos*(xs) - sin*(ys)
	// yd = sin*(xs) + cos*(ys)

	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			int xs = i;
			int ys = k;
			int xd = (int)(cos(radian) * xs - sin(radian) * ys);
			int yd = (int)(sin(radian) * xs + cos(radian) * ys);
			if ((0 <= xd && xd < outH) && (0 <= yd && yd < outW))
				outImage[xd][yd] = inImage[xs][ys];
		}
	}
	printImage();
}

void rotImage2() { // ȸ��(�߾�, �����)
	// �޸� ����
	freeOutputMemory();
	// (�߿�!) ��� �̹����� ũ�⸦ ���� ---> �˰��� ����
	outH = inH;
	outW = inW;
	// �޸� �Ҵ�	
	mallocOutputMemory();
	// �Է� �迭 --> ��� �迭
	int degree = getIntValue();
	double radian = degree * 3.141592 / 180.0;
	// xd = cos*(xs) - sin*(ys)
	// yd = sin*(xs) + cos*(ys)

	int cx = inH / 2;
	int cy = inW / 2;
	for (int i = 0; i < outH; i++) {
		for (int k = 0; k < outW; k++) {
			int xd = i;
			int yd = k;
			int xs = (int)(cos(radian) * (xd - cx) + sin(radian) * (yd - cy));
			int ys = (int)(-sin(radian) * (xd - cx) + cos(radian) * (yd - cy));
			xs += cx;
			ys += cy;
			if ((0 <= xs && xs < outH) && (0 <= ys && ys < outW))
				outImage[xd][yd] = inImage[xs][ys];
		}
	}
	printImage();
}

void moveImage() { // �̹��� �̵� �˰���
	// �޸� ����
	freeOutputMemory();
	// (�߿�!) ��� �̹����� ũ�⸦ ���� ---> �˰��� ����
	outH = inH;
	outW = inW;
	// �޸� �Ҵ�	
	mallocOutputMemory();
	// �Է� �迭 --> ��� �迭
	int x = getxValue();
	int y = getyValue();
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			if ((0 <= x + k && x + k < inH) && (0 <= y + i && y + i < inW))
				outImage[i + y][k + x] = inImage[i][k];
		}
	}
	printImage();
}

void mirrorLR() { // �¿���� �˰���
	// �޸� ����
	freeOutputMemory();
	// (�߿�!) ��� �̹����� ũ�⸦ ���� ---> �˰��� ����
	outH = inH;
	outW = inW;
	// �޸� �Ҵ�	
	mallocOutputMemory();
	// �Է� �迭 --> ��� �迭
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			outImage[i][k] = inImage[i][inW - k - 1];
		}
	}
	printImage();
}

void mirrorUD() { // ���Ϲ��� �˰���
	// �޸� ����
	freeOutputMemory();
	// (�߿�!) ��� �̹����� ũ�⸦ ���� ---> �˰��� ����
	outH = inH;
	outW = inW;
	// �޸� �Ҵ�	
	mallocOutputMemory();
	// �Է� �迭 --> ��� �迭
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			outImage[i][k] = inImage[inH - 1 - i][k];
		}
	}
	printImage();
}

void mirrorALL() { // �����¿���� �˰���
	// �޸� ����
	freeOutputMemory();
	// (�߿�!) ��� �̹����� ũ�⸦ ���� ---> �˰��� ����
	outH = inH;
	outW = inW;
	// �޸� �Ҵ�	
	mallocOutputMemory();
	// �Է� �迭 --> ��� �迭
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			outImage[i][k] = inImage[inH - 1 - i][inW - k - 1];
		}
	}
	printImage();
}

void  histoStretch() { // ������׷� ��Ʈ��Ī �˰���
	// �޸� ����
	freeOutputMemory();
	// (�߿�!) ��� �̹����� ũ�⸦ ���� ---> �˰��� ����
	outH = inH;
	outW = inW;
	// �޸� �Ҵ�	
	mallocOutputMemory();

	// ��¥ ����ó�� �˰���
	// new = (old - low) / (high - low) * 255.0
	int high = inImage[0][0], low = inImage[0][0];
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			if (inImage[i][k] < low)
				low = inImage[i][k];
			if (inImage[i][k] > high)
				high = inImage[i][k];
		}
	}
	int old, new;
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			old = inImage[i][k];
			new = (int)((double)(old - low) / (double)(high - low) * 255.0);
			if (new > 255)
				new = 255;
			if (new < 0)
				new = 0;
			outImage[i][k] = new;
		}
	}
	printImage();
}

void  endIn() { // ������ Ž�� �˰���
	// �޸� ����
	freeOutputMemory();
	// (�߿�!) ��� �̹����� ũ�⸦ ���� ---> �˰��� ����
	outH = inH;
	outW = inW;
	// �޸� �Ҵ�	
	mallocOutputMemory();

	// ��¥ ����ó�� �˰���
	// new = (old - low) / (high - low) * 255.0
	int high = inImage[0][0], low = inImage[0][0];
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			if (inImage[i][k] < low)
				low = inImage[i][k];
			if (inImage[i][k] > high)
				high = inImage[i][k];
		}
	}

	high -= 50;
	low += 50;

	int old, new;
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			old = inImage[i][k];
			new = (int)((double)(old - low) / (double)(high - low) * 255.0);
			if (new > 255)
				new = 255;
			if (new < 0)
				new = 0;
			outImage[i][k] = new;
		}
	}
	printImage();
}

void histoEqual() { // ������׷� ��Ȱȭ �˰���
	// �޸� ����
	freeOutputMemory();
	// (�߿�!) ��� �̹����� ũ�⸦ ���� ---> �˰��� ����
	outH = inH;
	outW = inW;
	// �޸� �Ҵ�	
	mallocOutputMemory();
	// 1�ܰ� : �󵵼� ����(=������׷�) histo[256]
	int histo[256] = { 0, };
	for (int i = 0; i < inH; i++)
		for (int k = 0; k < inW; k++)
			histo[inImage[i][k]]++;
	// 2�ܰ� : ����������׷� ����
	int sumHisto[256] = { 0, };
	sumHisto[0] = histo[0];
	for (int i = 1; i < 256; i++)
		sumHisto[i] = sumHisto[i - 1] + histo[i];
	// 3�ܰ� : ����ȭ�� ������׷� ����  normalHisto = sumHisto * (1.0 / (inH*inW) ) * 255.0;
	double normalHisto[256] = { 1.0, };
	for (int i = 0; i < 256; i++) {
		normalHisto[i] = sumHisto[i] * (1.0 / (inH * inW)) * 255.0;
	}
	// 4�ٳ� : inImage�� ����ȭ�� ������ ġȯ
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			outImage[i][k] = (unsigned char)normalHisto[inImage[i][k]];
		}
	}
	printImage();
}

void emboss() { // ȭ�ҿ��� ó�� : ������ �˰���
	// �޸� ����
	freeOutputMemory();
	// (�߿�!) ��� �̹����� ũ�⸦ ���� ---> �˰��� ����
	outH = inH;
	outW = inW;
	// �޸� �Ҵ�	
	mallocOutputMemory();

	////////////////
	// ȭ�� ���� ó��
	/////////////////
	double mask[3][3] = { {-1.0, 0.0, 0.0}, // ������ ����ũ
						  { 0.0, 0.0, 0.0},
						  { 0.0, 0.0, 1.0} };
	// �ӽ� �޸� �Ҵ�(�Ǽ���)
	double** tmpInImage = mallocDoubleMemory(inH + 2, inW + 2);
	double** tmpOutImage = mallocDoubleMemory(outH, outW);

	// �ӽ� �Է� �޸𸮸� �ʱ�ȭ(127) : �ʿ�� ��հ�
	for (int i = 0; i < inH + 2; i++)
		for (int k = 0; k < inW + 2; k++)
			tmpInImage[i][k] = 127;

	// �Է� �̹��� --> �ӽ� �Է� �̹���
	for (int i = 0; i < inH; i++)
		for (int k = 0; k < inW; k++)
			tmpInImage[i + 1][k + 1] = inImage[i][k];

	// *** ȸ�� ���� ***
	double S;
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			// ����ũ(3x3) �� ������ �߽������� 3x3�� ���ϱ�
			S = 0.0; // ����ũ 9���� �Է°� 9���� ���� ���ؼ� ���� ��.

			for (int m = 0; m < 3; m++)
				for (int n = 0; n < 3; n++)
					S += tmpInImage[i + m][k + n] * mask[m][n];

			tmpOutImage[i][k] = S;
		}
	}
	// ��ó�� (����ũ ���� �հ迡 ����...)
	for (int i = 0; i < outH; i++)
		for (int k = 0; k < outW; k++)
			tmpOutImage[i][k] += 127.0;

	// �ӽ� ��� ����--> ��� ����. 
	for (int i = 0; i < outH; i++) {
		for (int k = 0; k < outW; k++) {
			if (tmpOutImage[i][k] < 0.0)
				outImage[i][k] = 0;
			else if (tmpOutImage[i][k] > 255.0)
				outImage[i][k] = 255;
			else
				outImage[i][k] = (unsigned char)tmpOutImage[i][k];
		}
	}
	freeDoubleMemory(tmpInImage, inH + 2);
	freeDoubleMemory(tmpOutImage, outH);
	printImage();
}

void blur() { // ȭ�ҿ��� ó�� : ���� �˰���
	// �޸� ����
	freeOutputMemory();
	// (�߿�!) ��� �̹����� ũ�⸦ ���� ---> �˰��� ����
	outH = inH;
	outW = inW;
	// �޸� �Ҵ�	
	mallocOutputMemory();

	////////////////
	// ȭ�� ���� ó��
	/////////////////
	double mask[3][3] = { {1. / 9, 1. / 9, 1. / 9}, // ���� ����ũ
						  {1. / 9, 1. / 9, 1. / 9},
						  {1. / 9, 1. / 9, 1. / 9} };
	// �ӽ� �޸� �Ҵ�(�Ǽ���)
	double** tmpInImage = mallocDoubleMemory(inH + 2, inW + 2);
	double** tmpOutImage = mallocDoubleMemory(outH, outW);

	// �ӽ� �Է� �޸𸮸� �ʱ�ȭ(127) : �ʿ�� ��հ�
	for (int i = 0; i < inH + 2; i++)
		for (int k = 0; k < inW + 2; k++)
			tmpInImage[i][k] = 127;

	// �Է� �̹��� --> �ӽ� �Է� �̹���
	for (int i = 0; i < inH; i++)
		for (int k = 0; k < inW; k++)
			tmpInImage[i + 1][k + 1] = inImage[i][k];

	// *** ȸ�� ���� ***
	double S;
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			// ����ũ(3x3) �� ������ �߽������� 3x3�� ���ϱ�
			S = 0.0; // ����ũ 9���� �Է°� 9���� ���� ���ؼ� ���� ��.

			for (int m = 0; m < 3; m++)
				for (int n = 0; n < 3; n++)
					S += tmpInImage[i + m][k + n] * mask[m][n];

			tmpOutImage[i][k] = S;
		}
	}
	// ��ó�� (����ũ ���� �հ迡 ����...)
	//for (int i = 0; i < outH; i++)
	//	for (int k = 0; k < outW; k++)
	//		tmpOutImage[i][k] += 127.0;

	// �ӽ� ��� ����--> ��� ����. 
	for (int i = 0; i < outH; i++) {
		for (int k = 0; k < outW; k++) {
			if (tmpOutImage[i][k] < 0.0)
				outImage[i][k] = 0;
			else if (tmpOutImage[i][k] > 255.0)
				outImage[i][k] = 255;
			else
				outImage[i][k] = (unsigned char)tmpOutImage[i][k];
		}
	}
	freeDoubleMemory(tmpInImage, inH + 2);
	freeDoubleMemory(tmpOutImage, outH);
	printImage();
}

void sharpning() { // ȭ�ҿ��� ó�� : ������ �˰���
	// �޸� ����
	freeOutputMemory();
	// (�߿�!) ��� �̹����� ũ�⸦ ���� ---> �˰��� ����
	outH = inH;
	outW = inW;
	// �޸� �Ҵ�	
	mallocOutputMemory();

	////////////////
	// ȭ�� ���� ó��
	/////////////////
	double mask[3][3] = { {0.0, -1.0, 0.0}, // ������ ����ũ
								 {-1.0, 5.0, -1.0},
								 {0.0, -1.0, 0.0} };
	// �ӽ� �޸� �Ҵ�(�Ǽ���)
	double** tmpInImage = mallocDoubleMemory(inH + 2, inW + 2);
	double** tmpOutImage = mallocDoubleMemory(outH, outW);

	// �ӽ� �Է� �޸𸮸� �ʱ�ȭ(127) : �ʿ�� ��հ�
	for (int i = 0; i < inH + 2; i++)
		for (int k = 0; k < inW + 2; k++)
			tmpInImage[i][k] = 127;

	// �Է� �̹��� --> �ӽ� �Է� �̹���
	for (int i = 0; i < inH; i++)
		for (int k = 0; k < inW; k++)
			tmpInImage[i + 1][k + 1] = inImage[i][k];

	// *** ȸ�� ���� ***
	double S;
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			// ����ũ(3x3) �� ������ �߽������� 3x3�� ���ϱ�
			S = 0.0; // ����ũ 9���� �Է°� 9���� ���� ���ؼ� ���� ��.

			for (int m = 0; m < 3; m++)
				for (int n = 0; n < 3; n++)
					S += tmpInImage[i + m][k + n] * mask[m][n];

			tmpOutImage[i][k] = S;
		}
	}
	// ��ó�� (����ũ ���� �հ迡 ����...)
	//for (int i = 0; i < outH; i++)
	//	for (int k = 0; k < outW; k++)
	//		tmpOutImage[i][k] += 127.0;

	// �ӽ� ��� ����--> ��� ����. 
	for (int i = 0; i < outH; i++) {
		for (int k = 0; k < outW; k++) {
			if (tmpOutImage[i][k] < 0.0)
				outImage[i][k] = 0;
			else if (tmpOutImage[i][k] > 255.0)
				outImage[i][k] = 255;
			else
				outImage[i][k] = (unsigned char)tmpOutImage[i][k];
		}
	}
	freeDoubleMemory(tmpInImage, inH + 2);
	freeDoubleMemory(tmpOutImage, outH);
	printImage();
}

void hpfSharp() { // ȭ�ҿ��� ó�� : ���������� ������ �˰���
	// �޸� ����
	freeOutputMemory();
	// (�߿�!) ��� �̹����� ũ�⸦ ���� ---> �˰��� ����
	outH = inH;
	outW = inW;
	// �޸� �Ҵ�	
	mallocOutputMemory();

	////////////////
	// ȭ�� ���� ó��
	/////////////////
	double mask[3][3] = { {-1. / 9, -1. / 9, -1. / 9}, // ���������� ������ ����ũ
								 {-1. / 9, 8. / 9, -1. / 9},
								 {-1. / 9, -1. / 9, -1. / 9} };
	// �ӽ� �޸� �Ҵ�(�Ǽ���)
	double** tmpInImage = mallocDoubleMemory(inH + 2, inW + 2);
	double** tmpOutImage = mallocDoubleMemory(outH, outW);

	// �ӽ� �Է� �޸𸮸� �ʱ�ȭ(127) : �ʿ�� ��հ�
	for (int i = 0; i < inH + 2; i++)
		for (int k = 0; k < inW + 2; k++)
			tmpInImage[i][k] = 127;

	// �Է� �̹��� --> �ӽ� �Է� �̹���
	for (int i = 0; i < inH; i++)
		for (int k = 0; k < inW; k++)
			tmpInImage[i + 1][k + 1] = inImage[i][k];

	// *** ȸ�� ���� ***
	double S;
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			// ����ũ(3x3) �� ������ �߽������� 3x3�� ���ϱ�
			S = 0.0; // ����ũ 9���� �Է°� 9���� ���� ���ؼ� ���� ��.

			for (int m = 0; m < 3; m++)
				for (int n = 0; n < 3; n++)
					S += tmpInImage[i + m][k + n] * mask[m][n];

			tmpOutImage[i][k] = S;
		}
	}
	// ��ó�� (����ũ ���� �հ迡 ����...)
	//for (int i = 0; i < outH; i++)
	//	for (int k = 0; k < outW; k++)
	//		tmpOutImage[i][k] += 127.0;

	// �ӽ� ��� ����--> ��� ����. 
	for (int i = 0; i < outH; i++) {
		for (int k = 0; k < outW; k++) {
			if (tmpOutImage[i][k] < 0.0)
				outImage[i][k] = 0;
			else if (tmpOutImage[i][k] > 255.0)
				outImage[i][k] = 255;
			else
				outImage[i][k] = (unsigned char)tmpOutImage[i][k];
		}
	}
	freeDoubleMemory(tmpInImage, inH + 2);
	freeDoubleMemory(tmpOutImage, outH);
	printImage();
}

void lpfSharp() { // ȭ�ҿ��� ó�� : ���������� ������ �˰���
	// �޸� ����
	freeOutputMemory();
	// (�߿�!) ��� �̹����� ũ�⸦ ���� ---> �˰��� ����
	outH = inH;
	outW = inW;
	// �޸� �Ҵ�	
	mallocOutputMemory();

	////////////////
	// ȭ�� ���� ó��
	/////////////////
	double mask[3][3] = { {1. / 9, 1. / 9, 1. / 9}, // ���������� ������ ����ũ
								 {1. / 9, 1. / 9, 1. / 9},
								 {1. / 9, 1. / 9, 1. / 9} };
	// �ӽ� �޸� �Ҵ�(�Ǽ���)
	double** tmpInImage = mallocDoubleMemory(inH + 2, inW + 2);
	double** tmpOutImage = mallocDoubleMemory(outH, outW);

	// �ӽ� �Է� �޸𸮸� �ʱ�ȭ(127) : �ʿ�� ��հ�
	for (int i = 0; i < inH + 2; i++)
		for (int k = 0; k < inW + 2; k++)
			tmpInImage[i][k] = 127;

	// �Է� �̹��� --> �ӽ� �Է� �̹���
	for (int i = 0; i < inH; i++)
		for (int k = 0; k < inW; k++)
			tmpInImage[i + 1][k + 1] = inImage[i][k];

	// *** ȸ�� ���� ***
	double S;
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			// ����ũ(3x3) �� ������ �߽������� 3x3�� ���ϱ�
			S = 0.0; // ����ũ 9���� �Է°� 9���� ���� ���ؼ� ���� ��.

			for (int m = 0; m < 3; m++)
				for (int n = 0; n < 3; n++)
					S += tmpInImage[i + m][k + n] * mask[m][n];

			tmpOutImage[i][k] = S;
		}
	}
	// ��ó�� (����ũ ���� �հ迡 ����...)
	//for (int i = 0; i < outH; i++)
	//	for (int k = 0; k < outW; k++)
	//		tmpOutImage[i][k] += 127.0;

	// �ӽ� ��� ����--> ��� ����. 
	for (int i = 0; i < outH; i++) {
		for (int k = 0; k < outW; k++) {
			if (tmpOutImage[i][k] < 0.0)
				outImage[i][k] = 0;
			else if (tmpOutImage[i][k] > 255.0)
				outImage[i][k] = 255;
			else
				outImage[i][k] = (unsigned char)tmpOutImage[i][k];
		}
	}
	freeDoubleMemory(tmpInImage, inH + 2);
	freeDoubleMemory(tmpOutImage, outH);
	printImage();
}

void smoothing() { // ȭ�ҿ��� ó�� : ����þ� ������ �˰���
	// �޸� ����
	freeOutputMemory();
	// (�߿�!) ��� �̹����� ũ�⸦ ���� ---> �˰��� ����
	outH = inH;
	outW = inW;
	// �޸� �Ҵ�	
	mallocOutputMemory();

	////////////////
	// ȭ�� ���� ó��
	/////////////////
	double mask[3][3] = { {1. / 16, 1. / 8, 1. / 16}, // ����þ� ������ ����ũ
								 {1. / 8, 1. / 4, 1. / 8},
								 {1. / 16, 1. / 8, 1. / 16} };
	// �ӽ� �޸� �Ҵ�(�Ǽ���)
	double** tmpInImage = mallocDoubleMemory(inH + 2, inW + 2);
	double** tmpOutImage = mallocDoubleMemory(outH, outW);

	// �ӽ� �Է� �޸𸮸� �ʱ�ȭ(127) : �ʿ�� ��հ�
	for (int i = 0; i < inH + 2; i++)
		for (int k = 0; k < inW + 2; k++)
			tmpInImage[i][k] = 127;

	// �Է� �̹��� --> �ӽ� �Է� �̹���
	for (int i = 0; i < inH; i++)
		for (int k = 0; k < inW; k++)
			tmpInImage[i + 1][k + 1] = inImage[i][k];

	// *** ȸ�� ���� ***
	double S;
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			// ����ũ(3x3) �� ������ �߽������� 3x3�� ���ϱ�
			S = 0.0; // ����ũ 9���� �Է°� 9���� ���� ���ؼ� ���� ��.

			for (int m = 0; m < 3; m++)
				for (int n = 0; n < 3; n++)
					S += tmpInImage[i + m][k + n] * mask[m][n];

			tmpOutImage[i][k] = S;
		}
	}
	// ��ó�� (����ũ ���� �հ迡 ����...)
	//for (int i = 0; i < outH; i++)
	//	for (int k = 0; k < outW; k++)
	//		tmpOutImage[i][k] += 127.0;

	// �ӽ� ��� ����--> ��� ����. 
	for (int i = 0; i < outH; i++) {
		for (int k = 0; k < outW; k++) {
			if (tmpOutImage[i][k] < 0.0)
				outImage[i][k] = 0;
			else if (tmpOutImage[i][k] > 255.0)
				outImage[i][k] = 255;
			else
				outImage[i][k] = (unsigned char)tmpOutImage[i][k];
		}
	}
	freeDoubleMemory(tmpInImage, inH + 2);
	freeDoubleMemory(tmpOutImage, outH);
	printImage();
}

void edge1() { // ȭ�ҿ��� ó�� : �������� �˰���
	// �޸� ����
	freeOutputMemory();
	// (�߿�!) ��� �̹����� ũ�⸦ ���� ---> �˰��� ����
	outH = inH;
	outW = inW;
	// �޸� �Ҵ�	
	mallocOutputMemory();

	////////////////
	// ȭ�� ���� ó��
	/////////////////
	double mask[3][3] = { {0.0, 0.0, 0.0}, // �������� ����ũ
						  {-1.0, 1.0, 0.0},
						  {0.0, 0.0, 0.0} };
	// �ӽ� �޸� �Ҵ�(�Ǽ���)
	double** tmpInImage = mallocDoubleMemory(inH + 2, inW + 2);
	double** tmpOutImage = mallocDoubleMemory(outH, outW);

	// �ӽ� �Է� �޸𸮸� �ʱ�ȭ(127) : �ʿ�� ��հ�
	for (int i = 0; i < inH + 2; i++)
		for (int k = 0; k < inW + 2; k++)
			tmpInImage[i][k] = 127;

	// �Է� �̹��� --> �ӽ� �Է� �̹���
	for (int i = 0; i < inH; i++)
		for (int k = 0; k < inW; k++)
			tmpInImage[i + 1][k + 1] = inImage[i][k];

	// *** ȸ�� ���� ***
	double S;
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			// ����ũ(3x3) �� ������ �߽������� 3x3�� ���ϱ�
			S = 0.0; // ����ũ 9���� �Է°� 9���� ���� ���ؼ� ���� ��.

			for (int m = 0; m < 3; m++)
				for (int n = 0; n < 3; n++)
					S += tmpInImage[i + m][k + n] * mask[m][n];

			tmpOutImage[i][k] = S;
		}
	}
	// ��ó�� (����ũ ���� �հ迡 ����...)
	//for (int i = 0; i < outH; i++)
	//	for (int k = 0; k < outW; k++)
	//		tmpOutImage[i][k] += 127.0;

	// �ӽ� ��� ����--> ��� ����. 
	for (int i = 0; i < outH; i++) {
		for (int k = 0; k < outW; k++) {
			if (tmpOutImage[i][k] < 0.0)
				outImage[i][k] = 0;
			else if (tmpOutImage[i][k] > 255.0)
				outImage[i][k] = 255;
			else
				outImage[i][k] = (unsigned char)tmpOutImage[i][k];
		}
	}
	freeDoubleMemory(tmpInImage, inH + 2);
	freeDoubleMemory(tmpOutImage, outH);
	printImage();
}

void edge2() { // ȭ�ҿ��� ó�� : ������� �˰���
	// �޸� ����
	freeOutputMemory();
	// (�߿�!) ��� �̹����� ũ�⸦ ���� ---> �˰��� ����
	outH = inH;
	outW = inW;
	// �޸� �Ҵ�	
	mallocOutputMemory();

	////////////////
	// ȭ�� ���� ó��
	/////////////////
	double mask[3][3] = { {0.0, -1.0, 0.0}, // ������� ����ũ
						  {0.0, 1.0, 0.0},
						  {0.0, 0.0, 0.0} };
	// �ӽ� �޸� �Ҵ�(�Ǽ���)
	double** tmpInImage = mallocDoubleMemory(inH + 2, inW + 2);
	double** tmpOutImage = mallocDoubleMemory(outH, outW);

	// �ӽ� �Է� �޸𸮸� �ʱ�ȭ(127) : �ʿ�� ��հ�
	for (int i = 0; i < inH + 2; i++)
		for (int k = 0; k < inW + 2; k++)
			tmpInImage[i][k] = 127;

	// �Է� �̹��� --> �ӽ� �Է� �̹���
	for (int i = 0; i < inH; i++)
		for (int k = 0; k < inW; k++)
			tmpInImage[i + 1][k + 1] = inImage[i][k];

	// *** ȸ�� ���� ***
	double S;
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			// ����ũ(3x3) �� ������ �߽������� 3x3�� ���ϱ�
			S = 0.0; // ����ũ 9���� �Է°� 9���� ���� ���ؼ� ���� ��.

			for (int m = 0; m < 3; m++)
				for (int n = 0; n < 3; n++)
					S += tmpInImage[i + m][k + n] * mask[m][n];

			tmpOutImage[i][k] = S;
		}
	}
	// ��ó�� (����ũ ���� �հ迡 ����...)
	//for (int i = 0; i < outH; i++)
	//	for (int k = 0; k < outW; k++)
	//		tmpOutImage[i][k] += 127.0;

	// �ӽ� ��� ����--> ��� ����. 
	for (int i = 0; i < outH; i++) {
		for (int k = 0; k < outW; k++) {
			if (tmpOutImage[i][k] < 0.0)
				outImage[i][k] = 0;
			else if (tmpOutImage[i][k] > 255.0)
				outImage[i][k] = 255;
			else
				outImage[i][k] = (unsigned char)tmpOutImage[i][k];
		}
	}
	freeDoubleMemory(tmpInImage, inH + 2);
	freeDoubleMemory(tmpOutImage, outH);
	printImage();
}

void edge3() { // ȭ�ҿ��� ó�� : ���翬���� �˰���
	// �޸� ����
	freeOutputMemory();
	// (�߿�!) ��� �̹����� ũ�⸦ ���� ---> �˰��� ����
	outH = inH;
	outW = inW;
	// �޸� �Ҵ�	
	mallocOutputMemory();

	////////////////
	// ȭ�� ���� ó��
	/////////////////
	double mask[3][3] = { {1.0, 1.0, 1.0}, // ���翬���� ����ũ
						  {1.0, 1.0, 1.0},
						  {1.0, 1.0, 1.0} };
	// �ӽ� �޸� �Ҵ�(�Ǽ���)
	double** tmpInImage = mallocDoubleMemory(inH + 2, inW + 2);
	double** tmpOutImage = mallocDoubleMemory(outH, outW);

	// �ӽ� �Է� �޸𸮸� �ʱ�ȭ(127) : �ʿ�� ��հ�
	for (int i = 0; i < inH + 2; i++)
		for (int k = 0; k < inW + 2; k++)
			tmpInImage[i][k] = 127;

	// �Է� �̹��� --> �ӽ� �Է� �̹���
	for (int i = 0; i < inH; i++)
		for (int k = 0; k < inW; k++)
			tmpInImage[i + 1][k + 1] = inImage[i][k];

	// *** ȸ�� ���� ***
	double S, dif;
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			// ����ũ(3x3) �� ������ �߽������� 3x3�� ���ϱ�
			dif = 0.0; // ����ũ 9���� �Է°� 9���� ���� ���ؼ� ���� ��.

			for (int m = 0; m < 3; m++) {
				for (int n = 0; n < 3; n++) {
					S = tmpInImage[i + 1][k + 1] - tmpInImage[i + m][k + n];
					if (S > dif)
						dif = S;
				}
			}
			tmpOutImage[i][k] = dif;
		}
	}
	// ��ó�� (����ũ ���� �հ迡 ����...)
	//for (int i = 0; i < outH; i++)
	//	for (int k = 0; k < outW; k++)
	//		tmpOutImage[i][k] += 127.0;

	// �ӽ� ��� ����--> ��� ����. 
	double t;
	for (int i = 0; i < outH; i++) {
		for (int k = 0; k < outW; k++) {
			t = tmpOutImage[i][k];
			if (t < 0.0)
				t = 0.0;
			else if (t > 255.0)
				t = 255.0;
			else
				outImage[i][k] = (unsigned char)tmpOutImage[i][k] * (t / 255);
		}
	}
	freeDoubleMemory(tmpInImage, inH + 2);
	freeDoubleMemory(tmpOutImage, outH);
	printImage();
}

void Rrow() { // ȭ�ҿ��� ó�� : �ι���(�� ����) �˰���
	// �޸� ����
	freeOutputMemory();
	// (�߿�!) ��� �̹����� ũ�⸦ ���� ---> �˰��� ����
	outH = inH;
	outW = inW;
	// �޸� �Ҵ�	
	mallocOutputMemory();

	////////////////
	// ȭ�� ���� ó��
	/////////////////
	double mask[3][3] = { {-1.0, 0.0, 0.0}, // �ι���(�� ����) ����ũ
						  {0.0, 1.0, 0.0},
						  {0.0, 0.0, 0.0} };
	// �ӽ� �޸� �Ҵ�(�Ǽ���)
	double** tmpInImage = mallocDoubleMemory(inH + 2, inW + 2);
	double** tmpOutImage = mallocDoubleMemory(outH, outW);

	// �ӽ� �Է� �޸𸮸� �ʱ�ȭ(127) : �ʿ�� ��հ�
	for (int i = 0; i < inH + 2; i++)
		for (int k = 0; k < inW + 2; k++)
			tmpInImage[i][k] = 127;

	// �Է� �̹��� --> �ӽ� �Է� �̹���
	for (int i = 0; i < inH; i++)
		for (int k = 0; k < inW; k++)
			tmpInImage[i + 1][k + 1] = inImage[i][k];

	// *** ȸ�� ���� ***
	double S;
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			// ����ũ(3x3) �� ������ �߽������� 3x3�� ���ϱ�
			S = 0.0; // ����ũ 9���� �Է°� 9���� ���� ���ؼ� ���� ��.

			for (int m = 0; m < 3; m++)
				for (int n = 0; n < 3; n++)
					S += tmpInImage[i + m][k + n] * mask[m][n];

			tmpOutImage[i][k] = S;
		}
	}
	// ��ó�� (����ũ ���� �հ迡 ����...)
	//for (int i = 0; i < outH; i++)
	//	for (int k = 0; k < outW; k++)
	//		tmpOutImage[i][k] += 127.0;

	// �ӽ� ��� ����--> ��� ����. 
	for (int i = 0; i < outH; i++) {
		for (int k = 0; k < outW; k++) {
			if (tmpOutImage[i][k] < 0.0)
				outImage[i][k] = 0;
			else if (tmpOutImage[i][k] > 255.0)
				outImage[i][k] = 255;
			else
				outImage[i][k] = (unsigned char)tmpOutImage[i][k];
		}
	}
	freeDoubleMemory(tmpInImage, inH + 2);
	freeDoubleMemory(tmpOutImage, outH);
	printImage();
}

void Rcol() { // ȭ�ҿ��� ó�� : �ι���(�� ����) �˰���
	// �޸� ����
	freeOutputMemory();
	// (�߿�!) ��� �̹����� ũ�⸦ ���� ---> �˰��� ����
	outH = inH;
	outW = inW;
	// �޸� �Ҵ�	
	mallocOutputMemory();

	////////////////
	// ȭ�� ���� ó��
	/////////////////
	double mask[3][3] = { {0.0, 0.0, -1.0}, // �ι���(�� ����) ����ũ
						  {0.0, 1.0, 0.0},
						  {0.0, 0.0, 0.0} };
	// �ӽ� �޸� �Ҵ�(�Ǽ���)
	double** tmpInImage = mallocDoubleMemory(inH + 2, inW + 2);
	double** tmpOutImage = mallocDoubleMemory(outH, outW);

	// �ӽ� �Է� �޸𸮸� �ʱ�ȭ(127) : �ʿ�� ��հ�
	for (int i = 0; i < inH + 2; i++)
		for (int k = 0; k < inW + 2; k++)
			tmpInImage[i][k] = 127;

	// �Է� �̹��� --> �ӽ� �Է� �̹���
	for (int i = 0; i < inH; i++)
		for (int k = 0; k < inW; k++)
			tmpInImage[i + 1][k + 1] = inImage[i][k];

	// *** ȸ�� ���� ***
	double S;
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			// ����ũ(3x3) �� ������ �߽������� 3x3�� ���ϱ�
			S = 0.0; // ����ũ 9���� �Է°� 9���� ���� ���ؼ� ���� ��.

			for (int m = 0; m < 3; m++)
				for (int n = 0; n < 3; n++)
					S += tmpInImage[i + m][k + n] * mask[m][n];

			tmpOutImage[i][k] = S;
		}
	}
	// ��ó�� (����ũ ���� �հ迡 ����...)
	//for (int i = 0; i < outH; i++)
	//	for (int k = 0; k < outW; k++)
	//		tmpOutImage[i][k] += 127.0;

	// �ӽ� ��� ����--> ��� ����. 
	for (int i = 0; i < outH; i++) {
		for (int k = 0; k < outW; k++) {
			if (tmpOutImage[i][k] < 0.0)
				outImage[i][k] = 0;
			else if (tmpOutImage[i][k] > 255.0)
				outImage[i][k] = 255;
			else
				outImage[i][k] = (unsigned char)tmpOutImage[i][k];
		}
	}
	freeDoubleMemory(tmpInImage, inH + 2);
	freeDoubleMemory(tmpOutImage, outH);
	printImage();
}

void Srow() { // ȭ�ҿ��� ó�� : �Һ�(�� ����) �˰���
	// �޸� ����
	freeOutputMemory();
	// (�߿�!) ��� �̹����� ũ�⸦ ���� ---> �˰��� ����
	outH = inH;
	outW = inW;
	// �޸� �Ҵ�	
	mallocOutputMemory();

	////////////////
	// ȭ�� ���� ó��
	/////////////////
	double mask[3][3] = { {-1.0, -1.0, -1.0}, // �Һ�(�� ����) ����ũ
						  {0.0, 0.0, 0.0},
						  {1.0, 1.0, 1.0} };
	// �ӽ� �޸� �Ҵ�(�Ǽ���)
	double** tmpInImage = mallocDoubleMemory(inH + 2, inW + 2);
	double** tmpOutImage = mallocDoubleMemory(outH, outW);

	// �ӽ� �Է� �޸𸮸� �ʱ�ȭ(127) : �ʿ�� ��հ�
	for (int i = 0; i < inH + 2; i++)
		for (int k = 0; k < inW + 2; k++)
			tmpInImage[i][k] = 127;

	// �Է� �̹��� --> �ӽ� �Է� �̹���
	for (int i = 0; i < inH; i++)
		for (int k = 0; k < inW; k++)
			tmpInImage[i + 1][k + 1] = inImage[i][k];

	// *** ȸ�� ���� ***
	double S;
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			// ����ũ(3x3) �� ������ �߽������� 3x3�� ���ϱ�
			S = 0.0; // ����ũ 9���� �Է°� 9���� ���� ���ؼ� ���� ��.

			for (int m = 0; m < 3; m++)
				for (int n = 0; n < 3; n++)
					S += tmpInImage[i + m][k + n] * mask[m][n];

			tmpOutImage[i][k] = S;
		}
	}
	// ��ó�� (����ũ ���� �հ迡 ����...)
	//for (int i = 0; i < outH; i++)
	//	for (int k = 0; k < outW; k++)
	//		tmpOutImage[i][k] += 127.0;

	// �ӽ� ��� ����--> ��� ����. 
	for (int i = 0; i < outH; i++) {
		for (int k = 0; k < outW; k++) {
			if (tmpOutImage[i][k] < 0.0)
				outImage[i][k] = 0;
			else if (tmpOutImage[i][k] > 255.0)
				outImage[i][k] = 255;
			else
				outImage[i][k] = (unsigned char)tmpOutImage[i][k];
		}
	}
	freeDoubleMemory(tmpInImage, inH + 2);
	freeDoubleMemory(tmpOutImage, outH);
	printImage();
}

void Scol() { // ȭ�ҿ��� ó�� : �Һ�(�� ����) �˰���
	// �޸� ����
	freeOutputMemory();
	// (�߿�!) ��� �̹����� ũ�⸦ ���� ---> �˰��� ����
	outH = inH;
	outW = inW;
	// �޸� �Ҵ�	
	mallocOutputMemory();

	////////////////
	// ȭ�� ���� ó��
	/////////////////
	double mask[3][3] = { {1.0, 0.0, -1.0}, // �Һ�(�� ����) ����ũ
						  {1.0, 0.0, -1.0},
						  {1.0, 0.0, -1.0} };
	// �ӽ� �޸� �Ҵ�(�Ǽ���)
	double** tmpInImage = mallocDoubleMemory(inH + 2, inW + 2);
	double** tmpOutImage = mallocDoubleMemory(outH, outW);

	// �ӽ� �Է� �޸𸮸� �ʱ�ȭ(127) : �ʿ�� ��հ�
	for (int i = 0; i < inH + 2; i++)
		for (int k = 0; k < inW + 2; k++)
			tmpInImage[i][k] = 127;

	// �Է� �̹��� --> �ӽ� �Է� �̹���
	for (int i = 0; i < inH; i++)
		for (int k = 0; k < inW; k++)
			tmpInImage[i + 1][k + 1] = inImage[i][k];

	// *** ȸ�� ���� ***
	double S;
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			// ����ũ(3x3) �� ������ �߽������� 3x3�� ���ϱ�
			S = 0.0; // ����ũ 9���� �Է°� 9���� ���� ���ؼ� ���� ��.

			for (int m = 0; m < 3; m++)
				for (int n = 0; n < 3; n++)
					S += tmpInImage[i + m][k + n] * mask[m][n];

			tmpOutImage[i][k] = S;
		}
	}
	// ��ó�� (����ũ ���� �հ迡 ����...)
	//for (int i = 0; i < outH; i++)
	//	for (int k = 0; k < outW; k++)
	//		tmpOutImage[i][k] += 127.0;

	// �ӽ� ��� ����--> ��� ����. 
	for (int i = 0; i < outH; i++) {
		for (int k = 0; k < outW; k++) {
			if (tmpOutImage[i][k] < 0.0)
				outImage[i][k] = 0;
			else if (tmpOutImage[i][k] > 255.0)
				outImage[i][k] = 255;
			else
				outImage[i][k] = (unsigned char)tmpOutImage[i][k];
		}
	}
	freeDoubleMemory(tmpInImage, inH + 2);
	freeDoubleMemory(tmpOutImage, outH);
	printImage();
}

void Prow() { // ȭ�ҿ��� ó�� : ������(�� ����) �˰���
	// �޸� ����
	freeOutputMemory();
	// (�߿�!) ��� �̹����� ũ�⸦ ���� ---> �˰��� ����
	outH = inH;
	outW = inW;
	// �޸� �Ҵ�	
	mallocOutputMemory();

	////////////////
	// ȭ�� ���� ó��
	/////////////////
	double mask[3][3] = { {-1.0, -2.0, -1.0}, // ������(�� ����) ����ũ
						  {0.0, 0.0, 0.0},
						  {1.0, 2.0, 1.0} };
	// �ӽ� �޸� �Ҵ�(�Ǽ���)
	double** tmpInImage = mallocDoubleMemory(inH + 2, inW + 2);
	double** tmpOutImage = mallocDoubleMemory(outH, outW);

	// �ӽ� �Է� �޸𸮸� �ʱ�ȭ(127) : �ʿ�� ��հ�
	for (int i = 0; i < inH + 2; i++)
		for (int k = 0; k < inW + 2; k++)
			tmpInImage[i][k] = 127;

	// �Է� �̹��� --> �ӽ� �Է� �̹���
	for (int i = 0; i < inH; i++)
		for (int k = 0; k < inW; k++)
			tmpInImage[i + 1][k + 1] = inImage[i][k];

	// *** ȸ�� ���� ***
	double S;
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			// ����ũ(3x3) �� ������ �߽������� 3x3�� ���ϱ�
			S = 0.0; // ����ũ 9���� �Է°� 9���� ���� ���ؼ� ���� ��.

			for (int m = 0; m < 3; m++)
				for (int n = 0; n < 3; n++)
					S += tmpInImage[i + m][k + n] * mask[m][n];

			tmpOutImage[i][k] = S;
		}
	}
	// ��ó�� (����ũ ���� �հ迡 ����...)
	//for (int i = 0; i < outH; i++)
	//	for (int k = 0; k < outW; k++)
	//		tmpOutImage[i][k] += 127.0;

	// �ӽ� ��� ����--> ��� ����. 
	for (int i = 0; i < outH; i++) {
		for (int k = 0; k < outW; k++) {
			if (tmpOutImage[i][k] < 0.0)
				outImage[i][k] = 0;
			else if (tmpOutImage[i][k] > 255.0)
				outImage[i][k] = 255;
			else
				outImage[i][k] = (unsigned char)tmpOutImage[i][k];
		}
	}
	freeDoubleMemory(tmpInImage, inH + 2);
	freeDoubleMemory(tmpOutImage, outH);
	printImage();
}

void Pcol() { // ȭ�ҿ��� ó�� : ������(�� ����) �˰���
	// �޸� ����
	freeOutputMemory();
	// (�߿�!) ��� �̹����� ũ�⸦ ���� ---> �˰��� ����
	outH = inH;
	outW = inW;
	// �޸� �Ҵ�	
	mallocOutputMemory();

	////////////////
	// ȭ�� ���� ó��
	/////////////////
	double mask[3][3] = { {1.0, 0.0, -1.0}, // ������(�� ����) ����ũ
						  {2.0, 0.0, -2.0},
						  {1.0, 0.0, -1.0} };
	// �ӽ� �޸� �Ҵ�(�Ǽ���)
	double** tmpInImage = mallocDoubleMemory(inH + 2, inW + 2);
	double** tmpOutImage = mallocDoubleMemory(outH, outW);

	// �ӽ� �Է� �޸𸮸� �ʱ�ȭ(127) : �ʿ�� ��հ�
	for (int i = 0; i < inH + 2; i++)
		for (int k = 0; k < inW + 2; k++)
			tmpInImage[i][k] = 127;

	// �Է� �̹��� --> �ӽ� �Է� �̹���
	for (int i = 0; i < inH; i++)
		for (int k = 0; k < inW; k++)
			tmpInImage[i + 1][k + 1] = inImage[i][k];

	// *** ȸ�� ���� ***
	double S;
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			// ����ũ(3x3) �� ������ �߽������� 3x3�� ���ϱ�
			S = 0.0; // ����ũ 9���� �Է°� 9���� ���� ���ؼ� ���� ��.

			for (int m = 0; m < 3; m++)
				for (int n = 0; n < 3; n++)
					S += tmpInImage[i + m][k + n] * mask[m][n];

			tmpOutImage[i][k] = S;
		}
	}
	// ��ó�� (����ũ ���� �հ迡 ����...)
	//for (int i = 0; i < outH; i++)
	//	for (int k = 0; k < outW; k++)
	//		tmpOutImage[i][k] += 127.0;

	// �ӽ� ��� ����--> ��� ����. 
	for (int i = 0; i < outH; i++) {
		for (int k = 0; k < outW; k++) {
			if (tmpOutImage[i][k] < 0.0)
				outImage[i][k] = 0;
			else if (tmpOutImage[i][k] > 255.0)
				outImage[i][k] = 255;
			else
				outImage[i][k] = (unsigned char)tmpOutImage[i][k];
		}
	}
	freeDoubleMemory(tmpInImage, inH + 2);
	freeDoubleMemory(tmpOutImage, outH);
	printImage();
}

void lap1() { // ȭ�ҿ��� ó�� : ���ö�þ�(1) �˰���
	// �޸� ����
	freeOutputMemory();
	// (�߿�!) ��� �̹����� ũ�⸦ ���� ---> �˰��� ����
	outH = inH;
	outW = inW;
	// �޸� �Ҵ�	
	mallocOutputMemory();

	////////////////
	// ȭ�� ���� ó��
	/////////////////
	double mask[3][3] = { {0.0, -1.0, 0.0}, // ���ö�þ�(1) ����ũ
						  {-1.0, 4.0, -1.0},
						  {0.0, -1.0, 0.0} };
	// �ӽ� �޸� �Ҵ�(�Ǽ���)
	double** tmpInImage = mallocDoubleMemory(inH + 2, inW + 2);
	double** tmpOutImage = mallocDoubleMemory(outH, outW);

	// �ӽ� �Է� �޸𸮸� �ʱ�ȭ(127) : �ʿ�� ��հ�
	for (int i = 0; i < inH + 2; i++)
		for (int k = 0; k < inW + 2; k++)
			tmpInImage[i][k] = 127;

	// �Է� �̹��� --> �ӽ� �Է� �̹���
	for (int i = 0; i < inH; i++)
		for (int k = 0; k < inW; k++)
			tmpInImage[i + 1][k + 1] = inImage[i][k];

	// *** ȸ�� ���� ***
	double S;
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			// ����ũ(3x3) �� ������ �߽������� 3x3�� ���ϱ�
			S = 0.0; // ����ũ 9���� �Է°� 9���� ���� ���ؼ� ���� ��.

			for (int m = 0; m < 3; m++)
				for (int n = 0; n < 3; n++)
					S += tmpInImage[i + m][k + n] * mask[m][n];

			tmpOutImage[i][k] = S;
		}
	}
	// ��ó�� (����ũ ���� �հ迡 ����...)
	//for (int i = 0; i < outH; i++)
	//	for (int k = 0; k < outW; k++)
	//		tmpOutImage[i][k] += 127.0;

	// �ӽ� ��� ����--> ��� ����. 
	for (int i = 0; i < outH; i++) {
		for (int k = 0; k < outW; k++) {
			if (tmpOutImage[i][k] < 0.0)
				outImage[i][k] = 0;
			else if (tmpOutImage[i][k] > 255.0)
				outImage[i][k] = 255;
			else
				outImage[i][k] = (unsigned char)tmpOutImage[i][k];
		}
	}
	freeDoubleMemory(tmpInImage, inH + 2);
	freeDoubleMemory(tmpOutImage, outH);
	printImage();
}

void lap2() { // ȭ�ҿ��� ó�� : ���ö�þ�(2) �˰���
	// �޸� ����
	freeOutputMemory();
	// (�߿�!) ��� �̹����� ũ�⸦ ���� ---> �˰��� ����
	outH = inH;
	outW = inW;
	// �޸� �Ҵ�	
	mallocOutputMemory();

	////////////////
	// ȭ�� ���� ó��
	/////////////////
	double mask[3][3] = { {1.0, 1.0, 1.0}, // ���ö�þ�(2) ����ũ
						  {1.0, -8.0, 1.0},
						  {1.0, 1.0, 1.0} };
	// �ӽ� �޸� �Ҵ�(�Ǽ���)
	double** tmpInImage = mallocDoubleMemory(inH + 2, inW + 2);
	double** tmpOutImage = mallocDoubleMemory(outH, outW);

	// �ӽ� �Է� �޸𸮸� �ʱ�ȭ(127) : �ʿ�� ��հ�
	for (int i = 0; i < inH + 2; i++)
		for (int k = 0; k < inW + 2; k++)
			tmpInImage[i][k] = 127;

	// �Է� �̹��� --> �ӽ� �Է� �̹���
	for (int i = 0; i < inH; i++)
		for (int k = 0; k < inW; k++)
			tmpInImage[i + 1][k + 1] = inImage[i][k];

	// *** ȸ�� ���� ***
	double S;
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			// ����ũ(3x3) �� ������ �߽������� 3x3�� ���ϱ�
			S = 0.0; // ����ũ 9���� �Է°� 9���� ���� ���ؼ� ���� ��.

			for (int m = 0; m < 3; m++)
				for (int n = 0; n < 3; n++)
					S += tmpInImage[i + m][k + n] * mask[m][n];

			tmpOutImage[i][k] = S;
		}
	}
	// ��ó�� (����ũ ���� �հ迡 ����...)
	//for (int i = 0; i < outH; i++)
	//	for (int k = 0; k < outW; k++)
	//		tmpOutImage[i][k] += 127.0;

	// �ӽ� ��� ����--> ��� ����. 
	for (int i = 0; i < outH; i++) {
		for (int k = 0; k < outW; k++) {
			if (tmpOutImage[i][k] < 0.0)
				outImage[i][k] = 0;
			else if (tmpOutImage[i][k] > 255.0)
				outImage[i][k] = 255;
			else
				outImage[i][k] = (unsigned char)tmpOutImage[i][k];
		}
	}
	freeDoubleMemory(tmpInImage, inH + 2);
	freeDoubleMemory(tmpOutImage, outH);
	printImage();
}

void lap3() { // ȭ�ҿ��� ó�� : ���ö�þ�(3) �˰���
	// �޸� ����
	freeOutputMemory();
	// (�߿�!) ��� �̹����� ũ�⸦ ���� ---> �˰��� ����
	outH = inH;
	outW = inW;
	// �޸� �Ҵ�	
	mallocOutputMemory();

	////////////////
	// ȭ�� ���� ó��
	/////////////////
	double mask[3][3] = { {-1.0, -1.0, -1.0}, // ���ö�þ�(3) ����ũ
						  {-1.0, 8.0, -1.0},
						  {-1.0, -1.0, -1.0} };
	// �ӽ� �޸� �Ҵ�(�Ǽ���)
	double** tmpInImage = mallocDoubleMemory(inH + 2, inW + 2);
	double** tmpOutImage = mallocDoubleMemory(outH, outW);

	// �ӽ� �Է� �޸𸮸� �ʱ�ȭ(127) : �ʿ�� ��հ�
	for (int i = 0; i < inH + 2; i++)
		for (int k = 0; k < inW + 2; k++)
			tmpInImage[i][k] = 127;

	// �Է� �̹��� --> �ӽ� �Է� �̹���
	for (int i = 0; i < inH; i++)
		for (int k = 0; k < inW; k++)
			tmpInImage[i + 1][k + 1] = inImage[i][k];

	// *** ȸ�� ���� ***
	double S;
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			// ����ũ(3x3) �� ������ �߽������� 3x3�� ���ϱ�
			S = 0.0; // ����ũ 9���� �Է°� 9���� ���� ���ؼ� ���� ��.

			for (int m = 0; m < 3; m++)
				for (int n = 0; n < 3; n++)
					S += tmpInImage[i + m][k + n] * mask[m][n];

			tmpOutImage[i][k] = S;
		}
	}
	// ��ó�� (����ũ ���� �հ迡 ����...)
	//for (int i = 0; i < outH; i++)
	//	for (int k = 0; k < outW; k++)
	//		tmpOutImage[i][k] += 127.0;

	// �ӽ� ��� ����--> ��� ����. 
	for (int i = 0; i < outH; i++) {
		for (int k = 0; k < outW; k++) {
			if (tmpOutImage[i][k] < 0.0)
				outImage[i][k] = 0;
			else if (tmpOutImage[i][k] > 255.0)
				outImage[i][k] = 255;
			else
				outImage[i][k] = (unsigned char)tmpOutImage[i][k];
		}
	}
	freeDoubleMemory(tmpInImage, inH + 2);
	freeDoubleMemory(tmpOutImage, outH);
	printImage();
}