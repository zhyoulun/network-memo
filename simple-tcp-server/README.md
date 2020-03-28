## 测试用例

启动服务端

```
go run tcp_server.go
```

接收服务端消息

```
telnet 127.0.0.1 12345
```

发送消息到服务端

```
echo hello | nc 127.0.0.1 12345
```

## 测试1

```
$ telnet 127.0.0.1 12345
Trying 127.0.0.1...
Connected to 127.0.0.1.
Escape character is '^]'.
2020-03-28 20:55:39
2020-03-28 20:55:41
2020-03-28 20:55:43
2020-03-28 20:55:45
^]

telnet> quit
Connection closed.
```

```
2020/03/28 20:55:39 start write cycle, conn info: localAddr: 127.0.0.1:12345, remoteAddr: 127.0.0.1:58844
2020/03/28 20:55:39 start read cycle, conn info: localAddr: 127.0.0.1:12345, remoteAddr: 127.0.0.1:58844
2020/03/28 20:55:39 write data: 2020-03-28 20:55:39, write length: 20
2020/03/28 20:55:41 write data: 2020-03-28 20:55:41, write length: 20
2020/03/28 20:55:43 write data: 2020-03-28 20:55:43, write length: 20
2020/03/28 20:55:45 write data: 2020-03-28 20:55:45, write length: 20
2020/03/28 20:55:47 write data: 2020-03-28 20:55:47, write length: 20
2020/03/28 20:55:47 conn Read fail, err=EOF
2020/03/28 20:55:47 end read cycle, conn info: localAddr: 127.0.0.1:12345, remoteAddr: 127.0.0.1:58844
2020/03/28 20:55:47 conn Close success at readCycle
2020/03/28 20:55:49 conn Write fail, err=write tcp 127.0.0.1:12345->127.0.0.1:58844: use of closed network connection
2020/03/28 20:55:49 end write cycle, conn info: localAddr: 127.0.0.1:12345, remoteAddr: 127.0.0.1:58844
2020/03/28 20:55:49 conn Close fail at writeCycle, err=close tcp 127.0.0.1:12345->127.0.0.1:58844: use of closed network connection
```

read cycle先结束，conn被关闭，write cycle尝试写数据，报错use of closed network connection

## 测试2

不主动关闭conn，即注释如下代码

```
if err := conn.Close(); err != nil {
    log.Printf("conn Close fail at readCycle, err=%+v\n", err)
} else {
    log.Printf("conn Close success at readCycle\n")
}

if err := conn.Close(); err != nil {
    log.Printf("conn Close fail at writeCycle, err=%+v\n", err)
} else {
    log.Printf("conn Close success at writeCycle\n")
}
```

```
$ telnet 127.0.0.1 12345
Trying 127.0.0.1...
Connected to 127.0.0.1.
Escape character is '^]'.
2020-03-28 21:01:06
2020-03-28 21:01:08
2020-03-28 21:01:10
2020-03-28 21:01:12
^]

telnet> quit
Connection closed.
```

```
2020/03/28 21:01:03 listen 127.0.0.1:12345
2020/03/28 21:01:06 start write cycle, conn info: localAddr: 127.0.0.1:12345, remoteAddr: 127.0.0.1:59794
2020/03/28 21:01:06 write data: 2020-03-28 21:01:06, write length: 20
2020/03/28 21:01:06 start read cycle, conn info: localAddr: 127.0.0.1:12345, remoteAddr: 127.0.0.1:59794
2020/03/28 21:01:08 write data: 2020-03-28 21:01:08, write length: 20
2020/03/28 21:01:10 write data: 2020-03-28 21:01:10, write length: 20
2020/03/28 21:01:12 write data: 2020-03-28 21:01:12, write length: 20
2020/03/28 21:01:14 write data: 2020-03-28 21:01:14, write length: 20
2020/03/28 21:01:14 conn Read fail, err=EOF
2020/03/28 21:01:16 conn Write fail, err=write tcp 127.0.0.1:12345->127.0.0.1:59794: write: broken pipe
2020/03/28 21:01:16 end write cycle, conn info: localAddr: 127.0.0.1:12345, remoteAddr: 127.0.0.1:59794
```

telnet退出，read cycle退出，write cycle尝试write，报错broken pipe，write cycle退出

## 参考

- [Sending a simple TCP message using Netcat](https://askubuntu.com/questions/443227/sending-a-simple-tcp-message-using-netcat)
- [Go socket编程实践: TCP服务器和客户端实现](https://colobu.com/2014/12/02/go-socket-programming-TCP/)