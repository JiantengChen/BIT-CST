# 登录程序 位于captcha3.py文件 第30行

import time
from typing import Dict
from playwright.sync_api import sync_playwright
import ddddocr
import cv2


def image_detection(image_path: str, det, poses: Dict) -> None:
    """the function to analyse the captcha picture

    Args:
        image_path (str): a string written image path 
        det (_type_): det
        poses (Dict): a hashtable used to store the coordinate where the character exist
    """
    with open(image_path, 'rb') as f:
        image = f.read()
    poses[image_path] = det.detection(image)

    im = cv2.imread(image_path)
    for box in poses[image_path]:
        x1, y1, x2, y2 = box
        im = cv2.rectangle(im, (x1, y1), (x2, y2),
                           color=(0, 0, 255), thickness=2)
    cv2.imwrite(image_path, im)


def login() -> None:
    """the function to login the page whose url is "https://captcha3.scrape.center/" automatically
    """

    p = sync_playwright().start()
    browser = p.chromium.launch(headless=False)
    page = browser.new_page(viewport={'width': 1280, 'height': 720})
    page.goto("https://captcha3.scrape.center/")
    page.locator("form div:has-text(\"用户名\") input[type=\"text\"]").click()
    page.locator(
        "form div:has-text(\"用户名\") input[type=\"text\"]").fill("admin")
    page.locator("input[type=\"password\"]").click()
    page.locator("input[type=\"password\"]").fill("admin")
    while(1):
        try:
            page.locator("role=button[name=\"登录\"]").click(timeout=50)
            page.wait_for_load_state("networkidle")
        except:
            break

    det = ddddocr.DdddOcr(det=True)

    def pic_recognition() -> None:
        """the function that screenshot the captcha picture for follow-up operation
        """
        time.sleep(1)
        page.locator(".geetest_item_wrap >> nth=0").screenshot(
            path='captcha3\captcha3_screenshot.png')
        image_detection("captcha3\captcha3_screenshot.png", det, poses)

    def captcha3_operation():
        """attempt to crack the captcha 
        """
        while(1):
            try:
                poses.clear()
                pic_recognition()
                for item in poses["captcha3\captcha3_screenshot.png"]:
                    q, w, e, r = item
                    x = (q+e)/2
                    y = (w+r)/2
                    page.mouse.click(486.725+x, 188.355+y)
                page.locator("[aria-label=\"提交\"]").click(timeout=100)
                time.sleep(1.5)
                page.mouse.click(100, 100)
                time.sleep(1.5)
                page.locator("role=button[name=\"登录\"]").click(timeout=100)
            except:
                print("Successfully Login the website https:captcha3.scrape.center, now breaking")
                break
            
    poses = {}  
    captcha3_operation()



if __name__ == '__main__':
    login()
