package main

import (
	"fmt"
	"log"
	"net"
)

func main() {
	addr := "127.0.0.1:12345"
	laddr, err := net.ResolveUDPAddr("udp", addr)
	if err != nil {
		log.Fatalf("net ResolveUDPAddr fail, err=%+v\n", err)
	}
	conn, err := net.ListenUDP("udp", laddr)
	if err != nil {
		log.Fatalf("net ListenUDP fail, err=%+v\n", err)
	}
	defer conn.Close()

	for {
		handleClient(conn)
	}
}

func handleClient(conn *net.UDPConn) {
	info := conn.LocalAddr().String()
	log.Printf("start handle client, %s\n", info)
	defer log.Printf("end handle client, %s\n", info)

	buf := make([]byte, 1024)
	n, remoteAddr, err := conn.ReadFromUDP(buf)
	if err != nil {
		fmt.Printf("conn ReadFromUDP fail, err=%+v\n", err)
		return
	}
	log.Printf("read data: %s, length: %d, remote info: %s\n", string(buf), n, remoteAddr.String())
}
