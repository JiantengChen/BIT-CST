# Requests库项目源码说明
## 文件介绍
- __ init __.py
> import了对外暴露的变量名  
> 检查了库的版本  
> 对urllib3进行了设置
- __ version __.py
> 定义了版本信息，描述，作者，版权等信息
- _ internal_utils.py
> 定义了to_native_string和unicode_is_ascii两个函数
- adapters.py
> 定义了发送HTTP请求使用的接口。
- api.py
> 定义了Requests库的全部api接口，通过request作为入口
- auth.py
> 包含Requests库的authentication handler
- certs.py
> 返回默认的CA certificate bundle
- compat.py
> 兼容了python2和python3，对一些import的模块统一命名
- cookies.py
> 包含处理cookies的工具
- exceptions.py
> 定义了Requests库中的异常
- help.py
> 生成help信息
- hooks.py
> 定义了Requests库的hook系统
- models.py
> 定义了Request，PreparedRequest，Response三各类，分别对应了原始请求对象，要发送的请求对象，server的返回响应对象
- package.py
> 将urllibs3，idna，chardet重新引入
- sessions.py
> 提供了一个Session类和对象来处理request库的请求
- status_codes.py
> 定义codes全局变量，为dict，可用文字查找
- structures.py
> 定义支持Requests库的数据结构
- utils.py
> 工具函数

## Request库的请求流程
### Create Request
- 根据原始的请求参数创建相应的Request对象

### PreparedRequest
- 创建PreparedRequest对象，将请求的参数进行规范化处理

### Response
- 发送PreparedRequest，将返回的结果作为response

## Request请求的详细流程
1. 通过调用在api模块中封装的各种方法，发起HTTP请求
2. 返回一个Request对象，通过with函数实例化一个session对象
3. 对原始请求参数进行处理，在session中返回一个预处理之后用于初始化model层的一个request对象，同时Session类中维护了多个HTTPAdapter对象，分别用于处理不同请求
4. 在Session对象中，首先调用了prepare_request()将数据提前封装到PreparedRequest对象中，并进行对method，url等数据的预处理
    ```python
    Class PreparedRequest(...):
        ...
    def prepare(
            self,
            method=None,
            url=None,
            headers=None,
            files=None,
            data=None,
            params=None,
            auth=None,
            cookies=None,
            hooks=None,
            json=None,
        ):
            """Prepares the entire request with the given parameters."""

            self.prepare_method(method)
            self.prepare_url(url, params)
            self.prepare_headers(headers)
            self.prepare_cookies(cookies)
            self.prepare_body(data, files, json)
            self.prepare_auth(auth, url)
    ```
5. 通过调用Session.send()方法发送请求
6. 利用HTTPAdapter类发送请求并封装为Response对象
    ```python
        def send(
            self, request, stream=False, timeout=None, verify=True, cert=None, proxies=None
        ):
            """Sends PreparedRequest object. Returns Response object.

            :param request: The :class:`PreparedRequest <PreparedRequest>` being sent.
            :param stream: (optional) Whether to stream the request content.
            :param timeout: (optional) How long to wait for the server to send
                data before giving up, as a float, or a :ref:`(connect timeout,
                read timeout) <timeouts>` tuple.
            :type timeout: float or tuple or urllib3 Timeout object
            :param verify: (optional) Either a boolean, in which case it controls whether
                we verify the server's TLS certificate, or a string, in which case it
                must be a path to a CA bundle to use
            :param cert: (optional) Any user-provided SSL certificate to be trusted.
            :param proxies: (optional) The proxies dictionary to apply to the request.
            :rtype: requests.Response
            """
            ...
            return self.build_response(request, resp)
    ```