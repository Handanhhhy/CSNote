![image-20210507224909085](image-20210507224909085.png)

### request.get()

构造一个向服务器请求资源的Request对象，返回一个包含服务器资源的Response对象

![image-20210507225643191](requests-image/image-20210507225643191.png)

![image-20210507225828253](requests-image/image-20210507225828253.png)

![image-20210507230219862](requests-image/image-20210507230219862.png)

![image-20210507230405404](requests-image/image-20210507230405404.png)

![image-20210508195206891](requests-image/image-20210508195206891.png)



```python
try:
	r = requests.get(url,timeout=30)
	r.raise_for_status()
	r.encoding=r.apparent_encoding
	return r.text
except:
	return "产生异常"
```

![image-20210508210333644](requests-image/image-20210508210333644.png)

![image-20210508210822165](requests-image/image-20210508210822165.png)

![image-20210508212156965](requests-image/image-20210508212156965.png)

![image-20210508212827818](requests-image/image-20210508212827818.png)

![image-20210508215110516](requests-image/image-20210508215110516.png)

![image-20210508214928059](requests-image/image-20210508214928059.png)

![image-20210508215008027](requests-image/image-20210508215008027.png)