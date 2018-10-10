#!/usr/bin/python
# -*- coding: utf-8 -*-

from bs4 import BeautifulSoup
import bs4
import requests
import codecs

URL="http://openaccess.thecvf.com/CVPR2018.py"
INPUT_SAVE_PATH="input.txt"

if __name__ == '__main__':
	#爬取论文列表页面
	heads = {}
	heads['User-Agent'] = 'Mozilla/5.0 (Windows NT 10.0; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/49.0.2623.221 Safari/537.36 SE 2.X MetaSr 1.0'
	response=requests.get(URL,headers=heads)
	html=response.text
	#解析论文列表页面
	soup=BeautifulSoup(html, 'html.parser')
	#找出所有标签是dt的部份
	soup_texts=soup.find_all('dt')
	#打开文件
	f=codecs.open('input.txt','w','utf-8')
	count=0
	#循环的找出每一篇论文的超链，通过超链进入论文页面并解析页面
	for paperlink in soup_texts:
		download_url=paperlink.find('a')
		download_url='http://openaccess.thecvf.com/'+download_url['href']
		download_response=requests.get(download_url,headers=heads)
		download_html=download_response.text
		download_soup=BeautifulSoup(download_html, 'html.parser')
		#通过标签找出title和abstract文本
		papertitle=download_soup.find('div', id = 'papertitle')
		abstract=download_soup.find('div', id = 'abstract')
		papertitle=papertitle.text[1:]
		abstract=abstract.text[1:]
		#输入到文件中
		f.write(str(count)+'\n'+'Title: '+papertitle+'\n'+'Abstract: '+abstract+'\n'+'\n'+'\n')
		count+=1
		print(str(count)+'\n')
	f.close()