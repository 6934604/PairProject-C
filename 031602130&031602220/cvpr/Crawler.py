import requests
import re
from bs4 import BeautifulSoup

#定义一个函数，用来爬取网页内容
def Web(www):
    try:
        w = requests.get(www)
        w.raise_for_status()
        w.encoding = w.apparent_encoding
    except:
        print("fail！！！")
    temp = w.text
    wz = BeautifulSoup(temp,"html.parser")
    return wz

www = "http://openaccess.thecvf.com/CVPR2018.py"
wz = Web(www)

#定义一个函数，用来论文页面内容
def info(paperLink):
    www = "http://openaccess.thecvf.com/" + paperLink
    wz = Web(www)
    #标签
    bq=re.compile('</?\w+[>]*>')
    #消除
    title =bq.sub('', str(wz.find('div',id="papertitle"))).strip()
    abstract = bq.sub('',str(wz.find('div',id="abstract"))).strip()
    return title,abstract

#print(wz)
papersInfo = wz.find_all('dt')
filename = 'result.txt'
count=0
with open(filename,'w',encoding='utf-8') as outfile:
    for paperInfo in papersInfo:
        title,abstract = info(paperInfo.find('a').get('href'))
        outfile.write(str(i)+'\r\n')
        count = count+1
        outfile.write('Title: '+title+'\r\n')
        outfile.write('Abstract: '+abstract+'\r\n\r\n\r\n')
