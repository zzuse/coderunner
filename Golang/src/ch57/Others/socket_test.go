package Others

import (
	"bufio"
	"crypto/tls"
	"fmt"
	"io"
	"net"
	"runtime"
	"syscall"
	"testing"
	"time"
)

func TestSocket(t *testing.T) {
	fd1, err := syscall.Socket(syscall.AF_INET, syscall.SOCK_STREAM, syscall.IPPROTO_TCP)
	if err != nil {
		fmt.Printf("socket error: %v\n", err)
		return
	}
	defer syscall.Close(fd1)
	fmt.Printf("The file descriptor of socket: %d\n", fd1)
}

func TestSocket2(t *testing.T) {
	network := "tcp"
	host := "google.ca"
	reqStrTpl := `HEAD / HTTP/1.1
Accept: */*
Accept-Encoding: gzip, deflate
Connection: keep-alive
Host: %s
User-Agent: Dialer/%s



`
	network1 := network + "4"
	address1 := host + ":80"
	fmt.Printf("Dial %q with network %q ...\n", address1, network1)
	conn1, err := net.Dial(network1, address1)
	if err != nil {
		fmt.Printf("dial error: %v\n", err)
		return
	}
	defer conn1.Close()

	reqStr1 := fmt.Sprintf(reqStrTpl, host, runtime.Version())
	fmt.Printf("The request:\n%s\n", reqStr1)
	_, err = io.WriteString(conn1, reqStr1)
	if err != nil {
		fmt.Printf("write error: %v\n", err)
		return
	}
	fmt.Println("Write done")
	fmt.Println("The response:")
	reader1 := bufio.NewReader(conn1)
	line1, err := reader1.ReadString('\n')
	if err != nil {
		fmt.Printf("read error: %v\n", err)
		return
	}
	fmt.Printf("The first line of response:\n%s\n", line1)
	fmt.Println()

	tlsConf := &tls.Config{
		InsecureSkipVerify: true,
		MinVersion:         tls.VersionTLS10,
	}
	network2 := network
	address2 := host + ":443"
	fmt.Printf("Dial %q with network %q ...\n", address2, network2)
	conn2, err := tls.Dial(network2, address2, tlsConf)
	if err != nil {
		fmt.Printf("dial error: %v\n", err)
		return
	}
	defer conn2.Close()

	reqStr2 := fmt.Sprintf(reqStrTpl, host, runtime.Version())
	fmt.Printf("The request:\n%s\n", reqStr2)
	_, err = io.WriteString(conn2, reqStr2)
	if err != nil {
		fmt.Printf("write error: %v\n", err)
		return
	}
	reader2 := bufio.NewReader(conn2)
	line2, err := reader2.ReadString('\n')
	if err != nil {
		fmt.Printf("read error: %v\n", err)
		return
	}
	fmt.Printf("The first line of response:\n%s\n", line2)
	fmt.Println()
}

type dialArgs struct {
	network string
	address string
	timeout time.Duration
}

func TestSocket3(t *testing.T) {
	dialArgsList := []dialArgs{
		{"tcp",
			"google.ca:80",
			time.Millisecond * 500},
		{"tcp",
			"google.ca:80",
			time.Second * 2},
		{
			"tcp",
			"google.ca:80",
			time.Minute * 4,
		},
	}
	for _, args := range dialArgsList {
		fmt.Printf("Dial %q with network %q and timeout %s...\n", args.address, args.network, args.timeout)
		ts1 := time.Now()
		conn, err := net.DialTimeout(args.network, args.address, args.timeout)
		ts2 := time.Now()
		fmt.Printf("Elapsed time: %s\n", time.Duration(ts2.Sub(ts1)))
		if err != nil {
			fmt.Printf("dial error: %v\n", err)
			fmt.Println()
			continue
		}
		defer conn.Close()
		fmt.Printf("The local address: %s\n", conn.LocalAddr())
		fmt.Printf("The remote address: %s\n", conn.RemoteAddr())
		fmt.Println()
	}
}
