#define  _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <Windows.h> // GUI 지원 기능
#include <math.h>

/////////////////////
// 전역 변수부
/////////////////////
HWND hwnd; // 윈도 화면(외부, 물리적)
HDC hdc; // 윈도 화면 (내부, 논리적)

FILE* rfp, * wfp;
char fileName[200];
int inH, inW, outH, outW;
// 메모리 확보
unsigned char** inImage = NULL, ** outImage = NULL;

/////////////////////
// 함수 선언부
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
// 함수 정의부
/////////////////////
/// 공통 함수
//////////////
void printMenu() {
	puts("\n ## GrayScale Image Processing (Beta 4) ##");
	puts("0.열기 8.저장 9.종료");
	puts("1.화소점 처리 2.기하학 처리 3.히스토그램 처리 4.경계선 검출");
}

void printMenu1() {
	puts("\n ## GrayScale Image Processing (Beta 4) ##");
	puts("8.저장 9.뒤로 가기");
	puts("1.화소점 처리");
	puts("A.동일 B.밝게 C.어둡게 D.반전 E.흑백 F.감마 G.CAP파라볼라 H.CUP파라볼라 I.흑백(평균값) J.흑백(중앙값) K.명암대비스트레칭 L.포스터라이징 M.범위강조");
}

void printMenu2() {
	puts("\n ## GrayScale Image Processing (Beta 4) ##");
	puts("8.저장 9.뒤로 가기");
	puts("2.기하학 처리");
	puts("A.축소 B.확대(포워딩) C.확대(백워딩) D.회전(기본) E.회전(중앙, 백워딩) F.이미지 이동 G.좌우반전 H.상하반전 I.상하좌우반전");
}

void printMenu3() {
	puts("\n ## GrayScale Image Processing (Beta 4) ##");
	puts("8.저장 9.뒤로 가기");
	puts("3.히스토그램 처리");
	puts("A.히스토그램 스트레칭 B.엔드-인 C.평활화 D.엠보싱 E.블러 F.샤프닝 G.고주파필터 샤프닝 H.저주파필터 샤프닝 I.가우시안 스무딩");
}

void printMenu4() {
	puts("\n ## GrayScale Image Processing (Beta 4) ##");
	puts("8.저장 9.뒤로 가기");
	puts("4.경계선 검출");
	puts("A.경계선1(수직검출) B.경계선2(수평검출) C.경계선3(유사연산자) D.로버츠(행 검출) E.로버츠(열 검출) F.소벨(행 검출) G.소벨(열 검출) H.프리윗(행 검출) I.프리윗(열 검출) J.라플라시안(1) K.라플라시안(2) L.라플라시안(3)");
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
	printf("파일명-->"); // flower512, LENA256
	scanf("%s", tmpName);
	strcat(fullName, tmpName);
	strcat(fullName, ".raw");
	strcpy(fileName, fullName);

	// (중요!) 이미지의 폭과 높이를 결정
	rfp = fopen(fileName, "rb");
	if (rfp == NULL) {
		printf("파일명을 확인해주세요.");
		return 1;
	}
	fseek(rfp, 0L, SEEK_END); // 파일의 끝으로 이동
	long long fsize = ftell(rfp); // 나 어디쯤이지?  262,144  --> 512
	fclose(rfp);
	// 메모리 해제
	freeInputMemory();
	// 입력영상 높이, 폭 구하기
	inH = inW = (int)sqrt(fsize);
	// 메모리 할당
	mallocInputMemory();

	// 파일 --> 메모리
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
	printf("파일명-->"); // out01, out02......
	scanf("%s", tmpName);
	strcat(fullName, tmpName);
	strcat(fullName, ".raw");
	strcpy(fileName, fullName);

	wfp = fopen(fileName, "wb");
	// 메모리 --> 파일 (한행씩)
	for (int i = 0; i < outH; i++)
		fwrite(outImage[i], sizeof(unsigned char), outW, wfp);
	fclose(wfp);
	// MessageBox(hwnd, L"저장 완료", L"저장 창", NULL);
	printf("저장 완료");
}

int getIntValue() {
	int retValue;
	printf("정수값-->"); scanf("%d", &retValue);
	return retValue;
}

double getGamma() {
	double gamma;
	printf("감마 값 --> "); scanf("%lf", &gamma);
	return gamma;
}

int getStartValue() {
	int start;
	printf("시작 값-->"); scanf("%d", &start);
	return start;
}

int getEndValue() {
	int end;
	printf("끝 값-->"); scanf("%d", &end);
	return end;
}

int getxValue() {
	int x;
	printf("x 값-->"); scanf("%d", &x);
	return x;
}

int getyValue() {
	int y;
	printf("y 값-->"); scanf("%d", &y);
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
//  영상처리 함수
////////////////////
void equalImage() { // 동일영상 알고리즘
	// 메모리 해제
	freeOutputMemory();
	// (중요!) 출력 이미지의 크기를 결정 ---> 알고리즘에 의존
	outH = inH;
	outW = inW;
	// 메모리 할당	
	mallocOutputMemory();
	// 입력 배열 --> 출력 배열
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			outImage[i][k] = inImage[i][k];
		}
	}
	printImage();
}

void addImage() { // 더하기 알고리즘
	// 메모리 해제
	freeOutputMemory();
	// (중요!) 출력 이미지의 크기를 결정 ---> 알고리즘에 의존
	outH = inH;
	outW = inW;
	// 메모리 할당	
	mallocOutputMemory();

	// 입력 배열 --> 출력 배열
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

void subImage() { // 빼기 알고리즘
	// 메모리 해제
	freeOutputMemory();
	// (중요!) 출력 이미지의 크기를 결정 ---> 알고리즘에 의존
	outH = inH;
	outW = inW;
	// 메모리 할당	
	mallocOutputMemory();

	// 입력 배열 --> 출력 배열
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

void reverseImage() { // 반전 알고리즘
	// 메모리 해제
	freeOutputMemory();
	// (중요!) 출력 이미지의 크기를 결정 ---> 알고리즘에 의존
	outH = inH;
	outW = inW;
	// 메모리 할당	
	mallocOutputMemory();

	// 입력 배열 --> 출력 배열
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			outImage[i][k] = 255 - inImage[i][k];
		}
	}
	printImage();
}

