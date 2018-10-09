import re
import urllib.request
from bs4 import BeautifulSoup

if __name__ == "__main__":

    f = open("result.txt", 'a', encoding='utf-8')
    html1 = urllib.request.urlopen("http://openaccess.thecvf.com/CVPR2018.py").read()
    bf1 = BeautifulSoup(html1)
    texts1 = bf1.select('.ptitle')
    a_bf = BeautifulSoup(str(texts1))
    a = a_bf.find_all('a')
    urls = []
    for each in a:
        urls.append("http://openaccess.thecvf.com/" + each.get('href'))

    for i in range(len(urls)):
        f.write(str(i))  # 自动换行
        f.write("\n")
        html2 = urllib.request.urlopen(urls[i]).read()
        bf = BeautifulSoup(html2)
        texts2 = bf.find_all('div', id='papertitle')
        f.write("Title: " + texts2[0].text.lstrip('\n') + "\n")  # 使用text属性，提取文本内容，滤除br标签

        texts3 = bf.find_all('div', id='abstract')
        f.write("Abstract: " + texts3[0].text.lstrip('\n') + "\n\n\n")

