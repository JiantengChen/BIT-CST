import requests
from lxml import etree
import threading
import csv

infoList = []


def url_create():
    """用于生成包含链家北京租房信息从1到30页网页链接的列表

    Returns:
        _type_: 返回一个包含链家北京租房信息从1到100页网页链接的列表
    """
    url_base = "https://bj.lianjia.com/zufang/pg{}"
    links = [url_base.format(i) for i in range(1, 31)]
    return links


def parsePage(url):
    """爬取并对爬取下来的html文本进行数据筛选与清洗,将一个包含[房源标题,房源地址,其他信息]的列表添加到infoList表中

    Args:
        url (string): 链家单独页面的链接
    """

    html = requests.get(url=url).text
    tree = etree.HTML(html)
    li_List = tree.xpath("//*[@class=\"content__list--item--main\"]")
    lock = threading.RLock()
    lock.acquire()
    for li in li_List:
        title = li.xpath(
            "./p/a/text()")[0].strip('\"').strip("\n").replace(" ", "")
        position_ls = li.xpath("./p/a/text()")[1:]
        position = "".join(position_ls)
        extra_info_ls = li.xpath(
            "./p[@class=\"content__list--item--des\"]/text()")
        extra_info = ""
        for item in extra_info_ls:
            item = item.strip('\"').strip(
                "\n").replace(" ", "").replace("\n", "")
            if '-' in item:
                item = item.replace('-', "")
            extra_info += (item+' ')
        title += " " + extra_info.strip(' ')
        infoList.append([title, position])
    lock.release()


def main():
    """程序的主函数,运行时将爬取链接网页上1-100页的数据
    """

    links = url_create()
    for item in links:
        x = threading.Thread(target=parsePage, args=(item,))
        x.start()
    x.join()
    with open("infoList.csv", 'w', encoding="utf-8", newline="") as f:
        writer = csv.writer(f)
        writer.writerows(infoList)


if __name__ == '__main__':
    main()