void bwImage() { // 흑백 알고리즘
	// 메모리 해제
	freeOutputMemory();
	// (중요!) 출력 이미지의 크기를 결정 ---> 알고리즘에 의존
	outH = inH;
	outW = inW;
	// 메모리 할당	
	mallocOutputMemory();

	// 입력 배열 --> 출력 배열
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

void gamImage() { // 감마
	double gamma = getGamma();
	// 메모리 해제
	freeOutputMemory();
	// (중요!) 출력 이미지의 크기를 결정 ---> 알고리즘에 의존
	outH = inH;
	outW = inW;
	// 메모리 할당
	mallocOutputMemory();

	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			outImage[i][k] = 255 * pow(inImage[i][k] / 255., 1 / gamma);
		}
	}
	printImage();
}

void CAPparaImage() { // CAP 파라볼라
	// 메모리 해제
	freeOutputMemory();
	// (중요!) 출력 이미지의 크기를 결정 ---> 알고리즘에 의존
	outH = inH;
	outW = inW;
	// 메모리 할당
	mallocOutputMemory();

	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			outImage[i][k] = 255 * pow(inImage[i][k] / 127 - 1, 2);
		}
	}
	printImage();
}

void CUPparaImage() { // CUP 파라볼라
	// 메모리 해제
	freeOutputMemory();
	// (중요!) 출력 이미지의 크기를 결정 ---> 알고리즘에 의존
	outH = inH;
	outW = inW;
	// 메모리 할당
	mallocOutputMemory();

	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			outImage[i][k] = 255 - 255 * pow(inImage[i][k] / 127 - 1, 2);
		}
	}
	printImage();
}

void avgbwImage() { // 흑백(평균값)
	// 메모리 해제
	freeOutputMemory();
	// (중요!) 출력 이미지의 크기를 결정 ---> 알고리즘에 의존
	outH = inH;
	outW = inW;
	// 메모리 할당
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

void midbwImage() { // 흑백(중앙값)
	// 메모리 해제
	freeOutputMemory();
	// (중요!) 출력 이미지의 크기를 결정 ---> 알고리즘에 의존
	outH = inH;
	outW = inW;
	// 메모리 할당
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

void stretchImage() { // 명암 대비 스트레칭
	// 메모리 해제
	freeOutputMemory();
	// (중요!) 출력 이미지의 크기를 결정 ---> 알고리즘에 의존
	outH = inH;
	outW = inW;
	// 메모리 할당
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

void posterImage() { // 포스터라이징
	// 메모리 해제
	freeOutputMemory();
	// (중요!) 출력 이미지의 크기를 결정 ---> 알고리즘에 의존
	outH = inH;
	outW = inW;
	// 메모리 할당
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

void stressImage() { // 범위 강조
	// 메모리 해제
	freeOutputMemory();
	// (중요!) 출력 이미지의 크기를 결정 ---> 알고리즘에 의존
	outH = inH;
	outW = inW;
	// 메모리 할당	
	mallocOutputMemory();
	// 입력 배열 --> 출력 배열

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

void zoutImage() { // 축소
	int scale = getIntValue();
	// 메모리 해제
	freeOutputMemory();
	// (중요!) 출력 이미지의 크기를 결정 ---> 알고리즘에 의존
	outH = (int)(inH / scale);
	outW = (int)(inW / scale);
	// 메모리 할당
	mallocOutputMemory();

	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			outImage[(int)(i / scale)][(int)(k / scale)] = inImage[i][k];
		}
	}
	printImage();
}

void zinImage() { // 확대(포워딩)
	int scale = getIntValue();
	// 메모리 해제
	freeOutputMemory();
	// (중요!) 출력 이미지의 크기를 결정 ---> 알고리즘에 의존
	outH = (int)(inH * scale);
	outW = (int)(inW * scale);
	// 메모리 할당
	mallocOutputMemory();

	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			outImage[(int)(i * scale)][(int)(k * scale)] = inImage[i][k];
		}
	}
	printImage();
}

void zinImage2() { // 확대(백워딩)
	int scale = getIntValue();
	// 메모리 해제
	freeOutputMemory();
	// (중요!) 출력 이미지의 크기를 결정 ---> 알고리즘에 의존
	outH = (int)(inH * scale);
	outW = (int)(inW * scale);
	// 메모리 할당
	mallocOutputMemory();

	for (int i = 0; i < outH; i++) {
		for (int k = 0; k < outW; k++) {
			outImage[i][k] = inImage[(int)(i / scale)][(int)(k / scale)];
		}
	}
	printImage();
}

void rotImage() { // 회전(기본)
	// 메모리 해제
	freeOutputMemory();
	// (중요!) 출력 이미지의 크기를 결정 ---> 알고리즘에 의존
	outH = inH;
	outW = inW;
	// 메모리 할당	
	mallocOutputMemory();
	// 입력 배열 --> 출력 배열
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

void rotImage2() { // 회전(중앙, 백워딩)
	// 메모리 해제
	freeOutputMemory();
	// (중요!) 출력 이미지의 크기를 결정 ---> 알고리즘에 의존
	outH = inH;
	outW = inW;
	// 메모리 할당	
	mallocOutputMemory();
	// 입력 배열 --> 출력 배열
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

void moveImage() { // 이미지 이동 알고리즘
	// 메모리 해제
	freeOutputMemory();
	// (중요!) 출력 이미지의 크기를 결정 ---> 알고리즘에 의존
	outH = inH;
	outW = inW;
	// 메모리 할당	
	mallocOutputMemory();
	// 입력 배열 --> 출력 배열
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

void mirrorLR() { // 좌우반전 알고리즘
	// 메모리 해제
	freeOutputMemory();
	// (중요!) 출력 이미지의 크기를 결정 ---> 알고리즘에 의존
	outH = inH;
	outW = inW;
	// 메모리 할당	
	mallocOutputMemory();
	// 입력 배열 --> 출력 배열
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			outImage[i][k] = inImage[i][inW - k - 1];
		}
	}
	printImage();
}

void mirrorUD() { // 상하반전 알고리즘
	// 메모리 해제
	freeOutputMemory();
	// (중요!) 출력 이미지의 크기를 결정 ---> 알고리즘에 의존
	outH = inH;
	outW = inW;
	// 메모리 할당	
	mallocOutputMemory();
	// 입력 배열 --> 출력 배열
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			outImage[i][k] = inImage[inH - 1 - i][k];
		}
	}
	printImage();
}

