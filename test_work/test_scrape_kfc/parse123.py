import json
import requests

URL = 'https://restaurant-api.wolt.com/v3/menus/6087b57ab8047605df987b9c'
HEADERS = {'user-agent': 'Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) '
                         'Chrome/90.0.4430.212 YaBrowser/21.5.3.740 Yowser/2.5 Safari/537.36'
           }
def scrape_data():
    html = get_html(URL)
    json_data = json.loads(html.text)
    return json_data["results"][0]["items"]

def get_html(url):
    r = requests.get(url=url, headers=HEADERS)
    return r

def parse():
    html_response = scrape_data()

    menu_result = []
    for i in html_response:
        menu_result.append(
            {
                'name': i["name"][0]["value"].strip(),
                'description': i["description"][0].get("value", "None").strip(),
                'price': float(i["baseprice"]/100),
                'image': i.get("image", "None").strip()
            }
        )

    with open("menu_result.json", "a", encoding="utf-8") as file:
        json.dump(menu_result, file, indent=4, ensure_ascii=False)

parse()
