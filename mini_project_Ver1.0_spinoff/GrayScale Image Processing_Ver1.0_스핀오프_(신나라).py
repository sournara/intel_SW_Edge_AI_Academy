from tkinter import *
from tkinter import messagebox
from tkinter.filedialog import *
import os.path
import math
from tkinter.simpledialog import *


### 함수부
# ***************************
# 공통 함수부
# ***************************
def malloc2D(h, w, initValue=0):
    memory = [[initValue for _ in range(w)] for _ in range(h)]
    return memory


def openImage():
    global window, canvas, paper
    global inImage, outImage, inH, inW, outH, outW
    fullname = askopenfilename(parent=window,
                               filetypes=(("RAW파일", "*.raw"), ("모든파일", "*.*")))
    # 중요 ! 입력 이미지 크기를 결정
    fsize = os.path.getsize(fullname)  # 파일 크기(Byte)
    inH = inW = int(math.sqrt(fsize))
    # 메모리 할당
    inImage = malloc2D(inH, inW)
    # 파일 --> 메모리
    rfp = open(fullname, 'rb')
    for i in range(inH):
        for k in range(inW):
            inImage[i][k] = ord(rfp.read(1))

    rfp.close()
    equalImage()


def saveImage():
    global window, canvas, paper
    global inImage, outImage, inH, inW, outH, outW

    if (outImage == None or len(outImage) == 0):  # 영상처리를 한 적이 없다면...
        return
    wfp = asksaveasfile(parent=window, mode='wb', defaultextension="*.raw",
                        filetypes=(("RAW파일", "*.raw"), ("모든파일", "*.*")))
    import struct
    for i in range(outH):
        for k in range(outW):
            wfp.write(struct.pack('B', outImage[i][k]))
    wfp.close()
    messagebox.showinfo("성공", wfp.name + " 저장완료!")


