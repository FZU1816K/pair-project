#encoding: utf-8
import time
import requests
import multiprocessing
from multiprocessing import Queue,Process,Pool
from bs4 import BeautifulSoup
import re
import os
url = 'http://openaccess.thecvf.com/CVPR2018.py'
req_header={
'cookie':'ali_apache_id=10.182.248.22.1522458188584.201985.4; _ga=GA1.2.1071828404.1522458218; cna=BOauEnK3jgsCAdpqkRA8ZAr1; ali_beacon_id=10.182.248.22.1522458188584.201985.4; aep_common_f=6zjuRnKjk7c3XKoCZZomPDVKCClcrrEB2jRmApCafBCKewLn3OtE3g==; __utma=3375712.1071828404.1522458218.1523289317.1523289317.1; __utmz=3375712.1523289317.1.1.utmcsr=(direct)|utmccn=(direct)|utmcmd=(none); JSESSIONID=FF6YTN3RQ2-8L9UP81FVIR99ERSYGFT1-BPRNLBGJ-Z4S1; intl_locale=en_US; _gid=GA1.2.1277957881.1524449139; xman_f=oqOPOnn0p48KNgu7Kp081eedcMjzdePQ8MbULVw45ilvNbASfEeu9GTo1pZEglF1B48JQLQCjeFJWRA6S2N5d3EZS6YHXrcCx8tp1stNCFX1lo2y/rzZ3UPl20qUNtha8KiFHKPWmBasvuNLrnhvCe3nm2bzvqHJYKX9IvqeraW6QznNEPYvyeW2QZ1iDg0iBv1QFUVgJn5gd+qyYc31fugAmwNUxu/SOdZY6wV26sjEoheyRydsv8bOXyOTIagrIqnOi+6yZfTCPljJr4aA3fV6V/I8b1x4zysAAPqykeGVd/yOiRsEOorx5Es3m0+UQ+u8Bro4pJ0DN7HYGMArtCO77IICuTh8pEwaMlxQ/cwugcPpL9lZVb4BkpekuzzNfmjCZx++GLR2743cSqbP9w==; _mle_tmp0=eNrz4A12DQ729PeL9%2FV3cfUxiKnOTLFScnMziwzxMw4KNNK18LEMDbAwdAvzDLK0dA0KjnR3CzHUdQoI8vNxcvfSjTIJNlTSSS6xMjQ1MjExs7AwNDS0NNBJTEYTyK2wMqiNAgCDgh0R; xman_t=73hVz2RTQ3ZAPNwB+xJFeNvaqyopl597GdOPDHU7akB50LizM6Rb6JCwg+e/yKii; ali_apache_track=mt=1|mid=cn11763118lacae; ali_apache_tracktmp=W_signed=Y; aep_history=keywords%5E%0Akeywords%09%0A%0Aproduct_selloffer%5E%0Aproduct_selloffer%0932863047722%0932860321415%0932860496712%0932860636639%0932793159425%0932820026163%0932794645556%0932770006818; xman_us_f=x_l=0&x_locale=en_US&no_popup_today=n&x_user=CN|leo|magnus|ifm|1613410118&zero_order=y&last_popup_time=1523289316732; acs_usuc_t=acs_rt=1cb4733bc60749dc9f33f7a68a39345b&x_csrf=ukwp8w0ooc71; aep_usuc_f=region=US&site=glo&b_locale=en_US&isb=y&x_alimid=1613410118&c_tp=USD; intl_common_forever=riaQXbAzQoekt5ojj5ZJ/tg76KP0BkznKELoHeRw/vn79eLpeyXSYA==; isg=BHt7ClyapV_jppmIgyTnRrp5C19JyewexjF1fW048XqRzJuu9aAfIplN4myCbOfK',
'user-agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/65.0.3325.181 Safari/537.36'
}
i = 0
href = Queue()
def get_url():
    try:
        r = requests.get(url,headers=req_header)
        r.raise_for_status()
        r.encoding = r.status_code
        bsObj = BeautifulSoup(r.text,'lxml')
        for dt in bsObj.find_all('dt'):
            new_url = 'http://openaccess.thecvf.com/' + dt.a['href']
            href.put(new_url)
    except:
        print("error")
def get_message(myurl):
    try:
        global i

        title, abstract, authors, pdflink = get_abstract(myurl)
        with open('result.txt','a+',encoding='utf-8') as f:
            f.write(str(i) + '\n')
            f.write('Title: ' + title + '\n')
            f.write('Authors: ' + authors + '\n')
            f.write('Abstract: ' + abstract + '\n')
            f.write('PDF_LINK: '+ pdflink + '\n')
            f.write('\n\n')
        f.close()
        i += 1
        print("%s is crawled!" % myurl)
    except:
        print('error')

def get_abstract(newurl):
    try:
        r = requests.get(newurl,headers=req_header)
        r.raise_for_status()
        bsObj = BeautifulSoup(r.text,'lxml')
        pattern = re.compile('(.*)</div>')
        title = re.findall(pattern, r.text)
        title = bsObj.find_all('div',{'id':'papertitle'})[0].text
        abstract = bsObj.find_all('div',{'id':'abstract'})[0].text
        pattern = re.compile('.*<i>(.*)</i>')
        authors = re.findall(pattern, r.text)[0]
        pattern = re.compile('.*<a href="(.*)">pdf')
        pdflink = re.findall(pattern,r.text)[0].replace('../..','http://openaccess.thecvf.com')
        return title.replace('\n',''), abstract.replace('\n',''), authors, pdflink
    except:
        print("error")

if __name__ == '__main__':
    if os.path.exists('result.txt'):
        os.remove('result.txt')
    get_url()
    start = time.time()
    while not href.empty():
        get_message(href.get())
    # process = []
    # num_cpus = multiprocessing.cpu_count()
    # print('将会启动进程数为：', num_cpus)
    # while not href.empty():
    #     process.append(href.get())
    # p = Pool()
    # p.map(get_message, process)
    # p.close()
    # p.join()
    end = time.time()
    print("共计用时%.4f秒" %(end-start))

