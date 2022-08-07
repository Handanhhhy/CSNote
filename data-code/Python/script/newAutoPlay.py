import time
from selenium import webdriver 
from selenium.webdriver.common.action_chains import ActionChains


browser = webdriver.Firefox()#executable_path=""  # 双引号内添加下载好的浏览器驱动的地址 D:/Python/Scripts/geckodriver.exe

url = "http://i.chaoxing.com/vLoginPage" #学习通登录地址
browser.get(url)

mycourse=""
mytask=0
myfinished=0
flag=0
English="大学英语A(4)"
Discrete="离散数学"
Mao="毛泽东思想和中国特色社会主义理论体系概论（2018年版）"
Sport="乒乓球"
Work="创业理论与实践"
XZ="形势与政策（2020年春）"
vedio_start_time=0
vedio_end_time=0

def init():
    #code=input("请输入选择的课程代号(0:英语;1:离散数学;2:毛概;3:体育,4:创业理论与实践);5(行政):")
    code="5"
    global mycourse
    global flag
    if code == "1":
        mycourse = Discrete
        flag=3
    elif code == "2":
        mycourse = Mao
        flag=3
    elif code=="3":
        mycourse = Sport
    elif code=="4":
        mycourse = Work
    elif code=="5":
        mycourse = XZ
        flag=3
    else:
        mycourse = English
    print(mycourse)


def input_usename_and_password():
    li=browser.find_element_by_xpath("//li[contains(text(),'手机号/超星号登录')]")
    ActionChains(browser).move_to_element(li).click().perform()#切换登录框
    inp="15181866578"
    inp_2="dhd201810414301" 
    username = browser.find_element_by_id("uin_tips")
    password = browser.find_element_by_id("pwd_tips")
    ActionChains(browser).move_to_element(username).click().perform()
    username.send_keys(inp)
    ActionChains(browser).move_to_element(password).click().perform()
    password.send_keys(inp_2)
    sbm = browser.find_element_by_id("login")
    time.sleep(1)
    sbm.click()


# 进入首页，开始选择课程
def choose_course():
    time.sleep(1)
    #browser.implicitly_wait(3) 网速不好时使用
    browser.switch_to.frame("frame_content")
    str="//a[@title='"+mycourse+"']"
    course = browser.find_element_by_xpath(str)
    browser.execute_script("arguments[0].scrollIntoView({block:'center'});",course)#滑动到指定位置处
    course.click()
    print("进入课程")
    time.sleep(1)
    browser.switch_to.window(browser.window_handles[-1])


# 判断是否有通知
def is_notice():
    time.sleep(1)
    #browser.implicitly_wait(3)
    judge = 1
    while judge:
        try:
            cloes_widow = browser.find_element_by_xpath("/html/body/div[9]/div/a")
            browser.execute_script("arguments[0].scrollIntoView();",cloes_widow)#滑动到指定位置处
            cloes_widow.click()
            print("有通知消息")
        except:
            print("没有通知消息")
            judge = 0
            pass


# 进入课程学习页面 自动选择第一个未完成任务点
def into_start_study_window():
    time.sleep(1)
    #browser.implicitly_wait(3) #网络不太好是隐式等待
    try:
        first = browser.find_elements_by_xpath("//em[@class='orange']//../../span[@class='articlename']/a")
    except:
         print("获取错误")
    global mytask
    mytask = len(first)
    print("总共未完成任务点:", mytask)
    browser.execute_script("arguments[0].scrollIntoView();",first[0])
    ActionChains(browser).move_to_element(first[0]).click().perform()
    first[0].click()
    time.sleep(1)


