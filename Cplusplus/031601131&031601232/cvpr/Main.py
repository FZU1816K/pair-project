from bs4 import BeautifulSoup
from urllib.request import urlopen
import re
import random
filename = 'data.txt'
base_url = "http://openaccess.thecvf.com/CVPR2018.py"
b_url="http://openaccess.thecvf.com/"
html = urlopen(base_url).read().decode('utf-8')
soup = BeautifulSoup(html, features='lxml')
sub_urls = soup.find_all("a", { "href": re.compile("content_cvpr_2018/html/(.)+CVPR_2018_paper.html$")})
k=len(sub_urls)
print(k)
with open(filename,'w',encoding='utf-8') as f:
    for i in range (5):
        his=sub_urls[i]['href']
        url= b_url + his
        html2 = urlopen(url).read().decode('utf-8')
        soup2 = BeautifulSoup(html2, features='lxml')
        sub_urls2 = soup2.find_all("div",id="papertitle")
        sub_urls3 = soup2.find_all("div",id="abstract")
        j=str(i)
        f.write(j)
        f.write('\n')
        f.write("Title:"+sub_urls2[0].text.lstrip('\n'))
        f.write('\n')
        f.write("Abstract:"+sub_urls3[0].text.lstrip('\n'))
        f.write('\n')
        f.write("\n\n\n")
