
import os
import re
import urllib
import requests
import sys
import time
from bs4 import BeautifulSoup

url = "http://openaccess.thecvf.com/CVPR2018.py#"
request = urllib.request.Request(url)
resulst = urllib.request.urlopen(request)
html = resulst.read()
html = html.decode('utf-8')
reg = r'<a href="(.+?\.html)">'
papRe=re.compile(reg)
paperlist = re.findall(papRe,html)
le=len(paperlist) 

context = open("result.txt","w",encoding='utf-8')
url_2="http://openaccess.thecvf.com/"
i=0
print (time.strftime('%Y-%m-%d %H:%M:%S',time.localtime(time.time())))
for i in range(le):
    papget = urllib.request.Request(url_2+paperlist[i])
    papRes = urllib.request.urlopen(papget)
    papRes = papRes.read()
    papRes = papRes.decode('utf-8')

    soup = BeautifulSoup(papRes,"html.parser")
    title= soup.select('#papertitle')
    abstr= soup.select('#abstract')
    context.write(str(i)+'\n')
    
    context.write('Title: '+title[0].text)
    context.write('\n')
    #print (title[0].text)
    #print ('\n')
    context.write('Abstract: '+abstr[0].text)
    context.write('\n')
    #print (abstr[0].text)
print (time.strftime('%Y-%m-%d %H:%M:%S',time.localtime(time.time())))     
print ("hello world")

