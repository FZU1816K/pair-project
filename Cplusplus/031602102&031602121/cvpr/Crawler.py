import requests
import re
from bs4 import BeautifulSoup

def getWebInfo(url):#获取网页中的内容
    try:
        r = requests.get(url)
        r.raise_for_status()
        r.encoding = r.apparent_encoding
    except:
        print("request error")
    demo = r.text
    soup = BeautifulSoup(demo,"html.parser")
    return soup

def getPaperInfo(paperLink):#获取论文主页的内容
    url = "http://openaccess.thecvf.com/" + paperLink
    soup = getWebInfo(url)
    re_h=re.compile('</?\w+[^>]*>')#HTML标签
    #利用正则表达式去除网页内容中的标签
    title =re_h.sub('', str(soup.find('div',id="papertitle"))).strip()
    abstract = re_h.sub('',str(soup.find('div',id="abstract"))).strip()
    author = re_h.sub('',str(soup.find('i'))).strip().split(', ')
    return title,abstract,author
    

url = "http://openaccess.thecvf.com/CVPR2018.py"
soup = getWebInfo(url)
#print(soup)
papersInfo = soup.find_all('dt')
filename = 'result.txt'
i=0
with open(filename,'w',encoding='utf-8') as outfile:
    for paperInfo in papersInfo:
        title,abstract,author = getPaperInfo(paperInfo.find('a').get('href'))
        outfile.write(str(i)+'\r\n')
        i = i+1
        outfile.write('Title: '+title+'\r\n')
        outfile.write('Abstract: '+abstract+'\r\n\r\n\r\n')
