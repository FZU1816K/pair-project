from bs4 import BeautifulSoup
import bs4                                              # bs4.element.Tag
import requests
import os
import pickle
import os
import codecs
import time
import random

BASE_URL = "http://openaccess.thecvf.com"
CVPR_URL_TEXT = "cvpr_url_text.data"
RESULT_SAVE_PATH = "result.txt"
PAPAER_SAVE_DIR = "papers"

if not os.path.exists(PAPAER_SAVE_DIR):
    os.mkdir(PAPAER_SAVE_DIR)


error_list = []
result_io = codecs.open("result.txt", "w", "utf-8")


def getHTMLText(url):
    kv = {'user-agent': 'Mozilla/5.0'}                  # user-agent
    try:
        r = requests.get(url, headers=kv, timeout=30)
        r.raise_for_status()
        r.encoding = r.apparent_encoding
        return r.text
    except:
        print("[-]Error")
        return ""


def getPaperUrlLists():
    # 得到CVPR官网的HTML信息
    if os.path.exists(CVPR_URL_TEXT):
        # 如果本地已有 即从本地加载
        print("[+]从本地加载cvpr_url_text中...")
        with open(CVPR_URL_TEXT, "rb") as f:
            cvpr_url_text = pickle.load(f)
            print("[+]cvpr_url_text加载成功")
    else:
        # 没有本地html信息 爬取CVPR页面
        print("[ ]正在爬取CVPR页面")
        url = "http://openaccess.thecvf.com/CVPR2018.py"
        cvpr_url_text = getHTMLText(url)
        print("[+]CVPR页面爬取成功")
        
        with open(CVPR_URL_TEXT, "wb") as f:
            pickle.dump(cvpr_url_text, f)
            print("[+]成功将cvpr_url_text保存在本地")


    # 得到bs4实例
    soup = BeautifulSoup(cvpr_url_text, "html.parser")

    # 根据bs4得到paper_url_list
    count = 0
    paper_url_list = []

    # 查找content
    content = soup.find(id="content")
    for child in content.descendants:
        # 在content的子孙节点中寻找dt标签
        if child.name == "dt":
            for _child in child.children:
                if _child.name == "a":
                    count += 1
                    paper_url = BASE_URL + "/" + _child["href"]
                    paper_url_list.append(paper_url)

    print("[+]共查找到{}篇论文 ".format(count))
    return paper_url_list


def getPaperInfo(paper_url, counts):
    paper_save_path = os.path.join(PAPAER_SAVE_DIR, str(counts))
    if not os.path.exists(paper_save_path):
        print("[ ]尝试爬取论文")
        urlText = getHTMLText(paper_url)
        if urlText == "":
            print("[ ]尝试二次爬取论文")
            urlText = getHTMLText(paper_url)
        if urlText == "":
            print("[ ]爬取失败")
            error_list.append(counts)
            return
        with open(paper_save_path, "wb") as f:
            pickle.dump(urlText, f)
    else:
        print("[ ]从本地加载文件中")
        with open(paper_save_path, "rb") as f:
            urlText = pickle.load(f)

    soup = BeautifulSoup(urlText, "html.parser")

    try:
        for child in soup.find_all(id=["papertitle", "abstract", "authors"]):
            if child["id"] == "papertitle":
                title = child.string[1:]
            elif child["id"] == "abstract":
                abstract = child.string[1:]
            elif child["id"] == "authors":
                authors = child.find("i").string
        result_io.write("{}\nTitle: {}\nAbstract: {}\n\n\n".format(count, title, abstract))
    except:
        print("[-]发生未知错误")
    
    


if __name__ == '__main__':
    # 得到所有论文的url链接
    paper_url_lists = getPaperUrlLists()

    # 爬取paper_url_lists中每一个论文所在的页面
    count = 0
    for paper_url in paper_url_lists:
        print("\n[ ]开始处理第{:4d}篇论文".format(count))
        getPaperInfo(paper_url, count)
        print("[+]第{:4d}篇论文处理结束".format(count))
        count += 1

    result_io.close()

    print("[-]错误列表:")
    print(error_list)