# 登陆爬虫项目介绍

## 文件介绍

### captcha3
- captcha3.py
> 为登录网站"https://captcha3.scrape.center/"的python源代码
- captcha3_screenshot.png
> 为登录过程中识别验证码的过程图片

### captcha8
- captcha8.py
> 为登录网站"https://captcha8.scrape.center/"的python源代码
- captcha8_screenshot.png
> 为登录过程中识别验证码的过程图片

### login2
- login2.py
> 为登录网站"https://login2.scrape.center/"的python源代码

## requirements介绍
### playwright
- 本项目采用playwright实现，在虚拟窗口中进行登录实验
### ddddocr
- 为本项目采用的图像识别库，基于opencv开发，但是通过率低，识别正确率低

## 源码介绍
### login2.py
- 略

### captcha8.py
```python
def login() -> None:
    """the function to login the page whose url is "https://captcha8.scrape.center/" automatically
    """
    p = sync_playwright().start()
    browser = p.chromium.launch(headless=False)
    page = browser.new_page()
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
```
- 因ddddocr库中文字识别模块有一定的错误率，故采用循环进行多次验证，直到登录成功

### captcha3.py
- 相比于前两个网站，本网站的缓冲速率较慢，且有概率无法加载出验证码界面，故本程序中采用了多出异常捕捉模块与循环
```python
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
    page = browser.new_page()
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
```
- 在跳出验证码界面之后，通过图像识别库识别文字所在的位置
- **最初预想通过识别图片验证码上的文字来判断点击顺序，但是因中文文字识别准确率太低，故采用暴力破解方式，按照在图片验证码中识别出文字的顺序进行点击，如失败则刷新验证码，直到成功登录**