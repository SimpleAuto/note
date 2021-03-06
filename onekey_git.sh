#!/usr/bin/env bash
########################################################################
#    File Name: onekey_git.sh
# 
#       Author: Thomas Shanghai,Inc.
#         Mail: 982737593@qq.com
# Created Time: 2017年09月16日 星期六 19时50分09秒
#  Description: ...
# 
########################################################################

dir=$PWD
ls_date=`date "+%Y-%m-%d %H:%M:%S"`
echo $ls_date;
echo $dir;
echo "==========================================================================="
git pull origin master
echo "==========================================================================="
echo -e "\033[31m git pull origin master \033[0m" "\033[32m [OK] \033[0m"
git add $dir
echo "==========================================================================="
echo -e "\033[31m git add $dir \033[0m" "\033[32m [OK] \033[0m"
echo "==========================================================================="
git commit -m "$ls_date"  $dir
echo "==========================================================================="
echo -e "\033[31m git commit -m \"$ls_date\" $dir \033[0m" "\033[32m [OK] \033[0m"
echo "==========================================================================="
git push -u origin master
echo "==========================================================================="
echo -e "\033[31m git push -u origin master\033[0m" "\033[32m [OK] \033[0m"
echo "==========================================================================="
