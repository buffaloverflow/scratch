from bs4 import BeautifulSoup
import requests

ALLPRO_URL = "https://support.dlink.com/AllPro.aspx"
SINGLEPRO_URL = "http://www.dlink.com.cn/techsupport/ProductInfo.aspx?m="
SINGLEPRO_URL = "https://support.dlink.com/resource/PRODUCTS/"

r = requests.get(ALLPRO_URL)
soup = BeautifulSoup(r.text, features="html5lib")
prods = set(map(lambda x: x.get('alt'), soup.find_all(alt=True)))

print(prods)


for p in prods:
    url = SINGLEPRO_URL + p 
    print(url)
    r = requests.get(url)
    soup = BeautifulSoup(r.text, features="html5lib")
    reva = [x for x in soup.find_all('a') if "Parent" not in x.get_text()]
    
    print("*"*100)
    print(reva)
    break




