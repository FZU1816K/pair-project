
# coding: utf-8

# In[1]:


import requests
from bs4 import BeautifulSoup 
from urllib.request import urlopen


# In[2]:


i = 1
File=open(r'C:\Users\Ming\Desktop\result.txt','w',encoding='utf-8')


# In[3]:


def getHTMLText(url):
    try:
        r = requests.get(url)
        r.raise_for_status()
        r.encoding = 'utf-8'
        return r.text
    except:
        return ""


# In[4]:


def getMessage(url):
    html=getHTMLText(url)
    soup = BeautifulSoup(html,'html.parser')
    Title = soup.select('#papertitle')[0].text.strip()#消除空格
    Abstract = soup.select('#abstract')[0].text.strip()#消除空格
    print("Title:",Title,file=File)
    print("Abstract:",Abstract,file=File)
    print("\n",file=File)


# In[5]:


url = 'http://openaccess.thecvf.com/CVPR2018.py'
shtml = getHTMLText(url)
ssoup = BeautifulSoup(shtml,'html.parser')
for titles in ssoup.select('.ptitle'):
    print(i,file=File)
    i = i + 1
    durl="http://openaccess.thecvf.com/"+titles.select('a')[0]['href']
    getMessage(durl)