#该小节任务 视频或ppt
def finish_task():
    main_frame=browser.find_element_by_id("iframe")
    browser.switch_to.frame(main_frame)
    frames=browser.find_elements_by_class_name('ans-insertvideo-online')
    count=len(frames);
    browser.implicitly_wait(3) #网络不太好是隐式等待
    global vedio_start_time,vedio_end_time
    global myfinished
    myfinished = myfinished + 1
    if count > 0:
        print("该小节视频数量:",count)
        for i in range(0,count):
            time.sleep(1)
            browser.execute_script("arguments[0].scrollIntoView({block:'center'});",frames[i])#滑动到指定位置处
            browser.switch_to.frame(frames[i])
            time.sleep(0.5)
            try:
                vidio = browser.find_element_by_class_name("vjs-big-play-button")
                vidio.click()
            except:
                vidio = browser.find_element_by_class_name("vjs-control-bar")
                vidio.click()
                
            try:
                btn_mute=browser.find_element_by_xpath("/html/body/div[4]/div/div[4]/div[6]/button")
                btn_mute.click()
            except:
                btn_mute=browser.find_element_by_class_name("vjs-mute-control")
                btn_mute.click()
                
            print('第{}个视频开始播放'.format(i+1))
            try:
                vedio_end_time = browser.find_element_by_xpath("/html/body/div[4]//div/div[4]/div[4]/span[2]").get_attribute(
            'textContent')
            except:
                try:
                     vedio_end_time = browser.find_element_by_class_name("vjs-duration-display").get_attribute(
            'textContent')
                except:
                    print("无法获取到当前视频结束时间")
                    return
            while (vedio_start_time != vedio_end_time):
                if is_vedio_finished(count,i+1) == False:
                    break 
            print('第{}个视频播放完成'.format(i+1))
            browser.switch_to.parent_frame()
        print("该小节视频播放完毕")
    else:
        print("该小节没有视频")
    
    try:
        ppt_frame=browser.find_element_by_class_name('insertdoc-online-ppt')
    except:
        pass
    else:
        if mycourse == Discrete:
            pass
        else:
            try:
                browser.switch_to.frame(ppt_frame)
                btn_next=browser.find_element_by_xpath("//*[@id='ext-gen1042' and @class='mkeRbtn']")
            except:
                try:
                    btn_next=browser.find_element_by_class_name("mkeRbtn")
                except:
                    browser.switch_to.parent_frame()
                    print("无法获取PPT下一页点击按钮")
                    return  
            print("开始播放PPT")
            try:
                cur_page=browser.find_element_by_xpath("/html/body/div[8]/div[1]/span[1]").get_attribute("textContent")
                all_page=browser.find_element_by_xpath("/html/body/div[8]/div[1]/span[2]]").get_attribute("textContent")
            except:
                try:
                    cur_page=browser.find_element_by_class_name("num")
                    all_page=browser.find_element_by_class_name("all")
                except:
                    print("无法获取ppt页数")
                    return                                         
            while (cur_page!=all_page):
                time.sleep(0.1)
                try:
                    btn_next.click()
                except:
                    break
                
                try:
                    cur_page=browser.find_element_by_xpath("/html/body/div[8]/div[1]/span[1]").get_attribute("textContent")
                except:
                    cur_page=browser.find_element_by_class_name("num")
                print("当前PPT页数:",cur_page)
            print("PPT播放完成")
            browser.switch_to.parent_frame()


#处理选择题
def deal_choice():
    try:
        submit = browser.find_element_by_class_name("ans-videoquiz-submit")
    except:
        return True
    choices = browser.find_elements_by_xpath("//li[@class='ans-videoquiz-opt']/label")
    print(len(choices))
    count = 0
    for choice in choices:
         time.sleep(0.5)
         ActionChains(browser).move_to_element(choice).click().perform()
         choice.click()
         try:
             submit.click()
         except:
             ActionChains(browser).move_to_element(choice).click().perform()
             choice.click()
         finally:
             try:
                 count = count + 1
                 alert = browser.findElement(By.id("alert")).click();
                 print("选错一次")
                 while (alert != None):  
                    flag = True
                    try:
                        time.sleep(0.2)
                        #browser.switch_to.alert.accept()
                        #alert = browser.switch_to.alert
                        browser.switchTo().alert().accept();
                        alert = browser.findElement(By.id("alert")).click();
                    except:
                        break
                    finally:
                        if count > len(choices) :
                            print("跳过一次多选")
                            return False
                        
             except:
                print("处理了一个选择题")
                return True
         
        
        

         
