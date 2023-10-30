# 登录程序 位于captcha8.py文件 第9行

import time
from playwright.sync_api import sync_playwright
import ddddocr



def login() -> None:
    """the function to login the page whose url is "https://captcha8.scrape.center/" automatically
    """
    p = sync_playwright().start()
    browser = p.chromium.launch(headless=False)
    page = browser.new_page(viewport={'width': 1280, 'height': 720})
    page.goto("https://captcha8.scrape.center/")

    page.locator("form div:has-text(\"用户名\") input[type=\"text\"]").click()
    page.locator("form div:has-text(\"用户名\") input[type=\"text\"]").fill("admin")

    page.locator("input[type=\"password\"]").click()
    page.locator("input[type=\"password\"]").fill("admin")

    ocr = ddddocr.DdddOcr(beta=True)
    
    while (page.locator("role=heading[name=\"登录成功\"]").count()==0):
        
        page.locator('#captcha').click()
        page.locator("form div:has-text(\"验证码\") input[type=\"text\"]").click()
        page.locator('#captcha').screenshot(path='captcha8\captcha8_screenshot.png')
        with open('captcha8\captcha8_screenshot.png', 'rb') as f:
            image = f.read()
        res = ocr.classification(image)
        page.locator("form div:has-text(\"验证码\") input[type=\"text\"]").fill(res)
        page.locator("[type=\"button\"]").click()

    time.sleep(15)


if __name__ == '__main__':
    login()
