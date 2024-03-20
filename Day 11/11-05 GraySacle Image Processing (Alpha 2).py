import random
import math

## 함수부 (공통)
def malloc2D(h, w) :
    memory = [[0 for _ in range(w)] for _ in range(h)]
    return memory

def printImage() :
    global inImage, outImage, inH, inW, outH, outW
    for i in range(outH//2-3, outH//2+3, 1) :
        for k in range(outW//2-3, outW//2+3, 1) :
            print("%3d " % outImage[i][k], end = ' ')
        print()
    print()

## 함수부 (영상처리)
def equalImage() :
    global inImage, outImage, inH, inW, outH, outW
    # (중요!) 출력 이미지 크기 결정 --> 알고리즘에 의존
    outH = inH
    outW = inW
    # 출력 이미지 메모리 확보
    outImage = malloc2D(outH, outW)
    ### 진짜 영상처리 알고리즘 ###
    for i in range(inH) : # for (int i = 0; i < inH; i++)
        for k in range(inW) : # for (int k =0; k < inW; k++)
            outImage[i][k] = inImage[i][k]

    #############################
    printImage()

def addImage() :
    global inImage, outImage, inH, inW, outH, outW
    # (중요!) 출력 이미지 크기 결정 --> 알고리즘에 의존
    outH = inH
    outW = inW
    # 출력 이미지 메모리 확보
    outImage = malloc2D(outH, outW)
    ### 진짜 영상처리 알고리즘 ###
    val = int(input("정수 값 : "))
    for i in range(inH) : # for (int i = 0; i < inH; i++)
        for k in range(inW) : # for (int k =0; k < inW; k++)
            if (inImage[i][k] + val > 255) :
                outImage[i][k] = 255
            else :
                outImage[i][k] = inImage[i][k] + val
    #############################
    printImage()

def subImage() :
    global inImage, outImage, inH, inW, outH, outW
    # (중요!) 출력 이미지 크기 결정 --> 알고리즘에 의존
    outH = inH
    outW = inW
    # 출력 이미지 메모리 확보
    outImage = malloc2D(outH, outW)
    ### 진짜 영상처리 알고리즘 ###
    val = int(input("정수 값 : "))
    for i in range(inH) : # for (int i = 0; i < inH; i++)
        for k in range(inW) : # for (int k =0; k < inW; k++)
            if (inImage[i][k] - val < 0) :
                outImage[i][k] = 0
            else :
                outImage[i][k] = inImage[i][k] - val
    #############################
    printImage()

def revImage() :
    global inImage, outImage, inH, inW, outH, outW
    # (중요!) 출력 이미지 크기 결정 --> 알고리즘에 의존
    outH = inH
    outW = inW
    # 출력 이미지 메모리 확보
    outImage = malloc2D(outH, outW)
    ### 진짜 영상처리 알고리즘 ###
    for i in range(inH) : # for (int i = 0; i < inH; i++)
        for k in range(inW) : # for (int k =0; k < inW; k++)
            outImage[i][k] = 255 - inImage[i][k]

    #############################
    printImage()

def bwImage() :
    global inImage, outImage, inH, inW, outH, outW
    # (중요!) 출력 이미지 크기 결정 --> 알고리즘에 의존
    outH = inH
    outW = inW
    # 출력 이미지 메모리 확보
    outImage = malloc2D(outH, outW)
    ### 진짜 영상처리 알고리즘 ###
    for i in range(inH) : # for (int i = 0; i < inH; i++)
        for k in range(inW) : # for (int k =0; k < inW; k++)
            if (inImage[i][k] < 127) :
                outImage[i][k] = 0
            else :
                outImage[i][k] = 255

    #############################
    printImage()

def avgbwImage() :
    global inImage, outImage, inH, inW, outH, outW
    # (중요!) 출력 이미지 크기 결정 --> 알고리즘에 의존
    outH = inH
    outW = inW
    # 출력 이미지 메모리 확보
    outImage = malloc2D(outH, outW)
    ### 진짜 영상처리 알고리즘 ###
    avg, hap = 0, 0
    for i in range(inH) :
        for k in range(inW) :
            hap += inImage[i][k]
    avg = hap / (inH * inW)
    print(avg)
    for i in range(inH) : # for (int i = 0; i < inH; i++)
        for k in range(inW) : # for (int k =0; k < inW; k++)
            if (inImage[i][k] < avg) :
                outImage[i][k] = 0
            else :
                outImage[i][k] = 255

    #############################
    printImage()

def medbwImage() :
    global inImage, outImage, inH, inW, outH, outW
    # (중요!) 출력 이미지 크기 결정 --> 알고리즘에 의존
    outH = inH
    outW = inW
    # 출력 이미지 메모리 확보
    outImage = malloc2D(outH, outW)
    ### 진짜 영상처리 알고리즘 ###
    med, cnt = 0, 0
    arr = []
    for i in range(inH) :
        for k in range(inW) :
            arr.append(inImage[i][k])
    #print(arr)
    sortarr = sorted(arr)
    med = sortarr[int((inH * inW) / 2)]
    print(med)
    for i in range(inH) : # for (int i = 0; i < inH; i++)
        for k in range(inW) : # for (int k =0; k < inW; k++)
            if (inImage[i][k] < med) :
                outImage[i][k] = 0
            else :
                outImage[i][k] = 255

    #############################
    printImage()

def gammaImage() :
    global inImage, outImage, inH, inW, outH, outW
    # (중요!) 출력 이미지 크기 결정 --> 알고리즘에 의존
    outH = inH
    outW = inW
    # 출력 이미지 메모리 확보
    outImage = malloc2D(outH, outW)
    ### 진짜 영상처리 알고리즘 ###
    gamma = float(input("감마 값 : "))
    for i in range(inH) : # for (int i = 0; i < inH; i++)
        for k in range(inW) : # for (int k =0; k < inW; k++)
            outImage[i][k] = 255 * ((inImage[i][k]/ 255) ** 1 / gamma)

    #############################
    printImage()

def CAPparaImage() :
    global inImage, outImage, inH, inW, outH, outW
    # (중요!) 출력 이미지 크기 결정 --> 알고리즘에 의존
    outH = inH
    outW = inW
    # 출력 이미지 메모리 확보
    outImage = malloc2D(outH, outW)
    ### 진짜 영상처리 알고리즘 ###
    for i in range(inH) : # for (int i = 0; i < inH; i++)
        for k in range(inW) : # for (int k =0; k < inW; k++)
            outImage[i][k] = 255 * ((inImage[i][k]/127 - 1) ** 2)

    #############################
    printImage()

def CUPparaImage() :
    global inImage, outImage, inH, inW, outH, outW
    # (중요!) 출력 이미지 크기 결정 --> 알고리즘에 의존
    outH = inH
    outW = inW
    # 출력 이미지 메모리 확보
    outImage = malloc2D(outH, outW)
    ### 진짜 영상처리 알고리즘 ###
    for i in range(inH) : # for (int i = 0; i < inH; i++)
        for k in range(inW) : # for (int k =0; k < inW; k++)
            outImage[i][k] = 255 - 255 * ((inImage[i][k]/127 - 1) ** 2)

    #############################
    printImage()

def posterImage() :
    global inImage, outImage, inH, inW, outH, outW
    # (중요!) 출력 이미지 크기 결정 --> 알고리즘에 의존
    outH = inH
    outW = inW
    # 출력 이미지 메모리 확보
    outImage = malloc2D(outH, outW)
    ### 진짜 영상처리 알고리즘 ###
    for i in range(inH) : # for (int i = 0; i < inH; i++)
        for k in range(inW) : # for (int k =0; k < inW; k++)
            if (inImage[i][k] <= 0) :
                outImage[i][k] = 0
            elif (0 < inImage[i][k] and inImage[i][k] <= 32) :
                outImage[i][k] = 16
            elif (32 < inImage[i][k] and inImage[i][k] <= 64) :
                outImage[i][k] = 48
            elif (64 < inImage[i][k] and inImage[i][k] <=96) :
                outImage[i][k] = 80
            elif (96 < inImage[i][k] and inImage[i][k] <= 128) :
                outImage[i][k] = 112
            elif (128 < inImage[i][k] and inImage[i][k] <= 160) :
                outImage[i][k] = 144
            elif (160 < inImage[i][k] and inImage[i][k] <= 192) :
                outImage[i][k] = 176
            elif (192 < inImage[i][k] and inImage[i][k] <= 224) :
                outImage[i][k] = 208
            elif (224 < inImage[i][k] and inImage[i][k] <= 255) :
                outImage[i][k] = 240

    #############################
    printImage()

def stressImage() :
    global inImage, outImage, inH, inW, outH, outW
    # (중요!) 출력 이미지 크기 결정 --> 알고리즘에 의존
    outH = inH
    outW = inW
    # 출력 이미지 메모리 확보
    outImage = malloc2D(outH, outW)
    ### 진짜 영상처리 알고리즘 ###
    start = int(input("시작 값 : "))
    end = int(input("끝 값 : "))
    for i in range(inH) : # for (int i = 0; i < inH; i++)
        for k in range(inW) : # for (int k =0; k < inW; k++)
            if (start <= inImage[i][k] and inImage[i][k] <= end) :
                outImage[i][k] = 255
            else :
                outImage[i][k] = inImage[i][k]

    #############################
    printImage()

def zoutImage() :
    global inImage, outImage, inH, inW, outH, outW
    # (중요!) 출력 이미지 크기 결정 --> 알고리즘에 의존
    scale = int(input("축소 값 : "))
    outH = int(inH / scale)
    outW = int(inW / scale)
    # 출력 이미지 메모리 확보
    outImage = malloc2D(outH, outW)
    ### 진짜 영상처리 알고리즘 ###
    for i in range(inH) : # for (int i = 0; i < inH; i++)
        for k in range(inW) : # for (int k =0; k < inW; k++)
            outImage[int(i / scale)][int(k / scale)] = inImage[i][k]

    #############################
    printImage()

def zinImage() :
    global inImage, outImage, inH, inW, outH, outW
    # (중요!) 출력 이미지 크기 결정 --> 알고리즘에 의존
    scale = int(input("확대 값 : "))
    outH = int(inH * scale)
    outW = int(inW * scale)
    # 출력 이미지 메모리 확보
    outImage = malloc2D(outH, outW)
    ### 진짜 영상처리 알고리즘 ###
    for i in range(inH) : # for (int i = 0; i < inH; i++)
        for k in range(inW) : # for (int k =0; k < inW; k++)
            outImage[int(i * scale)][int(k * scale)] = inImage[i][k]

    #############################
    printImage()

def zinImage2() :
    global inImage, outImage, inH, inW, outH, outW
    # (중요!) 출력 이미지 크기 결정 --> 알고리즘에 의존
    scale = int(input("확대 값 : "))
    outH = int(inH * scale)
    outW = int(inW * scale)
    # 출력 이미지 메모리 확보
    outImage = malloc2D(outH, outW)
    ### 진짜 영상처리 알고리즘 ###
    for i in range(inH) : # for (int i = 0; i < inH; i++)
        for k in range(inW) : # for (int k =0; k < inW; k++)
            outImage[i][k] = inImage[int(i / scale)][int(k / scale)]

    #############################
    printImage()

def rotImage() :
    global inImage, outImage, inH, inW, outH, outW
    # (중요!) 출력 이미지 크기 결정 --> 알고리즘에 의존
    outH = inH
    outW = inW
    # 출력 이미지 메모리 확보
    outImage = malloc2D(outH, outW)
    ### 진짜 영상처리 알고리즘 ###
    degree = int(input("각도 값 : "))
    radian = float(degree * 3.141592 / 180.0)
    for i in range(inH) : # for (int i = 0; i < inH; i++)
        for k in range(inW) : # for (int k =0; k < inW; k++)
            xs = i
            ys = k
            xd = int(math.cos(radian) * xs - math.sin(radian) * ys)
            yd = int(math.sin(radian) * xs + math.cos(radian) * ys)
            if ((0 <= xd and xd < outH) and (0 <= yd and yd < outW)) :
                outImage[xd][yd] = inImage[xs][ys]

    #############################
    printImage()

def rotImage2() :
    global inImage, outImage, inH, inW, outH, outW
    # (중요!) 출력 이미지 크기 결정 --> 알고리즘에 의존
    outH = inH
    outW = inW
    # 출력 이미지 메모리 확보
    outImage = malloc2D(outH, outW)
    ### 진짜 영상처리 알고리즘 ###
    degree = int(input("각도 값 : "))
    radian = float(degree * 3.141592 / 180.0)
    cx = int(inH / 2)
    cy = int(inW / 2)
    for i in range(inH) : # for (int i = 0; i < inH; i++)
        for k in range(inW) : # for (int k =0; k < inW; k++)
            xd = i
            yd = k
            xs = int(math.cos(radian) * (xd - cx) + math.sin(radian) * (yd - cy))
            ys = int(-math.sin(radian) * (xd - cx) + math.cos(radian) * (yd - cy))
            xs += cx
            ys += cy
            if ((0 <= xd and xd < outH) and (0 <= yd and yd < outW)) :
                outImage[xd][yd] = inImage[xs][ys]

    #############################
    printImage()

def moveImage() :
    global inImage, outImage, inH, inW, outH, outW
    # (중요!) 출력 이미지 크기 결정 --> 알고리즘에 의존
    outH = inH
    outW = inW
    # 출력 이미지 메모리 확보
    outImage = malloc2D(outH, outW)
    ### 진짜 영상처리 알고리즘 ###
    x = int(input("x 값 : "))
    y = int(input("y 값 : "))
    for i in range(inH) : # for (int i = 0; i < inH; i++)
        for k in range(inW) : # for (int k =0; k < inW; k++)
            if ((0 <= x + k and x + k < inH) and (0 <= y + i and y + i < inW)) :
                outImage[i + y][k + x] = inImage[i][k]

    #############################
    printImage()


## 변수부
inImage, outImage = [], []
inH, inW, outH, outW = [0] * 4

## 메인부
# 1. 파일 --> 메모리
# 1-1. 이미지 크기 계산
inH = int(input("입력 이미지 높이(128, 256, 512...) : "))
inW = int(input("입력 이미지 폭(128, 256, 512... : "))
# 1-2. 메모리 할당
inImage = malloc2D(inH, inW)
# 1-3. 파일을 읽어서 메모리로 로딩
for i in range(inH) :
    for k in range(inW) :
        px = random.randint(0, 255)
        inImage[i][k] = px
print("동일 이미지")
equalImage()
print("밝게 하기")
addImage()
print("어둡게 하기")
subImage()
print("반전 이미지")
revImage()
print("흑백 이미지(127 기준)")
bwImage()
print("흑백 이미지(평균값)")
avgbwImage()
print("흑백 이미지(중앙값)")
medbwImage()
print("감마 이미지")
gammaImage()
print("CAP파라볼라 이미지")
CAPparaImage()
print("CUP파라볼라 이미지")
CUPparaImage()
print("포스터라이징 이미지")
posterImage()
print("범위 강조 이미지")
stressImage()
print("축소 이미지")
zoutImage()
print("확대(포워딩) 이미지")
zinImage()
print("확대(백워딩) 이미지")
zinImage2()
print("회전(기본) 이미지")
rotImage()
print("회전(중앙, 백워딩) 이미지")
rotImage2()
print("이미지 이동")
moveImage()

## 미션 : C언어의 화소점 처리/화소영역 처리/기하학 처리/히스토그램 처리 등
## 함수 구현하기