# 判断视频是否完成 同时处理选择题
def is_vedio_finished(allnum,curnum):
    #time.sleep(1)
    browser.implicitly_wait(1)
    global vedio_start_time
    try:
        vedio_start_time = browser.find_element_by_xpath("/html/bodn/div[4]//div/div[4]/div[2]/span[2]").get_attribute(
            "textContent")   
    except:
        try:
            vedio_start_time = browser.find_element_by_class_name("vjs-current-time-display").get_attribute(
            "textContent")
        except:
            return     
    print("该小节共{0}个视频,当前播放进度:第{1}个视频 {2},结束时间是:{3}\n总任务章节数{4},已完成数{5}".format(allnum,curnum, vedio_start_time, vedio_end_time,mytask,myfinished))
    time.sleep(4)  # 每5秒检测一次视频是否完成
    if mycourse == XZ:
        return deal_choice()#处理选择题
    else: return True


def is_next_course():
            browser.switch_to.default_content()
            time.sleep(1)
            #browser.implicitly_wait(3)
            try:
                h1=browser.find_element_by_xpath("/html/body/div[3]/div/div[2]/h1").get_attribute("textContent")
            except:
                try:
                    h1=browser.find_element_by_tag_name("h1").get_attribute("textContent")
                except:
                    print("无法获取到本小节标题")
                    return
            if mycourse == English:
                try:
                    next_page=browser.find_element_by_xpath("/html/body/div[3]/div/div[2]/div[1]/div[2]")
                    next_page.click()
                except:
                    try:
                        next_page=browser.find_element_by_class_name("orientationright ")
                        next_page.click()
                    except:
                        print("无法获取单个下一页按钮")      
            else:
                try:
                    try:
                        next_page=browser.find_element_by_xpath("/*[@id='right1']")
                        next_page.click()
                    except:
                        next_page=browser.find_element_by_id("right1")
                        next_page.click()
                except:
                    try:
                        try:
                            next_page=browser.find_element_by_xpath("/*[@id='right2']")
                            next_page.click()
                        except:
                            next_page=browser.find_element_by_id("right2")
                            next_page.click()
                    except:
                        try:
                            try:
                                next_page=browser.find_element_by_xpath("/*[@id='right3']")
                                next_page.click()     
                            except:
                                next_page=browser.find_element_by_id("right3")
                                next_page.click()
                        except:
                            print("3个下一页按钮均无法获取到,尝试获取单独下一页")
                            try:
                                next_page=browser.find_element_by_xpath("/html/body/div[3]/div/div[2]/div[1]/div[2]")
                                next_page.click()
                            except:
                                try:
                                    next_page=browser.find_element_by_class_name("orientationright ")
                                    next_page.click()
                                except:
                                    print("无法获取单个下一页按钮")
                                else:
                                    print("单个按钮获取成功")
                            
            print("点击下一页")
            time.sleep(0.5)
            try:
                _h1=browser.find_element_by_xpath("/html/body/div[3]/div/div[2]/h1").get_attribute("textContent")
            except:
                try:
                    _h1=browser.find_element_by_tag_name("h1").get_attribute("textContent")
                except:
                    print("无法获取到下一小节标题")
                    return
            print("当前小节和下一小节是:",h1,_h1)
            global flag
            if h1 ==_h1:
                if (mycourse == Discrete) or (mycourse == Mao)or (mycourse == XZ):
                    if flag > 1:
                        flag=flag-1
                        return True
                    else:
                        return False
                else: 
                    return False
            else:
                if (mycourse == Discrete) or (mycourse == Mao) or (mycourse == XZ):
                    flag=3
                return True


            

if __name__ == '__main__':
    init()
    input_usename_and_password()
    choose_course()
    is_notice()
    into_start_study_window()
    while True:
        finish_task()
        if is_next_course() == False:
            print("学习结束")
            break
        else:
            print("开始学习下一小节")
            