void mirrorALL() { // 상하좌우반전 알고리즘
	// 메모리 해제
	freeOutputMemory();
	// (중요!) 출력 이미지의 크기를 결정 ---> 알고리즘에 의존
	outH = inH;
	outW = inW;
	// 메모리 할당	
	mallocOutputMemory();
	// 입력 배열 --> 출력 배열
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			outImage[i][k] = inImage[inH - 1 - i][inW - k - 1];
		}
	}
	printImage();
}

void  histoStretch() { // 히스토그램 스트래칭 알고리즘
	// 메모리 해제
	freeOutputMemory();
	// (중요!) 출력 이미지의 크기를 결정 ---> 알고리즘에 의존
	outH = inH;
	outW = inW;
	// 메모리 할당	
	mallocOutputMemory();

	// 진짜 영상처리 알고리즘
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

void  endIn() { // 엔드인 탐색 알고리즘
	// 메모리 해제
	freeOutputMemory();
	// (중요!) 출력 이미지의 크기를 결정 ---> 알고리즘에 의존
	outH = inH;
	outW = inW;
	// 메모리 할당	
	mallocOutputMemory();

	// 진짜 영상처리 알고리즘
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

void histoEqual() { // 히스토그램 평활화 알고리즘
	// 메모리 해제
	freeOutputMemory();
	// (중요!) 출력 이미지의 크기를 결정 ---> 알고리즘에 의존
	outH = inH;
	outW = inW;
	// 메모리 할당	
	mallocOutputMemory();
	// 1단계 : 빈도수 세기(=히스토그램) histo[256]
	int histo[256] = { 0, };
	for (int i = 0; i < inH; i++)
		for (int k = 0; k < inW; k++)
			histo[inImage[i][k]]++;
	// 2단계 : 누적히스토그램 생성
	int sumHisto[256] = { 0, };
	sumHisto[0] = histo[0];
	for (int i = 1; i < 256; i++)
		sumHisto[i] = sumHisto[i - 1] + histo[i];
	// 3단계 : 정규화된 히스토그램 생성  normalHisto = sumHisto * (1.0 / (inH*inW) ) * 255.0;
	double normalHisto[256] = { 1.0, };
	for (int i = 0; i < 256; i++) {
		normalHisto[i] = sumHisto[i] * (1.0 / (inH * inW)) * 255.0;
	}
	// 4다녜 : inImage를 정규화된 값으로 치환
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			outImage[i][k] = (unsigned char)normalHisto[inImage[i][k]];
		}
	}
	printImage();
}

void emboss() { // 화소영역 처리 : 엠보싱 알고리즘
	// 메모리 해제
	freeOutputMemory();
	// (중요!) 출력 이미지의 크기를 결정 ---> 알고리즘에 의존
	outH = inH;
	outW = inW;
	// 메모리 할당	
	mallocOutputMemory();

	////////////////
	// 화소 영역 처리
	/////////////////
	double mask[3][3] = { {-1.0, 0.0, 0.0}, // 엠보싱 마스크
						  { 0.0, 0.0, 0.0},
						  { 0.0, 0.0, 1.0} };
	// 임시 메모리 할당(실수형)
	double** tmpInImage = mallocDoubleMemory(inH + 2, inW + 2);
	double** tmpOutImage = mallocDoubleMemory(outH, outW);

	// 임시 입력 메모리를 초기화(127) : 필요시 평균값
	for (int i = 0; i < inH + 2; i++)
		for (int k = 0; k < inW + 2; k++)
			tmpInImage[i][k] = 127;

	// 입력 이미지 --> 임시 입력 이미지
	for (int i = 0; i < inH; i++)
		for (int k = 0; k < inW; k++)
			tmpInImage[i + 1][k + 1] = inImage[i][k];

	// *** 회선 연산 ***
	double S;
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			// 마스크(3x3) 와 한점을 중심으로한 3x3을 곱하기
			S = 0.0; // 마스크 9개와 입력값 9개를 각각 곱해서 합한 값.

			for (int m = 0; m < 3; m++)
				for (int n = 0; n < 3; n++)
					S += tmpInImage[i + m][k + n] * mask[m][n];

			tmpOutImage[i][k] = S;
		}
	}
	// 후처리 (마스크 값의 합계에 따라서...)
	for (int i = 0; i < outH; i++)
		for (int k = 0; k < outW; k++)
			tmpOutImage[i][k] += 127.0;

	// 임시 출력 영상--> 출력 영상. 
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

void blur() { // 화소영역 처리 : 블러링 알고리즘
	// 메모리 해제
	freeOutputMemory();
	// (중요!) 출력 이미지의 크기를 결정 ---> 알고리즘에 의존
	outH = inH;
	outW = inW;
	// 메모리 할당	
	mallocOutputMemory();

	////////////////
	// 화소 영역 처리
	/////////////////
	double mask[3][3] = { {1. / 9, 1. / 9, 1. / 9}, // 블러링 마스크
						  {1. / 9, 1. / 9, 1. / 9},
						  {1. / 9, 1. / 9, 1. / 9} };
	// 임시 메모리 할당(실수형)
	double** tmpInImage = mallocDoubleMemory(inH + 2, inW + 2);
	double** tmpOutImage = mallocDoubleMemory(outH, outW);

	// 임시 입력 메모리를 초기화(127) : 필요시 평균값
	for (int i = 0; i < inH + 2; i++)
		for (int k = 0; k < inW + 2; k++)
			tmpInImage[i][k] = 127;

	// 입력 이미지 --> 임시 입력 이미지
	for (int i = 0; i < inH; i++)
		for (int k = 0; k < inW; k++)
			tmpInImage[i + 1][k + 1] = inImage[i][k];

	// *** 회선 연산 ***
	double S;
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			// 마스크(3x3) 와 한점을 중심으로한 3x3을 곱하기
			S = 0.0; // 마스크 9개와 입력값 9개를 각각 곱해서 합한 값.

			for (int m = 0; m < 3; m++)
				for (int n = 0; n < 3; n++)
					S += tmpInImage[i + m][k + n] * mask[m][n];

			tmpOutImage[i][k] = S;
		}
	}
	// 후처리 (마스크 값의 합계에 따라서...)
	//for (int i = 0; i < outH; i++)
	//	for (int k = 0; k < outW; k++)
	//		tmpOutImage[i][k] += 127.0;

	// 임시 출력 영상--> 출력 영상. 
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

