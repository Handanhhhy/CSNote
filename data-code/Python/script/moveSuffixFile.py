'''
本脚本用于将指定目录下的指定后缀的文件移动或复制到
目的目录下,不存在目录的创建,即提取,只包含移动或复制
的文件
'''
import os
import shutil

fileList = []


def getFile(curDir, suffix):
    for file in os.listdir(curDir):
        if os.path.isdir(os.path.join(curDir, file)):
            getFile(os.path.join(curDir, file), suffix)
        else:
            if file.endswith(suffix):
                fileList.append(curDir + '\\'+file)
                pass
    pass


def moveFile(aimDir, suffix, choose):
    for file in fileList:
        fileName = os.path.basename(file)
        aimPath = aimDir + '\\' + fileName
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
    getFile(curDir, suffix)
    moveFile(aimDir, suffix, choose)
    pass
