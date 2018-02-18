#!/usr/bin/env python
# -*- coding=utf-8 -*-
########################################################################
#    File Name: test_5.py
# 
#       Author: Thomas Shanghai,Inc.
#         Mail: 982737593@qq.com
# Created Time: 2018年02月18日 星期日 21时05分36秒
#  Description: ...
#                
########################################################################

from sys import argv

script, filename = argv

txt = open(filename)

print txt.read()
#read之后有一行回车作为间隔
#read 读文件, close 关闭文件, readline 读取一行, truncate清空文件, write(buff) buff写入文件
#error read a closed file
#open 可以加参数,exists(file) 判断文件是否存在,bool类型
#from os.path import exists
txt.close()

print txt.read()
