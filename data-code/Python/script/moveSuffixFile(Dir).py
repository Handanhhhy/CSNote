'''
本脚本用于将指定目录下的指定后缀的文件移动或复制到
目的目录下,其文件保存结构和原目录下的一样
即包含目录的移动，而不是提取
'''
import os
import shutil

fileList = []
aimlist = []


def getFile(mainDir, curDir, suffix):
    for file in os.listdir(curDir):
        fileFullpath = os.path.join(curDir, file)
        if os.path.isdir(fileFullpath):
            getFile(mainDir, fileFullpath, suffix)
        else:
            if file.endswith(suffix):
                fileList.append(fileFullpath)
                aimlist.append(fileFullpath.replace(mainDir, ''))
                pass
    pass


def moveFile(aimDir, suffix, choose):
    for file, aimFile in zip(fileList, aimlist):
        aimPath = aimDir + aimFile
        tupFile = os.path.split(aimPath)
        if not os.path.exists(tupFile[0]):
            os.mkdir(tupFile[0])
            pass
        if choose == '0':
            shutil.move(file, aimPath)
        else:
            shutil.copy(file, aimPath)
        pass
    pass


if __name__ == "__main__":
    curDir = input("请输入需要查找的目录:")
    suffix = input("请输入后缀:")
    aimDir = input("请输入目的目录:")
    choose = input("请选择移动(输入0)或者复制(非0):")
    if suffix[0] != '.':
        suffix = '.' + suffix
        pass
    getFile(curDir, curDir, suffix)
    moveFile(aimDir, suffix, choose)
    pass
