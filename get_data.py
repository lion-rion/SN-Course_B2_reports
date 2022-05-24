import requests
from bs4 import BeautifulSoup
from datetime import datetime, timedelta

load_url = "https://news.google.com/covid19/map?hl=ja&mid=%2Fm%2F03_3d&gl=JP&ceid=JP%3Aja"
html = requests.get(load_url)
soup = BeautifulSoup(html.content, "html.parser")

data = soup.find_all("div", class_="UvMayb")
data_2 = soup.find_all("td", class_="l3HOY")

today = data_2[6].text #新規感染者数
total = data[0].text #累計死亡者数
total_die = data[1].text #累計死亡者数

nowadays = datetime.now() #今日の日付
yesterday = nowadays - timedelta(1) #昨日の日付
date = yesterday.strftime('%Y年%-m月%-d日')
write_data = (date + " " + today + " " + total + " " + total_die + "\n").replace(",","") #カンマ削除

with open("data.csv", "r+") as f:
    original_data = f.read() #元データの読み込み
    f.seek(0)
    if(total.replace(",","") in original_data or date in original_data):
        print("***** 最新のデータは既に書き込まれています *****")
        exit
    else:
        f.write(write_data)
        f.write(original_data)

f.close()