void sharpning() { // 화소영역 처리 : 샤프닝 알고리즘
	// 메모리 해제
	freeOutputMemory();
	// (중요!) 출력 이미지의 크기를 결정 ---> 알고리즘에 의존
	outH = inH;
	outW = inW;
	// 메모리 할당	
	mallocOutputMemory();

	////////////////
	// 화소 영역 처리
	/////////////////
	double mask[3][3] = { {0.0, -1.0, 0.0}, // 샤프닝 마스크
								 {-1.0, 5.0, -1.0},
								 {0.0, -1.0, 0.0} };
	// 임시 메모리 할당(실수형)
	double** tmpInImage = mallocDoubleMemory(inH + 2, inW + 2);
	double** tmpOutImage = mallocDoubleMemory(outH, outW);

	// 임시 입력 메모리를 초기화(127) : 필요시 평균값
	for (int i = 0; i < inH + 2; i++)
		for (int k = 0; k < inW + 2; k++)
			tmpInImage[i][k] = 127;

	// 입력 이미지 --> 임시 입력 이미지
	for (int i = 0; i < inH; i++)
		for (int k = 0; k < inW; k++)
			tmpInImage[i + 1][k + 1] = inImage[i][k];

	// *** 회선 연산 ***
	double S;
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			// 마스크(3x3) 와 한점을 중심으로한 3x3을 곱하기
			S = 0.0; // 마스크 9개와 입력값 9개를 각각 곱해서 합한 값.

			for (int m = 0; m < 3; m++)
				for (int n = 0; n < 3; n++)
					S += tmpInImage[i + m][k + n] * mask[m][n];

			tmpOutImage[i][k] = S;
		}
	}
	// 후처리 (마스크 값의 합계에 따라서...)
	//for (int i = 0; i < outH; i++)
	//	for (int k = 0; k < outW; k++)
	//		tmpOutImage[i][k] += 127.0;

	// 임시 출력 영상--> 출력 영상. 
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

void hpfSharp() { // 화소영역 처리 : 고주파필터 샤프닝 알고리즘
	// 메모리 해제
	freeOutputMemory();
	// (중요!) 출력 이미지의 크기를 결정 ---> 알고리즘에 의존
	outH = inH;
	outW = inW;
	// 메모리 할당	
	mallocOutputMemory();

	////////////////
	// 화소 영역 처리
	/////////////////
	double mask[3][3] = { {-1. / 9, -1. / 9, -1. / 9}, // 고주파필터 샤프닝 마스크
								 {-1. / 9, 8. / 9, -1. / 9},
								 {-1. / 9, -1. / 9, -1. / 9} };
	// 임시 메모리 할당(실수형)
	double** tmpInImage = mallocDoubleMemory(inH + 2, inW + 2);
	double** tmpOutImage = mallocDoubleMemory(outH, outW);

	// 임시 입력 메모리를 초기화(127) : 필요시 평균값
	for (int i = 0; i < inH + 2; i++)
		for (int k = 0; k < inW + 2; k++)
			tmpInImage[i][k] = 127;

	// 입력 이미지 --> 임시 입력 이미지
	for (int i = 0; i < inH; i++)
		for (int k = 0; k < inW; k++)
			tmpInImage[i + 1][k + 1] = inImage[i][k];

	// *** 회선 연산 ***
	double S;
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			// 마스크(3x3) 와 한점을 중심으로한 3x3을 곱하기
			S = 0.0; // 마스크 9개와 입력값 9개를 각각 곱해서 합한 값.

			for (int m = 0; m < 3; m++)
				for (int n = 0; n < 3; n++)
					S += tmpInImage[i + m][k + n] * mask[m][n];

			tmpOutImage[i][k] = S;
		}
	}
	// 후처리 (마스크 값의 합계에 따라서...)
	//for (int i = 0; i < outH; i++)
	//	for (int k = 0; k < outW; k++)
	//		tmpOutImage[i][k] += 127.0;

	// 임시 출력 영상--> 출력 영상. 
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

void lpfSharp() { // 화소영역 처리 : 저주파필터 샤프닝 알고리즘
	// 메모리 해제
	freeOutputMemory();
	// (중요!) 출력 이미지의 크기를 결정 ---> 알고리즘에 의존
	outH = inH;
	outW = inW;
	// 메모리 할당	
	mallocOutputMemory();

	////////////////
	// 화소 영역 처리
	/////////////////
	double mask[3][3] = { {1. / 9, 1. / 9, 1. / 9}, // 저주파필터 샤프닝 마스크
								 {1. / 9, 1. / 9, 1. / 9},
								 {1. / 9, 1. / 9, 1. / 9} };
	// 임시 메모리 할당(실수형)
	double** tmpInImage = mallocDoubleMemory(inH + 2, inW + 2);
	double** tmpOutImage = mallocDoubleMemory(outH, outW);

	// 임시 입력 메모리를 초기화(127) : 필요시 평균값
	for (int i = 0; i < inH + 2; i++)
		for (int k = 0; k < inW + 2; k++)
			tmpInImage[i][k] = 127;

	// 입력 이미지 --> 임시 입력 이미지
	for (int i = 0; i < inH; i++)
		for (int k = 0; k < inW; k++)
			tmpInImage[i + 1][k + 1] = inImage[i][k];

	// *** 회선 연산 ***
	double S;
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			// 마스크(3x3) 와 한점을 중심으로한 3x3을 곱하기
			S = 0.0; // 마스크 9개와 입력값 9개를 각각 곱해서 합한 값.

			for (int m = 0; m < 3; m++)
				for (int n = 0; n < 3; n++)
					S += tmpInImage[i + m][k + n] * mask[m][n];

			tmpOutImage[i][k] = S;
		}
	}
	// 후처리 (마스크 값의 합계에 따라서...)
	//for (int i = 0; i < outH; i++)
	//	for (int k = 0; k < outW; k++)
	//		tmpOutImage[i][k] += 127.0;

	// 임시 출력 영상--> 출력 영상. 
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

