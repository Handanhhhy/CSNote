# -*- coding: UTF-8 -*-
import os

dir=r"C:\Users\25467\Desktop\Graduation design\temp"
newname = ""
suffix = ".doc"

def rename(newname,suffix):
    os.chdir(dir)
    fileList = os.listdir(dir)
    if not fileList:
        return
    #按照时间顺序排序文件
    dir_list = sorted(fileList,key=lambda x: os.path.getmtime(os.path.join(dir, x)))
    count = 1
    for file in fileList:
        if os.path.isdir(file):
            continue
        if os.path.splitext(file)[1] != suffix:
            continue
        dstname = newname + str(count) + suffix
        #print(dstname)
        if os.path.exists(dstname) == False :
            os.rename(file,dstname)
            pass
        count = count + 1

    return

rename(newname,suffix)
