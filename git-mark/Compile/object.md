#目标文件

##.text section 代码段
##.data section 数据段,存放已经初始化的全局变量和局部静态变量
##.bss  section 只是为未初始化的全局变量和局部变量预留位置,没有内容,不占文件大小

``` c++
gcc -c test.c
objdump -h test.o

test.o:     file format elf64-x86-64

Sections:
Idx Name           	      Size(长度)   VMA               LMA          File off(段偏移)  Algn
	0 .text        	    00000059  0000000000000000  0000000000000000  00000040  2**2
						CONTENTS, ALLOC, LOAD, RELOC, READONLY, CODE
	1 .data        		00000008  0000000000000000  0000000000000000  0000009c  2**2
				   		CONTENTS, ALLOC, LOAD, DATA
	2 .bss         		00000004  0000000000000000  0000000000000000  000000a4  2**2
				   		ALLOC
	3 .rodata      		00000004  0000000000000000  0000000000000000  000000a4  2**0
				   		CONTENTS, ALLOC, LOAD, READONLY, DATA
	4 .comment     		0000001d  0000000000000000  0000000000000000  000000a8  2**0
				   		CONTENTS, READONLY
	5 .note.GNU-stack   00000000  0000000000000000  0000000000000000  000000c5  2**0
				        CONTENTS, READONLY

ELF Header  0x00000000 ~ 0x00000040   40
text        0x00000040 ~ 0x0000009c   5c
rodata      0x0000009c ~ 0x000000a4    8
comment     0x000000a4 ~ 0x000000a8    4

rodata->只读信息段(程序中的只读变量,const 修饰的,字符串常量)-->只读
comment->注释信息段
note.GNU-stack->堆栈提示段

查看ELF文件的代码段,数据段和BSS段的长度(dec 3个段长度的和的十进制,hex 表示十六进制)
size test.o
text     data	 bss	dec	  hex	filename
181	      8	      4	    193	  c1	test.o

-s 将段内容以16进制的方式输出,-d 包含指令的段反汇编
objdump -s -d test.o
偏移量                32位内容                   ASNCII码
0000     554889e5 4883ec10 897dfc8b 45fc89c6  UH..H....}..E...

查看符号表
nm test.o
```

##ELF文件头
###包含描述整个文件的基本属性,比如ELF文件版本,目标机器型号,程序入口地址等
``` c++
readelf -h test.o

符号状态
readelf -s test.o
.symtab 符号表
```

##C++符号修饰,符号管理,函数签名
##强弱符号,强弱引用

