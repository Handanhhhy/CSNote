'''
使用正则表达式提取原文件名中重要部分以新命名
'''
import os
import re

aimDir=r"C:\Users\25467\Desktop\Documents"
#将dfgf123asdf456.txt变成123-456.txt
pattern=re.compile(r'\d+')
sep='-'

def modify(dir):
    for name in os.listdir(dir):
        oldname,suffix=os.path.splitext(name)
        res=re.findall(pattern,oldname)
        #print("res:",res)
        keyname=sep.join(res)
        #print("name:",name," keyname",keyname+suffix)
        os.rename(dir+os.sep+name,dir+os.sep+keyname+suffix)
        if os.path.isdir(dir+os.sep+name):
            modify(dir+os.sep+name)


os.chdir(aimDir)
print(os.getcwd())
modify(os.getcwd())
