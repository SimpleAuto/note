#操作系统部分基础概念

##SMP:对称多处理器,cpu之间完全相同,最佳场合,服务器和需要处理大量计算的环境
##多核处理器实际上就是简化版的SMP,只有1个处理器,多个核心

##系统调用接口在实现中依赖于软件中断, Linux(0x80)
##操作系统的主要功能,提供抽象的接口和管理硬件资源

##多道程序,简单的调度算法,没有优先级
##分时系统,每个程序运行时间以后都主动让出CPU给其他程序,使得一段时间内每个程序都有机会运行一小段时间
##多任务系统,系统接管了所有的硬件资源,并且本身运行在一个受硬件保护的级别,所有的应用程序都以进程的方式运行,可以抢占CPU

##进程隔离,每个进程都有自己独立的虚拟空间,而且每个进程只能访问自己的地址空间
###分段,对内存区域的映射按照程序为单位,如果内存不足,整个程序都会被交换到磁盘空间
###分页,把地址空间人为地等分成固定大小的页,每一页的大小由硬件决定,由操作系统选择决定页的大小
####虚拟页,虚拟空间的页,物理页,磁盘中的页,虚拟地址转换为物理地址依赖于MMU进行页映射

##线程,轻量级进程,是程序执行流的最小单元,由线程ID,当前指令指针(PC),寄存器集合和堆栈组成
###I/O密集型线程总是比CPU密集型线程容易得到优先级的提升

##同步与锁
###同步,即指在一个线程访问数据未结束的时候,其他线程不得对同一个数据进行访问
###互斥量,使用--,释放++,谁使用谁释放
###临界区,一个访问共用资源(例如：共用设备或是共用存储器)的程序片段
###读写锁,读不冲突,写唯一
###条件变量,条件满足,所有依赖于这个条件变量的进程可以同时进行
###防止过度优化,volatile,阻止编译器将变量写入寄存器后,下次使用直接读取寄存器的值,阻止编译器调整volatile变量的指令顺序
###使用barrier()函数,确保调用点之上的执行顺序在调用点之下的前面
