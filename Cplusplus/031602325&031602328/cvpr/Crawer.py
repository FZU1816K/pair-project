# -*- coding: utf-8 -*-
"""
Created on Wed Oct 10 10:32:39 2018

@author: 14194
"""
from bs4 import BeautifulSoup
from urllib.request import urlopen
import re
from urllib import request
base_url = "http://openaccess.thecvf.com/CVPR2018.py"
html = urlopen(base_url).read().decode('utf-8')
soup = BeautifulSoup(html, features='lxml')
paper_link = soup.find_all('a', {'href': re.compile('content_cvpr_2018/html/.*')})
dic = dic2 = {}
num = 0
urllist = []
headers = {'User-Agent':'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/55.0.2883.87 Safari/537.36'}  
#if __name__ == '__main__':
for link in paper_link:
    url = 'http://openaccess.thecvf.com/'+link['href']
    urllist.append(url)
for url in urllist: 
    page = request.Request(url,headers=headers)  
    page_info = request.urlopen(page).read().decode('utf-8')
    soup1 = BeautifulSoup(page_info, 'html.parser')  
    papertitle = soup1.find('div', id='papertitle')
    abstract = soup1.find('div', id='abstract')
    titles = papertitle.string.strip() 
    abstracts = abstract.string.strip()
    dic2 = {titles:abstracts}
    dic.update(dic2)
with open('results.txt','a+',encoding='utf-8') as file:
    for k,v in dic.items():
        file.write(str(num)+'\n'+'Title: '+k+'\n'+'Abstract: '+v+'\n'+'\n'+'\n')
        num += 1
                        


                
              