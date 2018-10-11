#!/usr/bin/env python
# coding: utf-8

# In[6]:


import requests
from urllib.request import urlopen
from bs4 import BeautifulSoup
txt = open (r'C:\Users\胖若两人\Desktop\result.txt' , 'w', encoding='utf-8' )
i=0
def getPaper (newsUrl) :
      res = requests. get (newsUrl)
      
      res. encoding = ' utf-8'

      soup =  BeautifulSoup (res. text, 'htm1. parser' )

      Title = soup. select( '#papertitle') [0]. text. strip()
      
      print("Title:", Title, file=txt)

      Abstract = soup. select( '#abstract' ) [0]. text. strip()
      
      print ( "Abstract:", Abstract,"\n\n" , file=txt)
      
      return

      sUr1 = 'http:// openaccess. thecvf. com/ CVPR2018. py'
      
      res1 = requests. get (sUrl)
     
      res1. encoding = 'utf-8'

      soup1 = BeautifulSoup (res1. text, 'htm1. parser' )
      
      for titles in soup1. select('. ptitle') :

          t ='http://openaccess thecvf. com/'+ titles. select( 'a' )[0][ 'href ']
          print(i, file=txt)
      
          getPaper (t)
      
          i=i+1

