## 1.实践简介

基于往年的 NBA 的各项比赛统计数据，实现针对2021-2022年每场比赛，预测比赛中哪支队伍最终将会获胜，并和真实值进行比较。  

数据来源：<https://www.basketball-reference.com/>  

数据详情：  

2018-2019Team Per Game Stats.csv：每支队伍在每场比赛中的表现统计。各字段含义如下：  
![](https://icode-image.oss-cn-beijing.aliyuncs.com/94ad5130d18ecbdb01c7b363b62cdb98.png)

2018-2019Opponent Per Game Stats.csv：每支队伍在每场比赛中遇到的对手表现统计。各字段含义同上。  

![](https://icode-image.oss-cn-beijing.aliyuncs.com/94ad5130d18ecbdb01c7b363b62cdb98.png)

2018-2019Miscellaneous Stats.csv：每支队伍的综合统计数据。各字段含义如下：  

![](https://icode-image.oss-cn-beijing.aliyuncs.com/4e7918d2cda3b73d08de4c74a340690f.png)

2018-2019_result.csv：每场比赛的数据。其中包括三个字段：  

* WTeam: 比赛胜利队伍
* LTeam: 失败队伍
* WLoc: 胜利队伍一方所在的为主场或是客场

2019-2020_schedule.csv：比赛的安排。其中包括两个字段：  

* Vteam: 客场作战队伍
* Hteam: 主场作战队伍

## 2.相关概念

比赛结果预测是一个典型的二分类问题。机器学习中常见的二分类模型有：逻辑回归、支持向量机、XGBoost、随机森林、人工神经网络等。  
选取以上任意一种进行训练。  

最终利用训练好的模型在2020-2021年的比赛数据中进行预测。对每一场新的比赛进行胜负方判断，最好能返回胜方胜利的概率。  

Jupyter是一个非营利组织，旨在“为数十种编程语言的交互式计算开发开源软件，开放标准和服务”。  

2014年由Fernando Pérez从IPython中衍生出来，Jupyter支持几十种语言的执行环境。Jupyter项目开发并支持交互式计算产品Jupyter Notebook（文件格式是.ipynb文件）、JupyterHub和JupyterLab。  

> <https://jupyter.org/>  

## 3.文件说明

```text
main.ipynb      数据分析文件
```

## 4.提交内容

相关程序分析代码，分析说明内嵌在Jupyter Notebook中，使用markdown格式编写。

## 5.如何评判

* 程序是否能够执行
* 程度代码是否规范
