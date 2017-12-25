# mmap()函数的使用方法

## 函数声明(来源于 Linux man手册)
``` c++
#include <sys/mman.h>
void *mmap(void *addr, size_t length, int prot, int flags,int fd, off_t offset);
```

## 函数描述
mmap() creates a new mapping in the virtual address space of the calling process.The starting address for the new mapping is specified in addr.The length argument specifies the length of the mapping.

If addr is NULL, then the kernel chooses the address at which to create the mapping; this is the most portable method of creating a new mapping.  If addr is not NULL, then the kernel takes it as a hint about where to place the mapping; on Linux, the mapping will be created at a nearby page boundary.  The address of the new mapping is returned as the result of the call.

The  contents of a file mapping (as opposed to an anonymous mapping; see MAP_ANONYMOUS below), are initialized using length bytes starting at offset offset in the file (or other object) referred to by the file descriptor fd.  offset must be a multiple of the page size as returned by sysconf(_SC_PAGE_SIZE).

The prot argument describes the desired memory protection of the mapping (and must not conflict with the open mode of the file).  It is either PROT_NONE or the bitwise OR of one or more of the fol‐lowing flags:


=============================================================================

mmap()创建了一个新的映射在调用进程的虚拟地址空间,在新的映射的起始地址是指定的地址(addr),长度由参数length决定.

如果传入的addr参数是NULL,那么内核会选择创建映射的地址;这是创建一个新的映射最便捷的方法.如果传入的addr参数不为NULL,那么内核会把它作为一个提示在创建映射的时候,用来说明放置映射位置;在Linux上,映射将被创建位于页界附近.新映射的地址作为调用的结果返回.

一个文件映射的内容(与匿名映射截然相反;具体参考下面的MAP_ANONYMOUS),在文件描述符fd中引用的文件(或其他对象)的偏移偏移量参数中根据长度字节进行初始化.偏移量必须是由sysconf(scpagesize)返回的页面大小的倍数.

prot参数描述了映射的期望内存保护(并且不应该与文件的打开模式冲突).它要么是原生的,要么是位的,或者是一个或多个折叠的标志.

=============================================================================

## 参数说明

void *addr    : 指定映射的起始地址,传NULL时表示由系统决定映射区的起始地址.

size_t length : 映射区的长度,长度单位是 以字节为单位,不足一内存页按一内存页处理.

int prot      : 期望的内存保护标志,不能与文件的打开模式冲突.

int flags     : 指定映射对象的类型,映射选项和映射页是否可以共享.

int fd        : 文件描述符.

off_t offset  : 被映射对象内容的偏移量.

### prot参数说明
- PROT_EXEC  Pages may be executed.------> 页内容可执行
- PROT_READ  Pages may be read.----------> 页内容可读
- PROT_WRITE Pages may be written.-------> 页内容可写
- PROT_NONE  Pages may not be accessed.--> 页内容不可访问

### flags参数说明
- MAP_FIXED : 使用指定的映射起始地址,如果由addr和len参数指定的内存区重叠于现存的映射空间,重叠部分将会被丢弃.如果指定的起始地址不可用,操作将会失败,并且起始地址必须落在页的边界上.
- MAP_NORESERVE : 不要为这个映射保留交换空间.当交换空间被保留,对映射区修改的可能会得到保证.当交换空间不被保留,同时内存不足,对映射区的修改会引起段违例信号.
- MAP_LOCKED : 锁定映射区的页面,从而防止页面被交换出内存.
- MAP_GROWSDOWN : 用于堆栈,告诉内核VM系统,映射区可以向下扩展.
- MAP_ANONYMOUS : 匿名映射,映射区不与任何文件关联.
- MAP_ANON : MAP_ANONYMOUS的别称,不再被使用.
- MAP_FILE : 兼容标志,被忽略.
- MAP_32BIT : 将映射区放在进程地址空间的低2GB,MAP_FIXED指定时会被忽略.当前这个标志只在x86-64平台上得到支持.
- MAP_POPULATE : 为文件映射通过预读的方式准备好页表.随后对映射区的访问不会被页违例阻塞.
- MAP_NONBLOCK : 仅和MAP_POPULATE一起使用时才有意义.不执行预读,只为已存在于内存中的页面建立页表入口.

=============================================================================

## 函数返回

On success, mmap() returns a pointer to the mapped area. On error, the value MAP_FAILED(that is, (void *) -1) is returned, and errno is set appropriately.

成功执行时，mmap()返回被映射区的指针.

失败的时候, mmap()返回MAP_FAILED[(void *)-1],并且设置errno.

- EACCES: 访问出错
- EAGAIN: 文件已被锁定，或者太多的内存已被锁定
- EBADF: fd不是有效的文件描述词
- EINVAL: 一个或者多个参数无效
- ENFILE: 已达到系统对打开文件的限制
- ENODEV: 指定文件所在的文件系统不支持内存映射
- ENOMEM: 内存不足，或者进程已超出最大内存映射数量
- EPERM:  权能不足，操作不允许
- ETXTBSY:  已写的方式打开文件，同时指定MAP_DENYWRITE标志
- SIGSEGV:  试着向只读区写入
- SIGBUS: 试着访问不属于进程的内存区

=============================================================================

##### --author:thomas
##### --date:2017.10.23
