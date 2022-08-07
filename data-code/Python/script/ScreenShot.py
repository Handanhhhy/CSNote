#!/usr/bin/env python3
# -*- coding: utf-8 -*- 
"""
Created on Tue Jun 12 09:37:38 2018
利用百度api实现图片文本识别
@author: XnCSD
"""

import glob
from os import path
import os
from aip import AipOcr
from PIL import Image
from PIL import ImageGrab
import pyautogui
from pymouse import PyMouse
import time

def convertimg(picfile, outdir):
    '''调整图片大小，对于过大的图片进行压缩
    picfile:    图片路径
    outdir：    图片输出路径
    '''
    #picfile="D:\PythonFile\normal_work\tmp"
    img = Image.open(picfile)
    width, height = img.size
    while(width*height > 4000000):  # 该数值压缩后的图片大约 两百多k
        width = width // 2
        height = height // 2
    new_img=img.resize((width, height),Image.BILINEAR)
    new_img.save(path.join(outdir,os.path.basename(picfile)))
    
def baiduOCR(picfile, outfile):
    """利用百度api识别文本，并保存提取的文字
    picfile:    图片文件名
    outfile:    输出文件
    """
    filename = path.basename(picfile)
    
    APP_ID = '20632746' # 刚才获取的 ID，下同
    API_KEY = 'Lau5sg4N6ZVp5GfSrLi6uWMP'
    SECRECT_KEY = 'r10X9Cm0fLeX95xUUy9bidby3d48qZBe'
    client = AipOcr(APP_ID, API_KEY, SECRECT_KEY)
    
    i = open(picfile, 'rb')
    img = i.read()
    print("正在识别图片：\t" + filename)
    message = client.basicGeneral(img)   # 通用文字识别，每天 50 000 次免费
    #message = client.basicAccurate(img)   # 通用文字高精度识别，每天 800 次免费
    print("识别成功！")
    i.close();
    
    with open(outfile, 'a+') as fo:
        #fo.writelines("+" * 60 + '\n')
        fo.writelines("识别图片：\t" + filename + "\n" * 2)
        #fo.writelines("文本内容：\n")
        # 输出文本内容
        for text in message.get('words_result'):
            fo.writelines(text.get('words') + '\n')
        fo.writelines('\n'*2)
    #print("文本导出成功！")
    print()

def ScreenShot():
    pos = (340,158,1282, 1020)
    s_x,x,y = 38,38,495
    cur,i,aim = 1,0,100
    gap_x,gap_y=40,33
    path = "D:/PythonFile/normal_work/tmp/"
    
    while (i<aim):   
        cut_img = ImageGrab.grab(pos)
        cut_img.save(path+str(cur)+".png")
        i=i+1
        cur=cur+1
        if(i%7 == 0):
            y = y + gap_y
            x = s_x
        else:
            x = x + gap_x
        AutoClick(x,y)



def AutoClick(x,y):
    pyautogui.moveTo(x,y,duration=0.5)
    pyautogui.click()

def Ocr():
    outfile = 'export.txt'
    outdir = 'tmp'
    if path.exists(outfile):
        os.remove(outfile)
    if not path.exists(outdir):
        os.mkdir(outdir)
    print("压缩过大的图片...")
    for picfile in glob.glob("picture/*"):
        convertimg(picfile, outdir)
    print("图片识别...")
    for picfile in glob.glob("tmp/*"):
        baiduOCR(picfile, outfile)
        #os.remove(picfile)
    print('图片文本提取结束！文本输出结果位于 %s 文件中。' % outfile)
    #os.removedirs(outdir)

    
if __name__ == "__main__":
    time.sleep(2)
    #ScreenShot()
    Ocr()

    
