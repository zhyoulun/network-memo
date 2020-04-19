package main

import (
	"fmt"
	"log"
	"net"
	"time"
)

func main() {
	addr := "127.0.0.1:12345"
	ln, err := net.Listen("tcp", addr)
	if err != nil {
		log.Fatalf("net Listen fail, err=%+v\n", err)
	}
	defer ln.Close()
	log.Printf("listen %s\n", addr)
	for {
		conn, err := ln.Accept()
		if err != nil {
			log.Printf("ln Accept fail, err=%+v\n", err)
			continue
		}
		go readCycle(conn)
		go writeCycle(conn)
	}
}

// 从客户端读取消息
func readCycle(conn net.Conn) {
	connInfo := fmt.Sprintf("localAddr: %s, remoteAddr: %s", conn.LocalAddr().String(), conn.RemoteAddr().String())
	log.Printf("start read cycle, conn info: %s\n", connInfo)

	buf := make([]byte, 1024)
	for {
		n, err := conn.Read(buf)
		if err != nil {
			log.Printf("conn Read fail, err=%+v\n", err)
			break
		}
		if n > 0 {
			log.Printf("read data: %s, read length: %d\n", string(buf), n)
		}
	}

	log.Printf("end read cycle, conn info: %s\n", connInfo)
	if err := conn.Close(); err != nil {
		log.Printf("conn Close fail at readCycle, err=%+v\n", err)
	} else {
		log.Printf("conn Close success at readCycle\n")
	}
}

//每两秒发送消息到客户端
func writeCycle(conn net.Conn) {
	connInfo := fmt.Sprintf("localAddr: %s, remoteAddr: %s", conn.LocalAddr().String(), conn.RemoteAddr().String())
	log.Printf("start write cycle, conn info: %s\n", connInfo)

	for {
		msg := time.Now().Format("2006-01-02 15:04:05")
		n, err := conn.Write([]byte(msg + "\n"))
		if err != nil {
			log.Printf("conn Write fail, err=%+v\n", err)
			break
		} else {
			log.Printf("write data: %s, write length: %d\n", msg, n)
		}
		time.Sleep(2 * time.Second)
	}

	log.Printf("end write cycle, conn info: %s\n", connInfo)
	if err := conn.Close(); err != nil {
		log.Printf("conn Close fail at writeCycle, err=%+v\n", err)
	} else {
		log.Printf("conn Close success at writeCycle\n")
	}
}
