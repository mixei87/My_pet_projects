from selenium import webdriver
from pathlib import Path
import requests
import time

URL = 'https://www.ubereats.com'

def scrape():
    # s = requests.session()
    # s.get(URL)
    # s.cookies.clear()
    options = webdriver.ChromeOptions()
    options.add_argument('Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) '
                         'Chrome/91.0.4472.106 YaBrowser/21.6.0.620 Yowser/2.5 Safari/537.36')
    path = Path('distrib', 'chromedriver.exe')
    driver = webdriver.Chrome(
        executable_path='PATH/distrib/chromedriver.exe', options=options
    )

    try:
        driver.get(URL)
        time.sleep(5)

        address_input = driver.find_element_by_id('location-typeahead-home-input')
        address_input.clear()
        address_input.send_keys('commonwealth ave 220')
        time.sleep(5)

    except Exception as ex:
        print(ex)
    finally:
        driver.close()
        driver.quit()

# Press the green button in the gutter to run the script.
if __name__ == '__main__':
    scrape()
