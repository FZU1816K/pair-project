#!/usr/bin/python
# -*- coding: utf-8 -*-
import  requests
import threading
from bs4 import BeautifulSoup
import re
import os
import time
#请求头字典
req_header={
'Accept': 'text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,image/apng,*/*;q=0.8',
'Accept-Encoding': 'gzip, deflate',
'Accept-Language': 'zh-CN,zh;q=0.9',
'Connection': 'keep-alive',
'Host':' openaccess.thecvf.com',
'Upgrade-Insecure-Requests': '1',
'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/68.0.3440.106 Safari/537.36'
}
def go(htmls):
    ff=open("result.txt","a+",encoding='utf-8')
    No=0
    for html in htmls:
        try:
            req_url=req_url_html+html
            #请求当前章节页面  params为请求参数
            r=requests.get(req_url,params=req_header) 
            #soup转换
            soup=BeautifulSoup(r.text,"html.parser")    
            #获取名称                                    
            #print(soup.select('#content #abstract')[0].text)
            section_name=soup.select('#content #papertitle')[0].text
            #获取文本
            section_text=soup.select('#content #abstract')[0].text
            #获取作者
            #section_person=soup.select('#content #authors i')[0].text
            #获取链接
            #section_abstract=req_url_base+'CameraReady/'+html+'.pdf'
            #格式转换
            section_namee=section_name.replace('\n',' ')
            section_textt=section_text.replace('\n',' ')
            #输出
            ff.write(str(No)+'\n')
            ff.write('Title:'+section_namee+'\n')
            #ff.write('Authors: '+section_person+'\n')
            ff.write('Abstract:'+section_textt+'\n')
            #ff.write('PDF_LINK: '+section_abstract+'\n')
            ff.write('\n')
            ff.write('\n')
            No=No+1
        except IndexError as e:   #抓取 IndexError 这个异常
            print(e) 
htmls=[]
req_url_base="http://openaccess.thecvf.com/content_cvpr_2018/"
req_url_html=req_url_base+'html/'
#req_url=req_url_base+"CVPR2018.py/"

r=requests.get(req_url_html,params=req_header)
soup=BeautifulSoup(r.text,'html.parser')
for i in range(980,1960):
    #print(soup.select('td a')[i].text+'\n')
    a=soup.select('td a')[i].text
    htmls.append(a)
go(htmls)