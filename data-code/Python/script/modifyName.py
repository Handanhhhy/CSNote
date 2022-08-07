'''
修改指定文件夹下aimName的文件名为chaName
'''
import os
import shutil

aimDir=r"D:\Usuall-Files\JavaIDEA\Experiment\project"
aimName="project5"
chaName="project"

def modify(dir):
    for name in os.listdir(dir):
        a,b=os.path.splitext(name)
        if a==aimName:
            #print("name",name,chaName+b)
            os.rename(dir+os.sep+name,dir+os.sep+chaName+b)
        if os.path.isdir(dir+os.sep+name):
            modify(dir+os.sep+name)


os.rename(aimDir,os.path.split(aimDir)[0]+os.sep+chaName)
os.chdir(aimDir)
modify(os.getcwd())