def displayImage():
    global window, canvas, paper
    global inImage, outImage, inH, inW, outH, outW

    # 기존의 이미지를 오픈한 적이 있으면, 캔버스 뜯어내기
    if (canvas != None):
        canvas.destroy()

    # 벽, 캔버스, 종이 설정
    window.geometry(str(outH) + 'x' + str(outW))  # "512x512"
    canvas = Canvas(window, height=outH, width=outW, bg="yellow")  # 칠판
    paper = PhotoImage(height=outH, width=outW)  # 종이
    canvas.create_image((outH // 2, outW // 2), image=paper, state="normal")

    # 메모리 --> 화면
    # for i in range(outH) :
    #     for k in range(outW) :
    #         r = g = b = outImage[i][k]
    #         paper.put("#%02x%02x%02x" % (r, g, b), (k, i))

    # 더블 버퍼링... 비슷한 기법 (모두 다 메모리상에 생성한 후에, 한방에 출력)
    rgbString = ""  # 전체에 대한 16진수 문자열
    for i in range(outH):
        oneString = ""  # 한 줄에 대한 16진수 문자열
        for k in range(outW):
            r = g = b = outImage[i][k]
            oneString += "#%02x%02x%02x " % (r, g, b)
        rgbString += '{' + oneString + '} '
    paper.put(rgbString)

    canvas.pack()


# ***************************
# 영상처리 함수부
# ***************************
def equalImage():  # 동일 이미지
    global window, canvas, paper
    global inImage, outImage, inH, inW, outH, outW
    # 중요! 출력 영상 크기 결정 --> 알고리즘에 의존
    outH = inH
    outW = inW
    # 메모리 할당
    outImage = malloc2D(outH, outW)
    ### 진짜 영상처리 알고리즘 ###
    for i in range(inH):
        for k in range(inW):
            outImage[i][k] = inImage[i][k]
    displayImage()


def addImage():  # 밝게 / 어둡게
    global window, canvas, paper
    global inImage, outImage, inH, inW, outH, outW
    # 중요! 출력 영상 크기 결정 --> 알고리즘에 의존
    outH = inH
    outW = inW
    # 메모리 할당
    outImage = malloc2D(outH, outW)
    ### 진짜 영상처리 알고리즘 ###
    value = askinteger("정수 입력", "-255~255 입력", maxvalue=255, minvalue=-255)
    for i in range(inH):
        for k in range(inW):
            px = inImage[i][k] + value
            if (px > 255):
                px = 255
            if (px < 0):
                px = 0
            outImage[i][k] = px
    displayImage()

def andImage() :
    global window, canvas, paper
    global inImage, outImage, inH, inW, outH, outW
    # 중요! 출력 영상 크기 결정 --> 알고리즘에 의존
    outH = inH
    outW = inW
    # 메모리 할당
    outImage = malloc2D(outH, outW)
    ### 진짜 영상처리 알고리즘 ###
    value = askinteger("정수 입력", "정수 입력")
    for i in range(inH):
        for k in range(inW):
            px = inImage[i][k] & value
            if (px > 255):
                px = 255
            if (px < 0):
                px = 0
            outImage[i][k] = px
    displayImage()

def orImage() :
    global window, canvas, paper
    global inImage, outImage, inH, inW, outH, outW
    # 중요! 출력 영상 크기 결정 --> 알고리즘에 의존
    outH = inH
    outW = inW
    # 메모리 할당
    outImage = malloc2D(outH, outW)
    ### 진짜 영상처리 알고리즘 ###
    value = askinteger("정수 입력", "정수 입력")
    for i in range(inH):
        for k in range(inW):
            px = inImage[i][k] | value
            if (px > 255):
                px = 255
            if (px < 0):
                px = 0
            outImage[i][k] = px
    displayImage()

def xorImage() :
    global window, canvas, paper
    global inImage, outImage, inH, inW, outH, outW
    # 중요! 출력 영상 크기 결정 --> 알고리즘에 의존
    outH = inH
    outW = inW
    # 메모리 할당
    outImage = malloc2D(outH, outW)
    ### 진짜 영상처리 알고리즘 ###
    value = askinteger("정수 입력", "정수 입력")
    for i in range(inH):
        for k in range(inW):
            px = inImage[i][k] ^ value
            if (px > 255):
                px = 255
            if (px < 0):
                px = 0
            outImage[i][k] = px
    displayImage()

def revImage():
    global window, canvas, paper
    global inImage, outImage, inH, inW, outH, outW
    # (중요!) 출력 이미지 크기 결정 --> 알고리즘에 의존
    outH = inH
    outW = inW
    # 출력 이미지 메모리 확보
    outImage = malloc2D(outH, outW)
    ### 진짜 영상처리 알고리즘 ###
    for i in range(inH):  # for (int i = 0; i < inH; i++)
        for k in range(inW):  # for (int k =0; k < inW; k++)
            outImage[i][k] = 255 - inImage[i][k]

    #############################
    displayImage()


def bwImage():
    global window, canvas, paper
    global inImage, outImage, inH, inW, outH, outW
    # (중요!) 출력 이미지 크기 결정 --> 알고리즘에 의존
    outH = inH
    outW = inW
    # 출력 이미지 메모리 확보
    outImage = malloc2D(outH, outW)
    ### 진짜 영상처리 알고리즘 ###
    for i in range(inH):  # for (int i = 0; i < inH; i++)
        for k in range(inW):  # for (int k =0; k < inW; k++)
            if (inImage[i][k] < 127):
                outImage[i][k] = 0
            else:
                outImage[i][k] = 255

    #############################
    displayImage()


def avgbwImage():
    global window, canvas, paper
    global inImage, outImage, inH, inW, outH, outW
    # (중요!) 출력 이미지 크기 결정 --> 알고리즘에 의존
    outH = inH
    outW = inW
    # 출력 이미지 메모리 확보
    outImage = malloc2D(outH, outW)
    ### 진짜 영상처리 알고리즘 ###
    avg, hap = 0, 0
    for i in range(inH):
        for k in range(inW):
            hap += inImage[i][k]
    avg = hap / (inH * inW)
    print(avg)
    for i in range(inH):  # for (int i = 0; i < inH; i++)
        for k in range(inW):  # for (int k =0; k < inW; k++)
            if (inImage[i][k] < avg):
                outImage[i][k] = 0
            else:
                outImage[i][k] = 255

    #############################
    displayImage()


def medbwImage():
    global window, canvas, paper
    global inImage, outImage, inH, inW, outH, outW
    # (중요!) 출력 이미지 크기 결정 --> 알고리즘에 의존
    outH = inH
    outW = inW
    # 출력 이미지 메모리 확보
    outImage = malloc2D(outH, outW)
    ### 진짜 영상처리 알고리즘 ###
    med, cnt = 0, 0
    arr = []
    for i in range(inH):
        for k in range(inW):
            arr.append(inImage[i][k])
    # print(arr)
    sortarr = sorted(arr)
    med = sortarr[int((inH * inW) / 2)]
    print(med)
    for i in range(inH):  # for (int i = 0; i < inH; i++)
        for k in range(inW):  # for (int k =0; k < inW; k++)
            if (inImage[i][k] < med):
                outImage[i][k] = 0
            else:
                outImage[i][k] = 255

    #############################
    displayImage()


def gammaImage():
    global window, canvas, paper
    global inImage, outImage, inH, inW, outH, outW
    # (중요!) 출력 이미지 크기 결정 --> 알고리즘에 의존
    outH = inH
    outW = inW
    # 출력 이미지 메모리 확보
    outImage = malloc2D(outH, outW)
    ### 진짜 영상처리 알고리즘 ###
    gamma = askfloat("실수 입력", "실수 입력")
    for i in range(inH):  # for (int i = 0; i < inH; i++)
        for k in range(inW):  # for (int k =0; k < inW; k++)
            outImage[i][k] = int(255 * ((inImage[i][k] / 255) ** 1 / gamma))

    #############################
    displayImage()


def CAPparaImage():
    global window, canvas, paper
    global inImage, outImage, inH, inW, outH, outW
    # (중요!) 출력 이미지 크기 결정 --> 알고리즘에 의존
    outH = inH
    outW = inW
    # 출력 이미지 메모리 확보
    outImage = malloc2D(outH, outW)
    ### 진짜 영상처리 알고리즘 ###
    for i in range(inH):  # for (int i = 0; i < inH; i++)
        for k in range(inW):  # for (int k =0; k < inW; k++)
            outImage[i][k] = int(255 * ((inImage[i][k] / 127 - 1) ** 2))

    #############################
    displayImage()


def CUPparaImage():
    global window, canvas, paper
    global inImage, outImage, inH, inW, outH, outW
    # (중요!) 출력 이미지 크기 결정 --> 알고리즘에 의존
    outH = inH
    outW = inW
    # 출력 이미지 메모리 확보
    outImage = malloc2D(outH, outW)
    ### 진짜 영상처리 알고리즘 ###
    for i in range(inH):  # for (int i = 0; i < inH; i++)
        for k in range(inW):  # for (int k =0; k < inW; k++)
            outImage[i][k] = int(255 - 255 * ((inImage[i][k] / 127 - 1) ** 2))

    #############################
    displayImage()


def posterImage():
    global window, canvas, paper
    global inImage, outImage, inH, inW, outH, outW
    # (중요!) 출력 이미지 크기 결정 --> 알고리즘에 의존
    outH = inH
    outW = inW
    # 출력 이미지 메모리 확보
    outImage = malloc2D(outH, outW)
    ### 진짜 영상처리 알고리즘 ###
    for i in range(inH):  # for (int i = 0; i < inH; i++)
        for k in range(inW):  # for (int k =0; k < inW; k++)
            if (inImage[i][k] <= 0):
                outImage[i][k] = 0
            elif (0 < inImage[i][k] <= 32):
                outImage[i][k] = 16
            elif (32 < inImage[i][k] <= 64):
                outImage[i][k] = 48
            elif (64 < inImage[i][k] <= 96):
                outImage[i][k] = 80
            elif (96 < inImage[i][k] <= 128):
                outImage[i][k] = 112
            elif (128 < inImage[i][k] <= 160):
                outImage[i][k] = 144
            elif (160 < inImage[i][k] <= 192):
                outImage[i][k] = 176
            elif (192 < inImage[i][k] <= 224):
                outImage[i][k] = 208
            elif (224 < inImage[i][k] <= 255):
                outImage[i][k] = 240

    #############################
    displayImage()


def stressImage():
    global window, canvas, paper
    global inImage, outImage, inH, inW, outH, outW
    # (중요!) 출력 이미지 크기 결정 --> 알고리즘에 의존
    outH = inH
    outW = inW
    # 출력 이미지 메모리 확보
    outImage = malloc2D(outH, outW)
    ### 진짜 영상처리 알고리즘 ###
    start = askinteger("시작 값 입력", "정수 시작 값 입력")
    end = askinteger("끝 값 입력", "정수 끝 값 입력")
    for i in range(inH):  # for (int i = 0; i < inH; i++)
        for k in range(inW):  # for (int k =0; k < inW; k++)
            if (start <= inImage[i][k] <= end):
                outImage[i][k] = 255
            else:
                outImage[i][k] = inImage[i][k]

    #############################
    displayImage()

def zoutImage():
    global window, canvas, paper
    global inImage, outImage, inH, inW, outH, outW
    # (중요!) 출력 이미지 크기 결정 --> 알고리즘에 의존
    scale = askinteger("축소 입력", "축소 정수 값 입력")
    outH = int(inH / scale)
    outW = int(inW / scale)
    # 출력 이미지 메모리 확보
    outImage = malloc2D(outH, outW)
    ### 진짜 영상처리 알고리즘 ###
    for i in range(inH):  # for (int i = 0; i < inH; i++)
        for k in range(inW):  # for (int k =0; k < inW; k++)
            outImage[int(i / scale)][int(k / scale)] = inImage[i][k]

    #############################
    displayImage()


def zinImage():
    global window, canvas, paper
    global inImage, outImage, inH, inW, outH, outW
    # (중요!) 출력 이미지 크기 결정 --> 알고리즘에 의존
    scale = askinteger("확대 입력", "확대 정수 값 입력")
    outH = int(inH * scale)
    outW = int(inW * scale)
    # 출력 이미지 메모리 확보
    outImage = malloc2D(outH, outW)
    ### 진짜 영상처리 알고리즘 ###
    for i in range(inH):  # for (int i = 0; i < inH; i++)
        for k in range(inW):  # for (int k =0; k < inW; k++)
            outImage[int(i * scale)][int(k * scale)] = inImage[i][k]

    #############################
    displayImage()


def zinImage2():
    global window, canvas, paper
    global inImage, outImage, inH, inW, outH, outW
    # (중요!) 출력 이미지 크기 결정 --> 알고리즘에 의존
    scale = askinteger("확대 입력", "확대 정수 값 입력")
    outH = int(inH * scale)
    outW = int(inW * scale)
    # 출력 이미지 메모리 확보
    outImage = malloc2D(outH, outW)
    ### 진짜 영상처리 알고리즘 ###
    for i in range(outH):  # for (int i = 0; i < inH; i++)
        for k in range(outW):  # for (int k =0; k < inW; k++)
            outImage[i][k] = inImage[int(i / scale)][int(k / scale)]

    #############################
    displayImage()


def rotImage():
    global window, canvas, paper
    global inImage, outImage, inH, inW, outH, outW
    # (중요!) 출력 이미지 크기 결정 --> 알고리즘에 의존
    outH = inH
    outW = inW
    # 출력 이미지 메모리 확보
    outImage = malloc2D(outH, outW)
    ### 진짜 영상처리 알고리즘 ###
    degree = askinteger("각도 입력", "각도 정수 값 입력")
    radian = float(degree * 3.141592 / 180.0)
    for i in range(inH):  # for (int i = 0; i < inH; i++)
        for k in range(inW):  # for (int k =0; k < inW; k++)
            xs = i
            ys = k
            xd = int(math.cos(radian) * xs - math.sin(radian) * ys)
            yd = int(math.sin(radian) * xs + math.cos(radian) * ys)
            if ((0 <= xd < outH) and (0 <= yd < outW)):
                outImage[xd][yd] = inImage[xs][ys]

    #############################
    displayImage()


def rotImage2():
    global window, canvas, paper
    global inImage, outImage, inH, inW, outH, outW
    # (중요!) 출력 이미지 크기 결정 --> 알고리즘에 의존
    outH = inH
    outW = inW
    # 출력 이미지 메모리 확보
    outImage = malloc2D(outH, outW)
    ### 진짜 영상처리 알고리즘 ###
    degree = askinteger("각도 입력", "각도 정수 값 입력")
    radian = float(degree * 3.141592 / 180.0)
    cx = int(inH / 2)
    cy = int(inW / 2)
    for i in range(inH):  # for (int i = 0; i < inH; i++)
        for k in range(inW):  # for (int k =0; k < inW; k++)
            xd = i
            yd = k
            xs = int(math.cos(radian) * (xd - cx) + math.sin(radian) * (yd - cy))
            ys = int(-math.sin(radian) * (xd - cx) + math.cos(radian) * (yd - cy))
            xs += cx
            ys += cy
            if ((0 <= xs < outH) and (0 <= ys < outW)):
                outImage[xd][yd] = inImage[xs][ys]

    #############################
    displayImage()


def moveImage():
    global window, canvas, paper
    global inImage, outImage, inH, inW, outH, outW
    # (중요!) 출력 이미지 크기 결정 --> 알고리즘에 의존
    outH = inH
    outW = inW
    # 출력 이미지 메모리 확보
    outImage = malloc2D(outH, outW)
    ### 진짜 영상처리 알고리즘 ###
    x = askinteger("x 입력", "x 정수 값 입력")
    y = askinteger("y 입력", "y 정수 값 입력")
    for i in range(inH):  # for (int i = 0; i < inH; i++)
        for k in range(inW):  # for (int k =0; k < inW; k++)
            if ((0 <= x + k < inH) and (0 <= y + i < inW)):
                outImage[i + y][k + x] = inImage[i][k]

    #############################
    displayImage()


def mirrorLR():
    global window, canvas, paper
    global inImage, outImage, inH, inW, outH, outW
    # (중요!) 출력 이미지 크기 결정 --> 알고리즘에 의존
    outH = inH
    outW = inW
    # 출력 이미지 메모리 확보
    outImage = malloc2D(outH, outW)
    ### 진짜 영상처리 알고리즘 ###
    for i in range(inH):  # for (int i = 0; i < inH; i++)
        for k in range(inW):  # for (int k =0; k < inW; k++)
            outImage[i][k] = inImage[i][inW - k - 1]

    #############################
    displayImage()


def mirrorUD():
    global window, canvas, paper
    global inImage, outImage, inH, inW, outH, outW
    # (중요!) 출력 이미지 크기 결정 --> 알고리즘에 의존
    outH = inH
    outW = inW
    # 출력 이미지 메모리 확보
    outImage = malloc2D(outH, outW)
    ### 진짜 영상처리 알고리즘 ###
    for i in range(inH):  # for (int i = 0; i < inH; i++)
        for k in range(inW):  # for (int k =0; k < inW; k++)
            outImage[i][k] = inImage[inH - 1 - i][k]

    #############################
    displayImage()


def mirrorALL():
    global window, canvas, paper
    global inImage, outImage, inH, inW, outH, outW
    # (중요!) 출력 이미지 크기 결정 --> 알고리즘에 의존
    outH = inH
    outW = inW
    # 출력 이미지 메모리 확보
    outImage = malloc2D(outH, outW)
    ### 진짜 영상처리 알고리즘 ###
    for i in range(inH):  # for (int i = 0; i < inH; i++)
        for k in range(inW):  # for (int k =0; k < inW; k++)
            outImage[i][k] = inImage[inH - 1 - i][inW - k - 1]

    #############################
    displayImage()


def histoStretch():
    global window, canvas, paper
    global inImage, outImage, inH, inW, outH, outW
    # (중요!) 출력 이미지 크기 결정 --> 알고리즘에 의존
    outH = inH
    outW = inW
    # 출력 이미지 메모리 확보
    outImage = malloc2D(outH, outW)
    ### 진짜 영상처리 알고리즘 ###
    high = inImage[0][0]
    low = inImage[0][0]
    for i in range(inH):  # for (int i = 0; i < inH; i++)
        for k in range(inW):  # for (int k =0; k < inW; k++)
            if (inImage[i][k] < low):
                low = inImage[i][k]
            if (inImage[i][k] > high):
                high = inImage[i][k]
    old, new = 0, 0
    for i in range(inH):
        for k in range(inW):
            old = inImage[i][k]
            new = int(float(old - low) / float(high - low) * 255.0)
            if (new > 255):
                new = 255
            if (new < 0):
                new = 0
            outImage[i][k] = new

    #############################
    displayImage()


def endIn():
    global window, canvas, paper
    global inImage, outImage, inH, inW, outH, outW
    # (중요!) 출력 이미지 크기 결정 --> 알고리즘에 의존
    outH = inH
    outW = inW
    # 출력 이미지 메모리 확보
    outImage = malloc2D(outH, outW)
    ### 진짜 영상처리 알고리즘 ###
    high = inImage[0][0]
    low = inImage[0][0]
    for i in range(inH):  # for (int i = 0; i < inH; i++)
        for k in range(inW):  # for (int k =0; k < inW; k++)
            if (inImage[i][k] < low):
                low = inImage[i][k]
            if (inImage[i][k] > high):
                high = inImage[i][k]

    high -= 50
    low += 50

    old, new = 0, 0
    for i in range(inH):
        for k in range(inW):
            old = inImage[i][k]
            new = int(float(old - low) / float(high - low) * 255.0)
            if (new > 255):
                new = 255
            if (new < 0):
                new = 0
            outImage[i][k] = new
    #############################
    displayImage()


def histoEqual():
    global window, canvas, paper
    global inImage, outImage, inH, inW, outH, outW
    # (중요!) 출력 이미지 크기 결정 --> 알고리즘에 의존
    outH = inH
    outW = inW
    # 출력 이미지 메모리 확보
    outImage = malloc2D(outH, outW)
    ### 진짜 영상처리 알고리즘 ###
    # 1단계 : 빈도수 세기 (= 히스토그램)
    histo = []
    for _ in range(256):
        histo.append(0)
    for i in range(inH):  # for (int i = 0; i < inH; i++)
        for k in range(inW):  # for (int k =0; k < inW; k++)
            histo[inImage[i][k]] += 1
    # 2단계 : 누적 히스토그램 생성
    sumHisto = []
    for _ in range(256):
        sumHisto.append(0)
    sumHisto[0] = histo[0]
    for i in range(256):
        sumHisto[i] = sumHisto[i - 1] + histo[i]
    # 3단계 : 정규화된 히스토그램 생성
    normalHisto = []
    for _ in range(256):
        normalHisto.append(0)
    for i in range(256):
        normalHisto[i] = sumHisto[i] * (1 / (inH * inW)) * 255
    # 4단계 : inImage를 정규화된 값으로 치환
    for i in range(inH):
        for k in range(inW):
            outImage[i][k] = int(normalHisto[inImage[i][k]])

    #############################
    displayImage()


def emboss():
    global window, canvas, paper
    global inImage, outImage, inH, inW, outH, outW
    # (중요!) 출력 이미지 크기 결정 --> 알고리즘에 의존
    outH = inH
    outW = inW
    # 출력 이미지 메모리 확보
    outImage = malloc2D(outH, outW)
    ### 진짜 영상처리 알고리즘 ###
    mask = [[-1.0, 0.0, 0.0], [0.0, 0.0, 0.0], [0.0, 0.0, 1.0]]
    tmpInImage = malloc2D(inH + 2, inW + 2)
    tmpOutImage = malloc2D(outH, outW)
    for i in range(inH + 2):  # for (int i = 0; i < inH; i++)
        for k in range(inW + 2):  # for (int k =0; k < inW; k++)
            tmpInImage[i][k] = 127
    for i in range(inH):  # for (int i = 0; i < inH; i++)
        for k in range(inW):  # for (int k =0; k < inW; k++)
            tmpInImage[i + 1][k + 1] = inImage[i][k]
    S = 0
    # 회선 연산
    for i in range(inH):
        for k in range(inW):
            S = 0.0
            for m in range(3):
                for n in range(3):
                    S += tmpInImage[i + m][k + n] * mask[m][n]
            tmpOutImage[i][k] = S

    # 후처리
    for i in range(outH):
        for k in range(outW):
            tmpOutImage[i][k] += 127.0
    for i in range(outH):
        for k in range(outW):
            if (tmpOutImage[i][k] < 0.0):
                outImage[i][k] = 0
            elif (tmpOutImage[i][k] > 255.0):
                outImage[i][k] = 255
            else:
                outImage[i][k] = int(tmpOutImage[i][k])

    #############################
    displayImage()


def blur():
    global window, canvas, paper
    global inImage, outImage, inH, inW, outH, outW
    # (중요!) 출력 이미지 크기 결정 --> 알고리즘에 의존
    outH = inH
    outW = inW
    # 출력 이미지 메모리 확보
    outImage = malloc2D(outH, outW)
    ### 진짜 영상처리 알고리즘 ###
    mask = [[1 / 9, 1 / 9, 1 / 9], [1 / 9, 1 / 9, 1 / 9], [1 / 9, 1 / 9, 1 / 9]]
    tmpInImage = malloc2D(inH + 2, inW + 2)
    tmpOutImage = malloc2D(outH, outW)
    for i in range(inH):  # for (int i = 0; i < inH; i++)
        for k in range(inW):  # for (int k =0; k < inW; k++)
            tmpInImage[i][k] = 127
    for i in range(inH):  # for (int i = 0; i < inH; i++)
        for k in range(inW):  # for (int k =0; k < inW; k++)
            tmpInImage[i + 1][k + 1] = inImage[i][k]

    # 회선 연산
    for i in range(inH):
        for k in range(inW):
            S = 0.0
            for m in range(3):
                for n in range(3):
                    S += tmpInImage[i + m][k + n] * mask[m][n]
            tmpOutImage[i][k] = S

    # 후처리
    for i in range(outH):
        for k in range(outW):
            if (tmpOutImage[i][k] < 0.0):
                outImage[i][k] = 0
            elif (tmpOutImage[i][k] > 255.0):
                outImage[i][k] = 255
            else:
                outImage[i][k] = int(tmpOutImage[i][k])

    #############################
    displayImage()


def sharpning():
    global window, canvas, paper
    global inImage, outImage, inH, inW, outH, outW
    # (중요!) 출력 이미지 크기 결정 --> 알고리즘에 의존
    outH = inH
    outW = inW
    # 출력 이미지 메모리 확보
    outImage = malloc2D(outH, outW)
    ### 진짜 영상처리 알고리즘 ###
    mask = [[0.0, -1.0, 0.0], [-1.0, 5.0, -1.0], [0.0, -1.0, 0.0]]
    tmpInImage = malloc2D(inH + 2, inW + 2)
    tmpOutImage = malloc2D(outH, outW)
    for i in range(inH + 2):  # for (int i = 0; i < inH; i++)
        for k in range(inW + 2):  # for (int k =0; k < inW; k++)
            tmpInImage[i][k] = 127
    for i in range(inH):  # for (int i = 0; i < inH; i++)
        for k in range(inW):  # for (int k =0; k < inW; k++)
            tmpInImage[i + 1][k + 1] = inImage[i][k]

    # 회선 연산
    for i in range(inH):
        for k in range(inW):
            S = 0.0
            for m in range(3):
                for n in range(3):
                    S += tmpInImage[i + m][k + n] * mask[m][n]
            tmpOutImage[i][k] = S

    # 후처리
    for i in range(outH):
        for k in range(outW):
            if (tmpOutImage[i][k] < 0.0):
                outImage[i][k] = 0
            elif (tmpOutImage[i][k] > 255.0):
                outImage[i][k] = 255
            else:
                outImage[i][k] = int(tmpOutImage[i][k])

    #############################
    displayImage()


def hpfSharp():
    global window, canvas, paper
    global inImage, outImage, inH, inW, outH, outW
    # (중요!) 출력 이미지 크기 결정 --> 알고리즘에 의존
    outH = inH
    outW = inW
    # 출력 이미지 메모리 확보
    outImage = malloc2D(outH, outW)
    ### 진짜 영상처리 알고리즘 ###
    mask = [[-1 / 9, -1 / 9, -1 / 9], [-1 / 9, 8 / 9, -1 / 9], [-1 / 9, -1 / 9, -1 / 9]]
    tmpInImage = malloc2D(inH + 2, inW + 2)
    tmpOutImage = malloc2D(outH, outW)
    for i in range(inH + 2):  # for (int i = 0; i < inH; i++)
        for k in range(inW + 2):  # for (int k =0; k < inW; k++)
            tmpInImage[i][k] = 127
    for i in range(inH):  # for (int i = 0; i < inH; i++)
        for k in range(inW):  # for (int k =0; k < inW; k++)
            tmpInImage[i + 1][k + 1] = inImage[i][k]

    # 회선 연산
    for i in range(inH):
        for k in range(inW):
            S = 0.0
            for m in range(3):
                for n in range(3):
                    S += tmpInImage[i + m][k + n] * mask[m][n]
            tmpOutImage[i][k] = S

    # 후처리
    for i in range(outH):
        for k in range(outW):
            if (tmpOutImage[i][k] < 0.0):
                outImage[i][k] = 0
            elif (tmpOutImage[i][k] > 255.0):
                outImage[i][k] = 255
            else:
                outImage[i][k] = int(tmpOutImage[i][k])

    #############################
    displayImage()


def lpfSharp():
    global window, canvas, paper
    global inImage, outImage, inH, inW, outH, outW
    # (중요!) 출력 이미지 크기 결정 --> 알고리즘에 의존
    outH = inH
    outW = inW
    # 출력 이미지 메모리 확보
    outImage = malloc2D(outH, outW)
    ### 진짜 영상처리 알고리즘 ###
    mask = [[1 / 9, 1 / 9, 1 / 9], [1 / 9, 1 / 9, 1 / 9], [1 / 9, 1 / 9, 1 / 9]]
    tmpInImage = malloc2D(inH + 2, inW + 2)
    tmpOutImage = malloc2D(outH, outW)
    for i in range(inH + 2):  # for (int i = 0; i < inH; i++)
        for k in range(inW + 2):  # for (int k =0; k < inW; k++)
            tmpInImage[i][k] = 127
    for i in range(inH):  # for (int i = 0; i < inH; i++)
        for k in range(inW):  # for (int k =0; k < inW; k++)
            tmpInImage[i + 1][k + 1] = inImage[i][k]

    # 회선 연산
    for i in range(inH):
        for k in range(inW):
            S = 0.0
            for m in range(3):
                for n in range(3):
                    S += tmpInImage[i + m][k + n] * mask[m][n]
            tmpOutImage[i][k] = S

    # 후처리
    for i in range(outH):
        for k in range(outW):
            if (tmpOutImage[i][k] < 0.0):
                outImage[i][k] = 0
            elif (tmpOutImage[i][k] > 255.0):
                outImage[i][k] = 255
            else:
                outImage[i][k] = int(tmpOutImage[i][k])

    #############################
    displayImage()


def smoothing():
    global window, canvas, paper
    global inImage, outImage, inH, inW, outH, outW
    # (중요!) 출력 이미지 크기 결정 --> 알고리즘에 의존
    outH = inH
    outW = inW
    # 출력 이미지 메모리 확보
    outImage = malloc2D(outH, outW)
    ### 진짜 영상처리 알고리즘 ###
    mask = [[1 / 16, 1 / 8, 1 / 16], [1 / 8, 1 / 4, 1 / 8], [1 / 16, 1 / 8, 1 / 16]]
    tmpInImage = malloc2D(inH + 2, inW + 2)
    tmpOutImage = malloc2D(outH, outW)
    for i in range(inH + 2):  # for (int i = 0; i < inH; i++)
        for k in range(inW + 2):  # for (int k =0; k < inW; k++)
            tmpInImage[i][k] = 127
    for i in range(inH):  # for (int i = 0; i < inH; i++)
        for k in range(inW):  # for (int k =0; k < inW; k++)
            tmpInImage[i + 1][k + 1] = inImage[i][k]

    # 회선 연산
    for i in range(inH):
        for k in range(inW):
            S = 0.0
            for m in range(3):
                for n in range(3):
                    S += tmpInImage[i + m][k + n] * mask[m][n]
            tmpOutImage[i][k] = S

    # 후처리
    for i in range(outH):
        for k in range(outW):
            if (tmpOutImage[i][k] < 0.0):
                outImage[i][k] = 0
            elif (tmpOutImage[i][k] > 255.0):
                outImage[i][k] = 255
            else:
                outImage[i][k] = int(tmpOutImage[i][k])

    #############################
    displayImage()


def edge1():
    global window, canvas, paper
    global inImage, outImage, inH, inW, outH, outW
    # (중요!) 출력 이미지 크기 결정 --> 알고리즘에 의존
    outH = inH
    outW = inW
    # 출력 이미지 메모리 확보
    outImage = malloc2D(outH, outW)
    ### 진짜 영상처리 알고리즘 ###
    mask = [[0, 0, 0], [-1, 1, 0], [0, 0, 0]]
    tmpInImage = malloc2D(inH + 2, inW + 2)
    tmpOutImage = malloc2D(outH, outW)
    for i in range(inH + 2):  # for (int i = 0; i < inH; i++)
        for k in range(inW + 2):  # for (int k =0; k < inW; k++)
            tmpInImage[i][k] = 127
    for i in range(inH):  # for (int i = 0; i < inH; i++)
        for k in range(inW):  # for (int k =0; k < inW; k++)
            tmpInImage[i][k] = inImage[i][k]

    # 회선 연산
    S = 0
    for i in range(inH):
        for k in range(inW):
            S = 0
            for m in range(3):
                for n in range(3):
                    S += tmpInImage[i + m][k + n] * mask[m][n]
            tmpOutImage[i][k] = S

    # 후처리
    for i in range(outH):
        for k in range(outW):
            if (tmpOutImage[i][k] < 0.0):
                outImage[i][k] = 0
            elif (tmpOutImage[i][k] > 255.0):
                outImage[i][k] = 255
            else:
                outImage[i][k] = int(tmpOutImage[i][k])

    #############################
    displayImage()


def edge2():
    global window, canvas, paper
    global inImage, outImage, inH, inW, outH, outW
    # (중요!) 출력 이미지 크기 결정 --> 알고리즘에 의존
    outH = inH
    outW = inW
    # 출력 이미지 메모리 확보
    outImage = malloc2D(outH, outW)
    ### 진짜 영상처리 알고리즘 ###
    mask = [[0.0, -1.0, 0.0], [0.0, 1.0, 0.0], [0.0, 0.0, 0.0]]
    tmpInImage = malloc2D(inH + 2, inW + 2)
    tmpOutImage = malloc2D(outH, outW)
    for i in range(inH + 2):  # for (int i = 0; i < inH; i++)
        for k in range(inW + 2):  # for (int k =0; k < inW; k++)
            tmpInImage[i][k] = 127
    for i in range(inH):  # for (int i = 0; i < inH; i++)
        for k in range(inW):  # for (int k =0; k < inW; k++)
            tmpInImage[i + 1][k + 1] = inImage[i][k]

    # 회선 연산
    for i in range(inH):
        for k in range(inW):
            S = 0.0
            for m in range(3):
                for n in range(3):
                    S += tmpInImage[i + m][k + n] * mask[m][n]
            tmpOutImage[i][k] = S

    # 후처리
    for i in range(outH):
        for k in range(outW):
            if (tmpOutImage[i][k] < 0.0):
                outImage[i][k] = 0
            elif (tmpOutImage[i][k] > 255.0):
                outImage[i][k] = 255
            else:
                outImage[i][k] = int(tmpOutImage[i][k])

    #############################
    displayImage()


def edge3():
    global window, canvas, paper
    global inImage, outImage, inH, inW, outH, outW
    # (중요!) 출력 이미지 크기 결정 --> 알고리즘에 의존
    outH = inH
    outW = inW
    # 출력 이미지 메모리 확보
    outImage = malloc2D(outH, outW)
    ### 진짜 영상처리 알고리즘 ###
    mask = [[1.0, 1.0, 1.0], [1.0, 1.0, 1.0], [1.0, 1.0, 1.0]]
    tmpInImage = malloc2D(inH + 2, inW + 2)
    tmpOutImage = malloc2D(outH, outW)
    for i in range(inH + 2):  # for (int i = 0; i < inH; i++)
        for k in range(inW + 2):  # for (int k =0; k < inW; k++)
            tmpInImage[i][k] = 127
    for i in range(inH):  # for (int i = 0; i < inH; i++)
        for k in range(inW):  # for (int k =0; k < inW; k++)
            tmpInImage[i + 1][k + 1] = inImage[i][k]

    # 회선 연산
    S, dif = 0, 0
    for i in range(inH):
        for k in range(inW):
            dif = 0
            for m in range(3):
                for n in range(3):
                    S = tmpInImage[i + 1][k + 1] - tmpInImage[i + m][k + n]
                    if (S > dif):
                        dif = S
            tmpOutImage[i][k] = dif

    # 후처리
    for i in range(outH):
        for k in range(outW):
            t = tmpOutImage[i][k]
            if (t < 0.0):
                t = 0
            elif (t > 255.0):
                t = 255
            else:
                outImage[i][k] = int(int(tmpOutImage[i][k]) * (t / 255))

    #############################
    displayImage()


def Rrow():
    global window, canvas, paper
    global inImage, outImage, inH, inW, outH, outW
    # (중요!) 출력 이미지 크기 결정 --> 알고리즘에 의존
    outH = inH
    outW = inW
    # 출력 이미지 메모리 확보
    outImage = malloc2D(outH, outW)
    ### 진짜 영상처리 알고리즘 ###
    mask = [[-1.0, 0.0, 0.0], [0.0, 1.0, 0.0], [0.0, 0.0, 0.0]]
    tmpInImage = malloc2D(inH + 2, inW + 2)
    tmpOutImage = malloc2D(outH, outW)
    for i in range(inH + 2):  # for (int i = 0; i < inH; i++)
        for k in range(inW + 2):  # for (int k =0; k < inW; k++)
            tmpInImage[i][k] = 127
    for i in range(inH):  # for (int i = 0; i < inH; i++)
        for k in range(inW):  # for (int k =0; k < inW; k++)
            tmpInImage[i + 1][k + 1] = inImage[i][k]

    # 회선 연산
    for i in range(inH):
        for k in range(inW):
            S = 0.0
            for m in range(3):
                for n in range(3):
                    S += tmpInImage[i + m][k + n] * mask[m][n]
            tmpOutImage[i][k] = S

    # 후처리
    for i in range(outH):
        for k in range(outW):
            if (tmpOutImage[i][k] < 0.0):
                outImage[i][k] = 0
            elif (tmpOutImage[i][k] > 255.0):
                outImage[i][k] = 255
            else:
                outImage[i][k] = int(tmpOutImage[i][k])

    #############################
    displayImage()


def Rcol():
    global window, canvas, paper
    global inImage, outImage, inH, inW, outH, outW
    # (중요!) 출력 이미지 크기 결정 --> 알고리즘에 의존
    outH = inH
    outW = inW
    # 출력 이미지 메모리 확보
    outImage = malloc2D(outH, outW)
    ### 진짜 영상처리 알고리즘 ###
    mask = [[0.0, 0.0, -1.0], [0.0, 1.0, 0.0], [0.0, 0.0, 0.0]]
    tmpInImage = malloc2D(inH + 2, inW + 2)
    tmpOutImage = malloc2D(outH, outW)
    for i in range(inH + 2):  # for (int i = 0; i < inH; i++)
        for k in range(inW + 2):  # for (int k =0; k < inW; k++)
            tmpInImage[i][k] = 127
    for i in range(inH):  # for (int i = 0; i < inH; i++)
        for k in range(inW):  # for (int k =0; k < inW; k++)
            tmpInImage[i + 1][k + 1] = inImage[i][k]

    # 회선 연산
    for i in range(inH):
        for k in range(inW):
            S = 0.0
            for m in range(3):
                for n in range(3):
                    S += tmpInImage[i + m][k + n] * mask[m][n]
            tmpOutImage[i][k] = S

    # 후처리
    for i in range(outH):
        for k in range(outW):
            if (tmpOutImage[i][k] < 0.0):
                outImage[i][k] = 0
            elif (tmpOutImage[i][k] > 255.0):
                outImage[i][k] = 255
            else:
                outImage[i][k] = int(tmpOutImage[i][k])

    #############################
    displayImage()


def Srow():
    global window, canvas, paper
    global inImage, outImage, inH, inW, outH, outW
    # (중요!) 출력 이미지 크기 결정 --> 알고리즘에 의존
    outH = inH
    outW = inW
    # 출력 이미지 메모리 확보
    outImage = malloc2D(outH, outW)
    ### 진짜 영상처리 알고리즘 ###
    mask = [[-1.0, -1.0, -1.0], [0.0, 0.0, 0.0], [1.0, 1.0, 1.0]]
    tmpInImage = malloc2D(inH + 2, inW + 2)
    tmpOutImage = malloc2D(outH, outW)
    for i in range(inH + 2):  # for (int i = 0; i < inH; i++)
        for k in range(inW + 2):  # for (int k =0; k < inW; k++)
            tmpInImage[i][k] = 127
    for i in range(inH):  # for (int i = 0; i < inH; i++)
        for k in range(inW):  # for (int k =0; k < inW; k++)
            tmpInImage[i + 1][k + 1] = inImage[i][k]

    # 회선 연산
    for i in range(inH):
        for k in range(inW):
            S = 0.0
            for m in range(3):
                for n in range(3):
                    S += tmpInImage[i + m][k + n] * mask[m][n]
            tmpOutImage[i][k] = S

    # 후처리
    for i in range(outH):
        for k in range(outW):
            if (tmpOutImage[i][k] < 0.0):
                outImage[i][k] = 0
            elif (tmpOutImage[i][k] > 255.0):
                outImage[i][k] = 255
            else:
                outImage[i][k] = int(tmpOutImage[i][k])

    #############################
    displayImage()


def Scol():
    global window, canvas, paper
    global inImage, outImage, inH, inW, outH, outW
    # (중요!) 출력 이미지 크기 결정 --> 알고리즘에 의존
    outH = inH
    outW = inW
    # 출력 이미지 메모리 확보
    outImage = malloc2D(outH, outW)
    ### 진짜 영상처리 알고리즘 ###
    mask = [[1.0, 0.0, -1.0], [1.0, 0.0, -1.0], [1.0, 0.0, -1.0]]
    tmpInImage = malloc2D(inH + 2, inW + 2)
    tmpOutImage = malloc2D(outH, outW)
    for i in range(inH + 2):  # for (int i = 0; i < inH; i++)
        for k in range(inW + 2):  # for (int k =0; k < inW; k++)
            tmpInImage[i][k] = 127
    for i in range(inH):  # for (int i = 0; i < inH; i++)
        for k in range(inW):  # for (int k =0; k < inW; k++)
            tmpInImage[i + 1][k + 1] = inImage[i][k]

    # 회선 연산
    for i in range(inH):
        for k in range(inW):
            S = 0.0
            for m in range(3):
                for n in range(3):
                    S += tmpInImage[i + m][k + n] * mask[m][n]
            tmpOutImage[i][k] = S
    # 후처리
    for i in range(outH):
        for k in range(outW):
            if (tmpOutImage[i][k] < 0.0):
                outImage[i][k] = 0
            elif (tmpOutImage[i][k] > 255.0):
                outImage[i][k] = 255
            else:
                outImage[i][k] = int(tmpOutImage[i][k])

    #############################
    displayImage()


def Prow():
    global window, canvas, paper
    global inImage, outImage, inH, inW, outH, outW
    # (중요!) 출력 이미지 크기 결정 --> 알고리즘에 의존
    outH = inH
    outW = inW
    # 출력 이미지 메모리 확보
    outImage = malloc2D(outH, outW)
    ### 진짜 영상처리 알고리즘 ###
    mask = [[-1.0, -2.0, -1.0], [0.0, 0.0, 0.0], [1.0, 2.0, 1.0]]
    tmpInImage = malloc2D(inH + 2, inW + 2)
    tmpOutImage = malloc2D(outH, outW)
    for i in range(inH + 2):  # for (int i = 0; i < inH; i++)
        for k in range(inW + 2):  # for (int k =0; k < inW; k++)
            tmpInImage[i][k] = 127
    for i in range(inH):  # for (int i = 0; i < inH; i++)
        for k in range(inW):  # for (int k =0; k < inW; k++)
            tmpInImage[i + 1][k + 1] = inImage[i][k]

    # 회선 연산
    for i in range(inH):
        for k in range(inW):
            S = 0.0
            for m in range(3):
                for n in range(3):
                    S += tmpInImage[i + m][k + n] * mask[m][n]
            tmpOutImage[i][k] = S

    # 후처리
    for i in range(outH):
        for k in range(outW):
            if (tmpOutImage[i][k] < 0.0):
                outImage[i][k] = 0
            elif (tmpOutImage[i][k] > 255.0):
                outImage[i][k] = 255
            else:
                outImage[i][k] = int(tmpOutImage[i][k])

    #############################
    displayImage()


def Pcol():
    global window, canvas, paper
    global inImage, outImage, inH, inW, outH, outW
    # (중요!) 출력 이미지 크기 결정 --> 알고리즘에 의존
    outH = inH
    outW = inW
    # 출력 이미지 메모리 확보
    outImage = malloc2D(outH, outW)
    ### 진짜 영상처리 알고리즘 ###
    mask = [[1.0, 0.0, -1.0], [2.0, 0.0, -2.0], [1.0, 0.0, -1.0]]
    tmpInImage = malloc2D(inH + 2, inW + 2)
    tmpOutImage = malloc2D(outH, outW)
    for i in range(inH + 2):  # for (int i = 0; i < inH; i++)
        for k in range(inW + 2):  # for (int k =0; k < inW; k++)
            tmpInImage[i][k] = 127
    for i in range(inH):  # for (int i = 0; i < inH; i++)
        for k in range(inW):  # for (int k =0; k < inW; k++)
            tmpInImage[i + 1][k + 1] = inImage[i][k]

    # 회선 연산
    for i in range(inH):
        for k in range(inW):
            S = 0.0
            for m in range(3):
                for n in range(3):
                    S += tmpInImage[i + m][k + n] * mask[m][n]
            tmpOutImage[i][k] = S

    # 후처리
    for i in range(outH):
        for k in range(outW):
            if (tmpOutImage[i][k] < 0.0):
                outImage[i][k] = 0
            elif (tmpOutImage[i][k] > 255.0):
                outImage[i][k] = 255
            else:
                outImage[i][k] = int(tmpOutImage[i][k])

    #############################
    displayImage()


def lap1():
    global window, canvas, paper
    global inImage, outImage, inH, inW, outH, outW
    # (중요!) 출력 이미지 크기 결정 --> 알고리즘에 의존
    outH = inH
    outW = inW
    # 출력 이미지 메모리 확보
    outImage = malloc2D(outH, outW)
    ### 진짜 영상처리 알고리즘 ###
    mask = [[0.0, -1.0, 0.0], [-1.0, 4.0, -1.0], [0.0, -1.0, 0.0]]
    tmpInImage = malloc2D(inH + 2, inW + 2)
    tmpOutImage = malloc2D(outH, outW)
    for i in range(inH + 2):  # for (int i = 0; i < inH; i++)
        for k in range(inW + 2):  # for (int k =0; k < inW; k++)
            tmpInImage[i][k] = 127
    for i in range(inH):  # for (int i = 0; i < inH; i++)
        for k in range(inW):  # for (int k =0; k < inW; k++)
            tmpInImage[i + 1][k + 1] = inImage[i][k]

    # 회선 연산
    for i in range(inH):
        for k in range(inW):
            S = 0.0
            for m in range(3):
                for n in range(3):
                    S += tmpInImage[i + m][k + n] * mask[m][n]
            tmpOutImage[i][k] = S

    # 후처리
    for i in range(outH):
        for k in range(outW):
            if (tmpOutImage[i][k] < 0.0):
                outImage[i][k] = 0
            elif (tmpOutImage[i][k] > 255.0):
                outImage[i][k] = 255
            else:
                outImage[i][k] = int(tmpOutImage[i][k])

    #############################
    displayImage()


def lap2():
    global window, canvas, paper
    global inImage, outImage, inH, inW, outH, outW
    # (중요!) 출력 이미지 크기 결정 --> 알고리즘에 의존
    outH = inH
    outW = inW
    # 출력 이미지 메모리 확보
    outImage = malloc2D(outH, outW)
    ### 진짜 영상처리 알고리즘 ###
    mask = [[1.0, 1.0, 1.0], [1.0, -8.0, 1.0], [1.0, 1.0, 1.0]]
    tmpInImage = malloc2D(inH + 2, inW + 2)
    tmpOutImage = malloc2D(outH, outW)
    for i in range(inH + 2):  # for (int i = 0; i < inH; i++)
        for k in range(inW + 2):  # for (int k =0; k < inW; k++)
            tmpInImage[i][k] = 127
    for i in range(inH):  # for (int i = 0; i < inH; i++)
        for k in range(inW):  # for (int k =0; k < inW; k++)
            tmpInImage[i + 1][k + 1] = inImage[i][k]

    # 회선 연산
    for i in range(inH):
        for k in range(inW):
            S = 0.0
            for m in range(3):
                for n in range(3):
                    S += tmpInImage[i + m][k + n] * mask[m][n]
            tmpOutImage[i][k] = S

    # 후처리
    for i in range(outH):
        for k in range(outW):
            if (tmpOutImage[i][k] < 0.0):
                outImage[i][k] = 0
            elif (tmpOutImage[i][k] > 255.0):
                outImage[i][k] = 255
            else:
                outImage[i][k] = int(tmpOutImage[i][k])

    #############################
    displayImage()


def lap3():
    global window, canvas, paper
    global inImage, outImage, inH, inW, outH, outW
    # (중요!) 출력 이미지 크기 결정 --> 알고리즘에 의존
    outH = inH
    outW = inW
    # 출력 이미지 메모리 확보
    outImage = malloc2D(outH, outW)
    ### 진짜 영상처리 알고리즘 ###
    mask = [[-1.0, -1.0, -1.0], [-1.0, 8.0, -1.0], [-1.0, -1.0, -1.0]]
    tmpInImage = malloc2D(inH + 2, inW + 2)
    tmpOutImage = malloc2D(outH, outW)
    for i in range(inH + 2):  # for (int i = 0; i < inH; i++)
        for k in range(inW + 2):  # for (int k =0; k < inW; k++)
            tmpInImage[i][k] = 127
    for i in range(inH):  # for (int i = 0; i < inH; i++)
        for k in range(inW):  # for (int k =0; k < inW; k++)
            tmpInImage[i + 1][k + 1] = inImage[i][k]

    # 회선 연산
    for i in range(inH):
        for k in range(inW):
            S = 0.0
            for m in range(3):
                for n in range(3):
                    S += tmpInImage[i + m][k + n] * mask[m][n]
            tmpOutImage[i][k] = S

    # 후처리
    for i in range(outH):
        for k in range(outW):
            if (tmpOutImage[i][k] < 0.0):
                outImage[i][k] = 0
            elif (tmpOutImage[i][k] > 255.0):
                outImage[i][k] = 255
            else:
                outImage[i][k] = int(tmpOutImage[i][k])

    #############################
    displayImage()


### 전역 변수부
window, canvas, paper = None, None, None
inImage, outImage = [], []
inH, inW, outH, outW = [0] * 4
fullname = ''

### 메인 코드부
window = Tk()
window.geometry("500x500")
window.resizable(width=False, height=False)
window.title("영상처리(RC 1)")

# 메뉴 만들기
mainMenu = Menu(window)  # 메뉴의 틀
window.config(menu=mainMenu)

fileMenu = Menu(mainMenu, tearoff=0)  # 상위 메뉴 (파일)
mainMenu.add_cascade(label="파일", menu=fileMenu)
fileMenu.add_command(label="열기", command=openImage)
fileMenu.add_command(label="저장", command=saveImage)
fileMenu.add_separator()
fileMenu.add_command(label="종료", command=None)

pixelMenu = Menu(mainMenu, tearoff=0)  # 상위 메뉴 (파일)
mainMenu.add_cascade(label="화소점 처리", menu=pixelMenu)
pixelMenu.add_command(label="동일 이미지", command=equalImage)
pixelMenu.add_command(label="밝게 / 어둡게", command=addImage)
pixelMenu.add_command(label="AND 연산", command=andImage)
pixelMenu.add_command(label="OR 연산", command=orImage)
pixelMenu.add_command(label="XOR 연산", command=xorImage)
pixelMenu.add_command(label="반전 이미지", command=revImage)
pixelMenu.add_command(label="흑백 (127)", command=bwImage)
pixelMenu.add_command(label="흑백 (평균값)", command=avgbwImage)
pixelMenu.add_command(label="흑백 (중앙값)", command=medbwImage)
pixelMenu.add_command(label="감마 보정", command=gammaImage)
pixelMenu.add_command(label="CAP 파라볼라", command=CAPparaImage)
pixelMenu.add_command(label="CUP 파라볼라", command=CUPparaImage)
pixelMenu.add_command(label="포스터라이징", command=posterImage)
pixelMenu.add_command(label="범위 강조", command=stressImage)

geoMenu = Menu(mainMenu, tearoff=0)
mainMenu.add_cascade(label="기하학 처리", menu=geoMenu)
geoMenu.add_command(label="축소", command=zoutImage)
geoMenu.add_command(label="확대", command=zinImage)
geoMenu.add_command(label="확대(백워딩)", command=zinImage2)
geoMenu.add_command(label="회전(기본)", command=rotImage)
geoMenu.add_command(label="회전(중앙, 백워딩)", command=rotImage2)
geoMenu.add_command(label="이미지 이동", command=moveImage)
geoMenu.add_command(label="좌우반전", command=mirrorLR)
geoMenu.add_command(label="상하반전", command=mirrorUD)
geoMenu.add_command(label="상하좌우반전", command=mirrorALL)

histoMenu = Menu(mainMenu, tearoff=0)
mainMenu.add_cascade(label="히스토그램 처리", menu=histoMenu)
histoMenu.add_command(label="히스토그램 스트레칭", command=histoStretch)
histoMenu.add_command(label="엔드-인", command=endIn)
histoMenu.add_command(label="히스토그램 평활화", command=histoEqual)
histoMenu.add_command(label="엠보싱", command=emboss)
histoMenu.add_command(label="블러링", command=blur)
histoMenu.add_command(label="샤프닝", command=sharpning)
histoMenu.add_command(label="고주파필터 샤프닝", command=hpfSharp)
histoMenu.add_command(label="저주파필터 샤프닝", command=lpfSharp)
histoMenu.add_command(label="가우시안 스무딩", command=smoothing)

edgeMenu = Menu(mainMenu, tearoff=0)
mainMenu.add_cascade(label="경계선 검출", menu=edgeMenu)
edgeMenu.add_command(label="경계선 검출(1)", command=edge1)
edgeMenu.add_command(label="경계선 검출(2)", command=edge2)
edgeMenu.add_command(label="경계선 검출(3)", command=edge3)
edgeMenu.add_command(label="로버트(행 검출)", command=Rrow)
edgeMenu.add_command(label="로버트(열 검출)", command=Rcol)
edgeMenu.add_command(label="소벨(행 검출)", command=Srow)
edgeMenu.add_command(label="소벨(열 검출)", command=Scol)
edgeMenu.add_command(label="프리윗(행 검출)", command=Prow)
edgeMenu.add_command(label="프리윗(열 검출)", command=Pcol)
edgeMenu.add_command(label="라플라시안(1)", command=lap1)
edgeMenu.add_command(label="라플라시안(2)", command=lap2)
edgeMenu.add_command(label="라플라시안(3)", command=lap3)

window.mainloop()