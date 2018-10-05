# coding:utf-8

import os
import re
import urllib
from selenium import webdriver
from bs4 import BeautifulSoup

# 调试的时候用firefox比较直观
# self.driver = webdriver.PhantomJS()
driver = webdriver.Edge()
driver.get("http://conferences.computer.org/cvpr/2018/#!/toc/0")
soup = BeautifulSoup(driver.page_source)  # 返回的HTML


###########################Only Type#####################################

#
# f = open('./Only_Type.txt', 'a',encoding='utf-8')
#
# for t in soup.find_all('a',class_='text-bold ng-binding'):
#      k=t.parent.parent.find('h3').text
#      if re.search('O',k):
#          f.write('Oral\n')
#      elif re.search('S\d',k):
#          f.write('Spotlight\n')
#      elif re.search('P',k):
#          f.write('Poster\n')
#
# f.close()

###########################Type#####################################
# f = open('./Type.txt', 'a',encoding='utf-8')
#
# for t in soup.find_all("h3",class_='text-bold ng-binding h5',id=re.compile(r'O\d')):
#     p=t.parent.find_all('div')
#     for p1 in p:
#         if p1:
#             for k in p1.find_all('a',class_='text-bold ng-binding'):
#                 f.write('Title: ')
#                 f.write(k.next_element)
#                 f.write('\r\n')
#                 f.write('Type: Oral')
#                 f.write('\r\n')
#
# for t in soup.find_all("h3",class_='text-bold ng-binding h5',id=re.compile(r'S\d')):
#     p=t.parent.find_all('div')
#     for p1 in p:
#         if p1:
#             for k in p1.find_all('a',class_='text-bold ng-binding'):
#                 f.write('Title: ')
#                 f.write(k.next_element)
#                 f.write('\r\n')
#                 f.write('Type: Spotlight')
#                 f.write('\r\n')
#
# for t in soup.find_all("h3",class_='text-bold ng-binding h4'):
#     p=t.parent.find_all('div')
#     for p1 in p:
#         if p1:
#             for k in p1.find_all('a',class_='text-bold ng-binding'):
#                 f.write('Title: ')
#                 f.write(k.next_element)
#                 f.write('\r\n')
#                 f.write('Type: Poster')
#                 f.write('\r\n')
#
# f.close()
################################################################


#############################Author###################################
f = open('./Authors.txt', 'a',encoding='utf-8')

for author in soup.find_all('em', class_='ng-binding'):
#    print(author.text)
    f.write(author.text)

f.close()
################################################################
driver.close()
