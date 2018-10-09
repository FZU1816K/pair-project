# -*- coding:utf-8 -*-
import re
import time
from urllib import request
from bs4 import BeautifulSoup

class MyPaper:
    Num = 0
    def __init__(self,PTitle,PAbstract):
        Num += 1
        Title = PTitle
        Abstract = PAbstract

url = r'http://openaccess.thecvf.com/CVPR2018.py'
# 模拟真实浏览器进行访问
headers = {'User-Agent':'Mozilla/5.0 (Windows NT 10.0; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/55.0.2883.87 Safari/537.36'}
page = request.Request(url, headers=headers)
page_info = request.urlopen(page).read()
page_info = page_info.decode('utf-8')

# 将获取到的内容转换成BeautifulSoup格式，并将html.parser作为解析器
soup = BeautifulSoup(page_info, 'html.parser')  

# 以格式化的形式打印html
# print(soup.prettify())
titles = soup.find_all(href=re.compile(".html"))  # 查找所有a标签中class='title'的语句
# 打印查找到的每一个a标签的string
f = open("result.txt","w",encoding='utf-8')
i = -1
for title in titles:
    i = i+1
    print("Number:"+str(i))
    print('Title:'+title.string)
    f.write(str(i)+'\n')
    f.write('Title: '+title.string+'\n')
    pUrl = r'http://openaccess.thecvf.com/'+ (title.get('href'))
    pPage = request.Request(pUrl, headers=headers)
    pPage_info = request.urlopen(pPage).read()
    pPage_info = pPage_info.decode('utf-8')
    pSoup = BeautifulSoup(pPage_info, 'html.parser')
    pAbstracts = pSoup.find_all(id = 'abstract')
    for abstract in pAbstracts:
        #print(abstract.string[1:])
        f.write('Abstract: '+abstract.string[1:]+'\n')
    f.write('\n')
    f.write('\n')
f.close()