void smoothing() { // 화소영역 처리 : 가우시안 스무딩 알고리즘
	// 메모리 해제
	freeOutputMemory();
	// (중요!) 출력 이미지의 크기를 결정 ---> 알고리즘에 의존
	outH = inH;
	outW = inW;
	// 메모리 할당	
	mallocOutputMemory();

	////////////////
	// 화소 영역 처리
	/////////////////
	double mask[3][3] = { {1. / 16, 1. / 8, 1. / 16}, // 가우시안 스무딩 마스크
								 {1. / 8, 1. / 4, 1. / 8},
								 {1. / 16, 1. / 8, 1. / 16} };
	// 임시 메모리 할당(실수형)
	double** tmpInImage = mallocDoubleMemory(inH + 2, inW + 2);
	double** tmpOutImage = mallocDoubleMemory(outH, outW);

	// 임시 입력 메모리를 초기화(127) : 필요시 평균값
	for (int i = 0; i < inH + 2; i++)
		for (int k = 0; k < inW + 2; k++)
			tmpInImage[i][k] = 127;

	// 입력 이미지 --> 임시 입력 이미지
	for (int i = 0; i < inH; i++)
		for (int k = 0; k < inW; k++)
			tmpInImage[i + 1][k + 1] = inImage[i][k];

	// *** 회선 연산 ***
	double S;
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			// 마스크(3x3) 와 한점을 중심으로한 3x3을 곱하기
			S = 0.0; // 마스크 9개와 입력값 9개를 각각 곱해서 합한 값.

			for (int m = 0; m < 3; m++)
				for (int n = 0; n < 3; n++)
					S += tmpInImage[i + m][k + n] * mask[m][n];

			tmpOutImage[i][k] = S;
		}
	}
	// 후처리 (마스크 값의 합계에 따라서...)
	//for (int i = 0; i < outH; i++)
	//	for (int k = 0; k < outW; k++)
	//		tmpOutImage[i][k] += 127.0;

	// 임시 출력 영상--> 출력 영상. 
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

void edge1() { // 화소영역 처리 : 수직검출 알고리즘
	// 메모리 해제
	freeOutputMemory();
	// (중요!) 출력 이미지의 크기를 결정 ---> 알고리즘에 의존
	outH = inH;
	outW = inW;
	// 메모리 할당	
	mallocOutputMemory();

	////////////////
	// 화소 영역 처리
	/////////////////
	double mask[3][3] = { {0.0, 0.0, 0.0}, // 수직검출 마스크
						  {-1.0, 1.0, 0.0},
						  {0.0, 0.0, 0.0} };
	// 임시 메모리 할당(실수형)
	double** tmpInImage = mallocDoubleMemory(inH + 2, inW + 2);
	double** tmpOutImage = mallocDoubleMemory(outH, outW);

	// 임시 입력 메모리를 초기화(127) : 필요시 평균값
	for (int i = 0; i < inH + 2; i++)
		for (int k = 0; k < inW + 2; k++)
			tmpInImage[i][k] = 127;

	// 입력 이미지 --> 임시 입력 이미지
	for (int i = 0; i < inH; i++)
		for (int k = 0; k < inW; k++)
			tmpInImage[i + 1][k + 1] = inImage[i][k];

	// *** 회선 연산 ***
	double S;
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			// 마스크(3x3) 와 한점을 중심으로한 3x3을 곱하기
			S = 0.0; // 마스크 9개와 입력값 9개를 각각 곱해서 합한 값.

			for (int m = 0; m < 3; m++)
				for (int n = 0; n < 3; n++)
					S += tmpInImage[i + m][k + n] * mask[m][n];

			tmpOutImage[i][k] = S;
		}
	}
	// 후처리 (마스크 값의 합계에 따라서...)
	//for (int i = 0; i < outH; i++)
	//	for (int k = 0; k < outW; k++)
	//		tmpOutImage[i][k] += 127.0;

	// 임시 출력 영상--> 출력 영상. 
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

void edge2() { // 화소영역 처리 : 수평검출 알고리즘
	// 메모리 해제
	freeOutputMemory();
	// (중요!) 출력 이미지의 크기를 결정 ---> 알고리즘에 의존
	outH = inH;
	outW = inW;
	// 메모리 할당	
	mallocOutputMemory();

	////////////////
	// 화소 영역 처리
	/////////////////
	double mask[3][3] = { {0.0, -1.0, 0.0}, // 수평검출 마스크
						  {0.0, 1.0, 0.0},
						  {0.0, 0.0, 0.0} };
	// 임시 메모리 할당(실수형)
	double** tmpInImage = mallocDoubleMemory(inH + 2, inW + 2);
	double** tmpOutImage = mallocDoubleMemory(outH, outW);

	// 임시 입력 메모리를 초기화(127) : 필요시 평균값
	for (int i = 0; i < inH + 2; i++)
		for (int k = 0; k < inW + 2; k++)
			tmpInImage[i][k] = 127;

	// 입력 이미지 --> 임시 입력 이미지
	for (int i = 0; i < inH; i++)
		for (int k = 0; k < inW; k++)
			tmpInImage[i + 1][k + 1] = inImage[i][k];

	// *** 회선 연산 ***
	double S;
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			// 마스크(3x3) 와 한점을 중심으로한 3x3을 곱하기
			S = 0.0; // 마스크 9개와 입력값 9개를 각각 곱해서 합한 값.

			for (int m = 0; m < 3; m++)
				for (int n = 0; n < 3; n++)
					S += tmpInImage[i + m][k + n] * mask[m][n];

			tmpOutImage[i][k] = S;
		}
	}
	// 후처리 (마스크 값의 합계에 따라서...)
	//for (int i = 0; i < outH; i++)
	//	for (int k = 0; k < outW; k++)
	//		tmpOutImage[i][k] += 127.0;

	// 임시 출력 영상--> 출력 영상. 
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

