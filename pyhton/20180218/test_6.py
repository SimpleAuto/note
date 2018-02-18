#!/usr/bin/env python
# -*- coding=utf-8 -*-
########################################################################
#    File Name: test_6.py
# 
#       Author: Thomas Shanghai,Inc.
#         Mail: 982737593@qq.com
# Created Time: 2018年02月18日 星期日 21时11分56秒
#  Description: ...
#                
########################################################################

def print_two(*args):
    arg1, arg2, arg3 = args
    print "arg1 %r, arg2 %r" % (arg1, arg2)

def print_two_again(arg1, arg2):
    print "arg1 %r, arg2 %r" % (arg1, arg2)
    
print_two(1,2,3)
print_two_again(1,2)
