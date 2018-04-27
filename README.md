一、注意函数fread，fwrite,read,write,fgets fputs gets puts sprintf,snprintf,fgetc fputc getchar putchar等的使用（APUE第五章）

二、accep函数：
int accept（int sockfd,struct sockaddr *cliaddr,socklen_t *addrlen)，常把它的第一个参数称为监听套接口，把它的返回值称为已连接套接口

三、有名管道通信：
有名管道间通信注意：1、程序不能以O_RDWR模式打开FIFO；2、mkfifo参数中是完整的路径名比如"/tmp/text"，而不能是"./text"，且不能是已经存在的文件；
3、阻塞问题
对于以只读方式（O_RDONLY）打开的FIFO文件，如果open调用是阻塞的（即第二个参数为O_RDONLY），除非有一个进程以写方式打开同一个FIFO，否则它不会返回；如果open调用是非阻塞的的（即第二个参数为O_RDONLY | O_NONBLOCK），则即使没有其他进程以写方式打开同一个FIFO文件，open调用将成功并立即返回。
对于以只写方式（O_WRONLY）打开的FIFO文件，如果open调用是阻塞的（即第二个参数为O_WRONLY），open调用将被阻塞，直到有一个进程以只读方式打开同一个FIFO文件为止；如果open调用是非阻塞的（即第二个参数为O_WRONLY | O_NONBLOCK），open总会立即返回，但如果没有其他进程以只读方式打开同一个FIFO文件，open调用将返回-1，并且FIFO也不会被打开。


四、 文件锁：1、当一个进程终止时，它所建立的锁全部释放，任何时候关闭一个描述符时，
             则该进程通过这一描述符可以存访的文件上的任何一把锁都被释放
          2、由fork产生的子程序不继承父进程所设置的锁
          3、在执行exec之后，新程序可以继承原来执行程序的锁
