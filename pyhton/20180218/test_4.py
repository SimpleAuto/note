#!/usr/bin/env python
# -*- coding=utf-8 -*-
########################################################################
#    File Name: test_4.py
# 
#       Author: Thomas Shanghai,Inc.
#         Mail: 982737593@qq.com
# Created Time: 2018年02月18日 星期日 20时58分28秒
#  Description: ...
#                
########################################################################

#exec this file
#python test_4.py 1 2 3
#test_4.py->script, 1->first...
from sys import argv

script, first, second, third = argv

print "script %s" % script
print "first  %s" % first
print "second %s" % second
print "third  %s" % third