void edge3() { // 화소영역 처리 : 유사연산자 알고리즘
	// 메모리 해제
	freeOutputMemory();
	// (중요!) 출력 이미지의 크기를 결정 ---> 알고리즘에 의존
	outH = inH;
	outW = inW;
	// 메모리 할당	
	mallocOutputMemory();

	////////////////
	// 화소 영역 처리
	/////////////////
	double mask[3][3] = { {1.0, 1.0, 1.0}, // 유사연산자 마스크
						  {1.0, 1.0, 1.0},
						  {1.0, 1.0, 1.0} };
	// 임시 메모리 할당(실수형)
	double** tmpInImage = mallocDoubleMemory(inH + 2, inW + 2);
	double** tmpOutImage = mallocDoubleMemory(outH, outW);

	// 임시 입력 메모리를 초기화(127) : 필요시 평균값
	for (int i = 0; i < inH + 2; i++)
		for (int k = 0; k < inW + 2; k++)
			tmpInImage[i][k] = 127;

	// 입력 이미지 --> 임시 입력 이미지
	for (int i = 0; i < inH; i++)
		for (int k = 0; k < inW; k++)
			tmpInImage[i + 1][k + 1] = inImage[i][k];

	// *** 회선 연산 ***
	double S, dif;
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			// 마스크(3x3) 와 한점을 중심으로한 3x3을 곱하기
			dif = 0.0; // 마스크 9개와 입력값 9개를 각각 곱해서 합한 값.

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
	// 후처리 (마스크 값의 합계에 따라서...)
	//for (int i = 0; i < outH; i++)
	//	for (int k = 0; k < outW; k++)
	//		tmpOutImage[i][k] += 127.0;

	// 임시 출력 영상--> 출력 영상. 
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

void Rrow() { // 화소영역 처리 : 로버츠(행 검출) 알고리즘
	// 메모리 해제
	freeOutputMemory();
	// (중요!) 출력 이미지의 크기를 결정 ---> 알고리즘에 의존
	outH = inH;
	outW = inW;
	// 메모리 할당	
	mallocOutputMemory();

	////////////////
	// 화소 영역 처리
	/////////////////
	double mask[3][3] = { {-1.0, 0.0, 0.0}, // 로버츠(행 검출) 마스크
						  {0.0, 1.0, 0.0},
						  {0.0, 0.0, 0.0} };
	// 임시 메모리 할당(실수형)
	double** tmpInImage = mallocDoubleMemory(inH + 2, inW + 2);
	double** tmpOutImage = mallocDoubleMemory(outH, outW);

	// 임시 입력 메모리를 초기화(127) : 필요시 평균값
	for (int i = 0; i < inH + 2; i++)
		for (int k = 0; k < inW + 2; k++)
			tmpInImage[i][k] = 127;

	// 입력 이미지 --> 임시 입력 이미지
	for (int i = 0; i < inH; i++)
		for (int k = 0; k < inW; k++)
			tmpInImage[i + 1][k + 1] = inImage[i][k];

	// *** 회선 연산 ***
	double S;
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			// 마스크(3x3) 와 한점을 중심으로한 3x3을 곱하기
			S = 0.0; // 마스크 9개와 입력값 9개를 각각 곱해서 합한 값.

			for (int m = 0; m < 3; m++)
				for (int n = 0; n < 3; n++)
					S += tmpInImage[i + m][k + n] * mask[m][n];

			tmpOutImage[i][k] = S;
		}
	}
	// 후처리 (마스크 값의 합계에 따라서...)
	//for (int i = 0; i < outH; i++)
	//	for (int k = 0; k < outW; k++)
	//		tmpOutImage[i][k] += 127.0;

	// 임시 출력 영상--> 출력 영상. 
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

void Rcol() { // 화소영역 처리 : 로버츠(열 검출) 알고리즘
	// 메모리 해제
	freeOutputMemory();
	// (중요!) 출력 이미지의 크기를 결정 ---> 알고리즘에 의존
	outH = inH;
	outW = inW;
	// 메모리 할당	
	mallocOutputMemory();

	////////////////
	// 화소 영역 처리
	/////////////////
	double mask[3][3] = { {0.0, 0.0, -1.0}, // 로버츠(열 검출) 마스크
						  {0.0, 1.0, 0.0},
						  {0.0, 0.0, 0.0} };
	// 임시 메모리 할당(실수형)
	double** tmpInImage = mallocDoubleMemory(inH + 2, inW + 2);
	double** tmpOutImage = mallocDoubleMemory(outH, outW);

	// 임시 입력 메모리를 초기화(127) : 필요시 평균값
	for (int i = 0; i < inH + 2; i++)
		for (int k = 0; k < inW + 2; k++)
			tmpInImage[i][k] = 127;

	// 입력 이미지 --> 임시 입력 이미지
	for (int i = 0; i < inH; i++)
		for (int k = 0; k < inW; k++)
			tmpInImage[i + 1][k + 1] = inImage[i][k];

	// *** 회선 연산 ***
	double S;
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			// 마스크(3x3) 와 한점을 중심으로한 3x3을 곱하기
			S = 0.0; // 마스크 9개와 입력값 9개를 각각 곱해서 합한 값.

			for (int m = 0; m < 3; m++)
				for (int n = 0; n < 3; n++)
					S += tmpInImage[i + m][k + n] * mask[m][n];

			tmpOutImage[i][k] = S;
		}
	}
	// 후처리 (마스크 값의 합계에 따라서...)
	//for (int i = 0; i < outH; i++)
	//	for (int k = 0; k < outW; k++)
	//		tmpOutImage[i][k] += 127.0;

	// 임시 출력 영상--> 출력 영상. 
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

void Srow() { // 화소영역 처리 : 소벨(행 검출) 알고리즘
	// 메모리 해제
	freeOutputMemory();
	// (중요!) 출력 이미지의 크기를 결정 ---> 알고리즘에 의존
	outH = inH;
	outW = inW;
	// 메모리 할당	
	mallocOutputMemory();

	////////////////
	// 화소 영역 처리
	/////////////////
	double mask[3][3] = { {-1.0, -1.0, -1.0}, // 소벨(행 검출) 마스크
						  {0.0, 0.0, 0.0},
						  {1.0, 1.0, 1.0} };
	// 임시 메모리 할당(실수형)
	double** tmpInImage = mallocDoubleMemory(inH + 2, inW + 2);
	double** tmpOutImage = mallocDoubleMemory(outH, outW);

	// 임시 입력 메모리를 초기화(127) : 필요시 평균값
	for (int i = 0; i < inH + 2; i++)
		for (int k = 0; k < inW + 2; k++)
			tmpInImage[i][k] = 127;

	// 입력 이미지 --> 임시 입력 이미지
	for (int i = 0; i < inH; i++)
		for (int k = 0; k < inW; k++)
			tmpInImage[i + 1][k + 1] = inImage[i][k];

	// *** 회선 연산 ***
	double S;
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			// 마스크(3x3) 와 한점을 중심으로한 3x3을 곱하기
			S = 0.0; // 마스크 9개와 입력값 9개를 각각 곱해서 합한 값.

			for (int m = 0; m < 3; m++)
				for (int n = 0; n < 3; n++)
					S += tmpInImage[i + m][k + n] * mask[m][n];

			tmpOutImage[i][k] = S;
		}
	}
	// 후처리 (마스크 값의 합계에 따라서...)
	//for (int i = 0; i < outH; i++)
	//	for (int k = 0; k < outW; k++)
	//		tmpOutImage[i][k] += 127.0;

	// 임시 출력 영상--> 출력 영상. 
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

