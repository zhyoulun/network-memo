## 测试

```
$ go run udp_server.go
2020/03/28 22:21:06 start handle client, 127.0.0.1:12345
2020/03/28 22:21:11 read data: 12345
, length: 6, remote info: 127.0.0.1:47703
2020/03/28 22:21:11 end handle client, 127.0.0.1:12345
2020/03/28 22:21:11 start handle client, 127.0.0.1:12345
2020/03/28 22:21:20 read data: def
, length: 4, remote info: 127.0.0.1:56026
2020/03/28 22:21:20 end handle client, 127.0.0.1:12345
2020/03/28 22:21:20 start handle client, 127.0.0.1:12345
```

```
$ nc -u 127.0.0.1 12345
12345
```

```
$ nc -u 127.0.0.1 12345
def
```

只能在remote ip:port上对对端做区分

## 参考

- [Go socket编程实践: UDP服务器和客户端实现](https://colobu.com/2014/12/02/go-socket-programming-UDP/)