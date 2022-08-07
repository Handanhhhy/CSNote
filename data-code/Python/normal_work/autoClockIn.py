import time
import os
import sys
import shutil
from selenium import webdriver  # 导入库
from selenium.webdriver.common.action_chains import ActionChains
#D:\PythonFile\normal_work\autoClockIn.py 201810412105 510502 otherLog
#日志文件存放
logFileName = "C:\\Users\\ASUS\\Desktop\\CheckInLog"
#用户名密码
name = ""
pswd = ""
#获取Chrome的运行配置
option = webdriver.ChromeOptions()
option.binary_location = "D:\\Chrome\\Application\\chrome.exe"
option.add_argument('disable-infobars')
#存储Chrome运行配置的文件
tempDir = "D:\\Temp\\profile"
option.add_argument("user-data-dir=%s" % (tempDir))
#设置无头模式
option.add_argument('--headless')
option.add_argument('--disable-gpu')
option.add_argument('--no-sandbox')
option.add_argument('--disable-dev-shm-usage')

browser = webdriver.Chrome(executable_path
                           ="D:\\Tools\\chromedriver.exe",chrome_options=option)

def LogIn():
    browser.implicitly_wait(3)
    url = "https://xsswzx.cdu.edu.cn/ispstu4-1/com_user/weblogin.asp"
    browser.get(url)
    browser.implicitly_wait(3)
    #用户名和密码
    namePath = "//*[@id='username']"
    pswdPath = "//*[@id='userpwd']"
    nameBox = browser.find_element_by_xpath(namePath)
    pswdBox= browser.find_element_by_xpath(pswdPath)
    #填入
    ActionChains(browser).move_to_element(nameBox).click().perform()
    nameBox.send_keys(name)
    ActionChains(browser).move_to_element(pswdBox).click().perform()
    pswdBox.send_keys(pswd)

    #获取验证码
    validPath = "//*[@id='form']/div[3]" #Chrome
    validCodebox = browser.find_element_by_xpath(validPath)
    validCode = validCodebox.text.strip()
    #填入
    inputBox =browser.find_element_by_xpath("//*[@id='code']")
    ActionChains(browser).move_to_element(inputBox).click().perform()
    inputBox.send_keys(validCode)

    #点击登录
    login = browser.find_element_by_id("提交")
    time.sleep(0.5)
    login.click()
    pass

def Log(message,flag):
    logFile = open(logFileName,"a",encoding='gbk')
    if flag == True:
        logFile.write(name+" "+message + '登记成功\n')
    else:
        logFile.write(name+" "+message + '\n')
    logFile.close()
    pass

def CheckModel():
    browser.switch_to.window(browser.window_handles[-1])
    browser.implicitly_wait(3)
    #print(browser.current_url)  
    #疫情信息登记
    browser.switch_to.frame("leftFrame")
    infoBox = browser.find_element_by_xpath("/html/body/div/div/div[5]/ul[7]/li[2]/a")
    infoBox.click()
    #自动登记
    browser.switch_to.parent_frame()
    browser.switch_to.frame("main")
    pass

def CheckIn():
    CheckModel()
    checkBtn = browser.find_element_by_xpath("/html/body/table[1]/tbody/tr[6]/td/a[2]/input")
    checkBtn.click()
    #获取对话框
    try:
        browser.implicitly_wait(3)
        browser.switch_to.alert.accept()
    except:
        browser.refresh()
        CheckModel()
        pass
    #输出登记日志
    try:
        firstLine = browser.find_elements_by_css_selector('td.tdmenu')[0]
        checkDate = firstLine.find_element_by_tag_name("div").text
    except:
        Log("登记失败",False)
    else:
        Log(checkDate,True)
    
    #安全退出
    browser.switch_to.parent_frame()
    browser.switch_to.frame("leftFrame")
    logoutBtn = browser.find_element_by_xpath("/html/body/div/div/div[2]/ul/a[2]")
    logoutBtn.click() 
    browser.close()#关闭页面
    browser.quit()#关闭驱动
    pass

def Main():
    time.sleep(1)
    browser.implicitly_wait(5)
    try:
        LogIn()
    except:
        Log("登路失败",False)
    CheckIn()
    pass

if __name__ == "__main__":
    name = str(sys.argv[1])
    pswd = str(sys.argv[2])
    if len(sys.argv) == 4:
        logFileName = "C:\\Users\\ASUS\\Desktop\\" + str(sys.argv[3])
    Main()
    shutil.rmtree(tempDir)