void Scol() { // 화소영역 처리 : 소벨(열 검출) 알고리즘
	// 메모리 해제
	freeOutputMemory();
	// (중요!) 출력 이미지의 크기를 결정 ---> 알고리즘에 의존
	outH = inH;
	outW = inW;
	// 메모리 할당	
	mallocOutputMemory();

	////////////////
	// 화소 영역 처리
	/////////////////
	double mask[3][3] = { {1.0, 0.0, -1.0}, // 소벨(열 검출) 마스크
						  {1.0, 0.0, -1.0},
						  {1.0, 0.0, -1.0} };
	// 임시 메모리 할당(실수형)
	double** tmpInImage = mallocDoubleMemory(inH + 2, inW + 2);
	double** tmpOutImage = mallocDoubleMemory(outH, outW);

	// 임시 입력 메모리를 초기화(127) : 필요시 평균값
	for (int i = 0; i < inH + 2; i++)
		for (int k = 0; k < inW + 2; k++)
			tmpInImage[i][k] = 127;

	// 입력 이미지 --> 임시 입력 이미지
	for (int i = 0; i < inH; i++)
		for (int k = 0; k < inW; k++)
			tmpInImage[i + 1][k + 1] = inImage[i][k];

	// *** 회선 연산 ***
	double S;
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			// 마스크(3x3) 와 한점을 중심으로한 3x3을 곱하기
			S = 0.0; // 마스크 9개와 입력값 9개를 각각 곱해서 합한 값.

			for (int m = 0; m < 3; m++)
				for (int n = 0; n < 3; n++)
					S += tmpInImage[i + m][k + n] * mask[m][n];

			tmpOutImage[i][k] = S;
		}
	}
	// 후처리 (마스크 값의 합계에 따라서...)
	//for (int i = 0; i < outH; i++)
	//	for (int k = 0; k < outW; k++)
	//		tmpOutImage[i][k] += 127.0;

	// 임시 출력 영상--> 출력 영상. 
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

void Prow() { // 화소영역 처리 : 프리윗(행 검출) 알고리즘
	// 메모리 해제
	freeOutputMemory();
	// (중요!) 출력 이미지의 크기를 결정 ---> 알고리즘에 의존
	outH = inH;
	outW = inW;
	// 메모리 할당	
	mallocOutputMemory();

	////////////////
	// 화소 영역 처리
	/////////////////
	double mask[3][3] = { {-1.0, -2.0, -1.0}, // 프리윗(행 검출) 마스크
						  {0.0, 0.0, 0.0},
						  {1.0, 2.0, 1.0} };
	// 임시 메모리 할당(실수형)
	double** tmpInImage = mallocDoubleMemory(inH + 2, inW + 2);
	double** tmpOutImage = mallocDoubleMemory(outH, outW);

	// 임시 입력 메모리를 초기화(127) : 필요시 평균값
	for (int i = 0; i < inH + 2; i++)
		for (int k = 0; k < inW + 2; k++)
			tmpInImage[i][k] = 127;

	// 입력 이미지 --> 임시 입력 이미지
	for (int i = 0; i < inH; i++)
		for (int k = 0; k < inW; k++)
			tmpInImage[i + 1][k + 1] = inImage[i][k];

	// *** 회선 연산 ***
	double S;
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			// 마스크(3x3) 와 한점을 중심으로한 3x3을 곱하기
			S = 0.0; // 마스크 9개와 입력값 9개를 각각 곱해서 합한 값.

			for (int m = 0; m < 3; m++)
				for (int n = 0; n < 3; n++)
					S += tmpInImage[i + m][k + n] * mask[m][n];

			tmpOutImage[i][k] = S;
		}
	}
	// 후처리 (마스크 값의 합계에 따라서...)
	//for (int i = 0; i < outH; i++)
	//	for (int k = 0; k < outW; k++)
	//		tmpOutImage[i][k] += 127.0;

	// 임시 출력 영상--> 출력 영상. 
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

void Pcol() { // 화소영역 처리 : 프리윗(열 검출) 알고리즘
	// 메모리 해제
	freeOutputMemory();
	// (중요!) 출력 이미지의 크기를 결정 ---> 알고리즘에 의존
	outH = inH;
	outW = inW;
	// 메모리 할당	
	mallocOutputMemory();

	////////////////
	// 화소 영역 처리
	/////////////////
	double mask[3][3] = { {1.0, 0.0, -1.0}, // 프리윗(열 검출) 마스크
						  {2.0, 0.0, -2.0},
						  {1.0, 0.0, -1.0} };
	// 임시 메모리 할당(실수형)
	double** tmpInImage = mallocDoubleMemory(inH + 2, inW + 2);
	double** tmpOutImage = mallocDoubleMemory(outH, outW);

	// 임시 입력 메모리를 초기화(127) : 필요시 평균값
	for (int i = 0; i < inH + 2; i++)
		for (int k = 0; k < inW + 2; k++)
			tmpInImage[i][k] = 127;

	// 입력 이미지 --> 임시 입력 이미지
	for (int i = 0; i < inH; i++)
		for (int k = 0; k < inW; k++)
			tmpInImage[i + 1][k + 1] = inImage[i][k];

	// *** 회선 연산 ***
	double S;
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			// 마스크(3x3) 와 한점을 중심으로한 3x3을 곱하기
			S = 0.0; // 마스크 9개와 입력값 9개를 각각 곱해서 합한 값.

			for (int m = 0; m < 3; m++)
				for (int n = 0; n < 3; n++)
					S += tmpInImage[i + m][k + n] * mask[m][n];

			tmpOutImage[i][k] = S;
		}
	}
	// 후처리 (마스크 값의 합계에 따라서...)
	//for (int i = 0; i < outH; i++)
	//	for (int k = 0; k < outW; k++)
	//		tmpOutImage[i][k] += 127.0;

	// 임시 출력 영상--> 출력 영상. 
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

