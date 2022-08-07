'''
使用正则表达式提取原文件名中重要部分以新命名,并添加排序命名
'''
import os
import re
import time
import shutil

aimDir = r"E:\\"
pattern = re.compile(r'-(.*)')
sep = '-'


def extract_name(dir):
    '''004-歌曲-时间都去哪儿了 -> 歌曲-时间都去哪儿了'''
    for name in os.listdir(dir):
        if os.path.isdir(name):
            continue
        oldname, suffix = os.path.splitext(name)
        res = re.findall(pattern, oldname)
        # print("res:",res)
        keyname = sep.join(res)
        #print("name:",name," keyname",keyname+suffix)
        os.rename(dir+os.sep+name, dir+os.sep+keyname+suffix)
    pass


def add_prefix(dir):
    '''歌曲-时间都去哪儿了 -> 001-歌曲-时间都去哪儿了'''
    count = 170
    for name in os.listdir(dir):
        if os.path.isdir(name):
            continue
        fpath, oldname = os.path.split(name)
        newname = fpath+str(count).zfill(3)+sep+oldname
        print("name:", fpath+oldname, " newname", fpath+newname)
        os.rename(fpath+oldname, fpath+newname)
        count = count+1
    pass


def comPareFile(elem):
    return int(re.split("-", elem)[0])


def set_file_time(dir):
    '''修改文件时间进行排序,通过比较001-xxx的前缀序'''
    allfile = []
    for name in os.listdir(dir):
        allfile.append(name)
    allfile.sort(key=comPareFile)
    for name in allfile:
        filename = os.path.abspath(name)
        update_time = time.strftime(
            "%Y-%m-%d %H:%M:%S", time.localtime(os.path.getmtime(filename)))
        print("filename:", filename, "old_update_time:", update_time, sep=" ")

        #cur_time = time.strftime("%Y-%m-%d %H:%M:%S", time.localtime())
        os.utime(filename)
        update_time = time.strftime(
            "%Y-%m-%d %H:%M:%S", time.localtime(os.path.getmtime(filename)))
        print("new_update_time:", update_time)
    pass


def add_prefix_by_oldfix(dir):
    allfile = []
    for name in os.listdir(dir):
        allfile.append(name)
    allfile.sort(key=comPareFile)

    count = 1
    for name in allfile:
        if os.path.isdir(name):
            continue
        fpath, oldname = os.path.split(name)
        rep_fix = oldname.split('-')[0]
        newname = fpath+str(count).zfill(3)+oldname.replace(rep_fix, '')
        print("name:", fpath+oldname, " newname", fpath+newname)
        os.rename(fpath+oldname, fpath+newname)
        count = count+1
    pass


def moveFile(curDir, aimDir):
    '''用于按顺序复制进U盘，使U盘有序'''
    allfile = []
    for name in os.listdir(curDir):
        allfile.append(name)
    allfile.sort(key=comPareFile)
    for name in allfile:
        fileName = os.path.basename(name)
        aimPath = aimDir + '\\' + fileName
        print("当前操作文件：", fileName, sep=" ")
        #shutil.copy(curDir+'\\'+name, aimPath)
        shutil.move(curDir+'\\'+name, aimPath)
        print("操作完成")
    print("移动完成")
    pass

#dir = r"D:\Vidio\我的兄弟叫顺溜"


def change_suffix(dir):
    '''改变suffix'''
    for file in os.listdir(dir):
        if file.endswith("pdf"):
            print(os.path.join(dir, file), sep="->")
            _file = file.replace("pdf", "mp4")
            os.rename(os.path.join(dir, file), os.path.join(dir, _file))
            print(os.path.join(dir, _file))


def add_dir_name(dir):
    '''将文件夹名称添加到文件前面'''
    add_name = dir.split("\\")[-1]
    # print(add_name)
    for file in os.listdir(dir):
        print(os.path.join(dir, file), os.path.join(
            dir, add_name+file), sep='->')
        os.rename(os.path.join(dir, file),
                  os.path.join(dir, add_name+file))


os.chdir(aimDir)
print(os.getcwd())
# set_file_time(os.getcwd())
# extract_name(os.getcwd())
# add_prefix(os.getcwd())
# add_prefix_by_oldfix(os.getcwd())
moveFile(r"D:\Vidio\知否知否", os.getcwd())
