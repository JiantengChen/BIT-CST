# 登录程序 位于login2.py文件 第7行

import time
from playwright.sync_api import sync_playwright


def login() ->None:
    """the function to login the page whose url is "https://login2.scrape.center/" automatically
    """
    with sync_playwright() as p:
        browser = p.chromium.launch(headless=False)
        page = browser.new_page(viewport={'width': 1280, 'height': 720})
        page.goto("https://login2.scrape.center/")
        page.locator("input[name=\"username\"]").click()
        page.locator("input[name=\"username\"]").fill("admin")
        page.locator("input[name=\"password\"]").click()
        page.locator("input[name=\"password\"]").fill("admin")
        page.locator("input:has-text(\"登录\")").click()
        time.sleep(20)


if __name__ == '__main__':
    login()