void lap1() { // 화소영역 처리 : 라플라시안(1) 알고리즘
	// 메모리 해제
	freeOutputMemory();
	// (중요!) 출력 이미지의 크기를 결정 ---> 알고리즘에 의존
	outH = inH;
	outW = inW;
	// 메모리 할당	
	mallocOutputMemory();

	////////////////
	// 화소 영역 처리
	/////////////////
	double mask[3][3] = { {0.0, -1.0, 0.0}, // 라플라시안(1) 마스크
						  {-1.0, 4.0, -1.0},
						  {0.0, -1.0, 0.0} };
	// 임시 메모리 할당(실수형)
	double** tmpInImage = mallocDoubleMemory(inH + 2, inW + 2);
	double** tmpOutImage = mallocDoubleMemory(outH, outW);

	// 임시 입력 메모리를 초기화(127) : 필요시 평균값
	for (int i = 0; i < inH + 2; i++)
		for (int k = 0; k < inW + 2; k++)
			tmpInImage[i][k] = 127;

	// 입력 이미지 --> 임시 입력 이미지
	for (int i = 0; i < inH; i++)
		for (int k = 0; k < inW; k++)
			tmpInImage[i + 1][k + 1] = inImage[i][k];

	// *** 회선 연산 ***
	double S;
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			// 마스크(3x3) 와 한점을 중심으로한 3x3을 곱하기
			S = 0.0; // 마스크 9개와 입력값 9개를 각각 곱해서 합한 값.

			for (int m = 0; m < 3; m++)
				for (int n = 0; n < 3; n++)
					S += tmpInImage[i + m][k + n] * mask[m][n];

			tmpOutImage[i][k] = S;
		}
	}
	// 후처리 (마스크 값의 합계에 따라서...)
	//for (int i = 0; i < outH; i++)
	//	for (int k = 0; k < outW; k++)
	//		tmpOutImage[i][k] += 127.0;

	// 임시 출력 영상--> 출력 영상. 
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

void lap2() { // 화소영역 처리 : 라플라시안(2) 알고리즘
	// 메모리 해제
	freeOutputMemory();
	// (중요!) 출력 이미지의 크기를 결정 ---> 알고리즘에 의존
	outH = inH;
	outW = inW;
	// 메모리 할당	
	mallocOutputMemory();

	////////////////
	// 화소 영역 처리
	/////////////////
	double mask[3][3] = { {1.0, 1.0, 1.0}, // 라플라시안(2) 마스크
						  {1.0, -8.0, 1.0},
						  {1.0, 1.0, 1.0} };
	// 임시 메모리 할당(실수형)
	double** tmpInImage = mallocDoubleMemory(inH + 2, inW + 2);
	double** tmpOutImage = mallocDoubleMemory(outH, outW);

	// 임시 입력 메모리를 초기화(127) : 필요시 평균값
	for (int i = 0; i < inH + 2; i++)
		for (int k = 0; k < inW + 2; k++)
			tmpInImage[i][k] = 127;

	// 입력 이미지 --> 임시 입력 이미지
	for (int i = 0; i < inH; i++)
		for (int k = 0; k < inW; k++)
			tmpInImage[i + 1][k + 1] = inImage[i][k];

	// *** 회선 연산 ***
	double S;
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			// 마스크(3x3) 와 한점을 중심으로한 3x3을 곱하기
			S = 0.0; // 마스크 9개와 입력값 9개를 각각 곱해서 합한 값.

			for (int m = 0; m < 3; m++)
				for (int n = 0; n < 3; n++)
					S += tmpInImage[i + m][k + n] * mask[m][n];

			tmpOutImage[i][k] = S;
		}
	}
	// 후처리 (마스크 값의 합계에 따라서...)
	//for (int i = 0; i < outH; i++)
	//	for (int k = 0; k < outW; k++)
	//		tmpOutImage[i][k] += 127.0;

	// 임시 출력 영상--> 출력 영상. 
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

void lap3() { // 화소영역 처리 : 라플라시안(3) 알고리즘
	// 메모리 해제
	freeOutputMemory();
	// (중요!) 출력 이미지의 크기를 결정 ---> 알고리즘에 의존
	outH = inH;
	outW = inW;
	// 메모리 할당	
	mallocOutputMemory();

	////////////////
	// 화소 영역 처리
	/////////////////
	double mask[3][3] = { {-1.0, -1.0, -1.0}, // 라플라시안(3) 마스크
						  {-1.0, 8.0, -1.0},
						  {-1.0, -1.0, -1.0} };
	// 임시 메모리 할당(실수형)
	double** tmpInImage = mallocDoubleMemory(inH + 2, inW + 2);
	double** tmpOutImage = mallocDoubleMemory(outH, outW);

	// 임시 입력 메모리를 초기화(127) : 필요시 평균값
	for (int i = 0; i < inH + 2; i++)
		for (int k = 0; k < inW + 2; k++)
			tmpInImage[i][k] = 127;

	// 입력 이미지 --> 임시 입력 이미지
	for (int i = 0; i < inH; i++)
		for (int k = 0; k < inW; k++)
			tmpInImage[i + 1][k + 1] = inImage[i][k];

	// *** 회선 연산 ***
	double S;
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			// 마스크(3x3) 와 한점을 중심으로한 3x3을 곱하기
			S = 0.0; // 마스크 9개와 입력값 9개를 각각 곱해서 합한 값.

			for (int m = 0; m < 3; m++)
				for (int n = 0; n < 3; n++)
					S += tmpInImage[i + m][k + n] * mask[m][n];

			tmpOutImage[i][k] = S;
		}
	}
	// 후처리 (마스크 값의 합계에 따라서...)
	//for (int i = 0; i < outH; i++)
	//	for (int k = 0; k < outW; k++)
	//		tmpOutImage[i][k] += 127.0;

	// 임시 출력 영상--> 출력 영상. 
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