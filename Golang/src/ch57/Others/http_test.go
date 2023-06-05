package Others

import (
	"fmt"
	"log"
	"net/http"
	"strings"
	"sync"
	"testing"
	"time"
)

func TestHttp(t *testing.T) {
	host := "google.ca"

	url1 := "http://" + host
	fmt.Printf("Send request to %q\n", url1)
	resp1, err := http.Get(url1)
	if err != nil {
		fmt.Printf("Error: %v\n", err)
		return
	}
	defer resp1.Body.Close()
	line1 := resp1.Proto + " " + resp1.Status
	fmt.Printf("Response: %s\n", line1)
	fmt.Printf("Response: %q\n", line1)
	fmt.Println()

	url2 := "https://go.dev"
	fmt.Printf("Send request to %q\n", url2)
	var httpClient1 http.Client
	resp2, err := httpClient1.Get(url2)
	if err != nil {
		fmt.Printf("Error: %v\n", err)
		return
	}
	defer resp2.Body.Close()
	line2 := resp2.Proto + " " + resp2.Status
	fmt.Printf("Response: %s\n", line2)
}

var domains = []string{
	"google.com",
	"google.com.hk",
	"google.cn",
	"google.ca",
	"go.dev",
}

func TestHttp2(t *testing.T) {
	myTransport := &http.Transport{
		Proxy:                 http.ProxyFromEnvironment,
		MaxConnsPerHost:       2,
		MaxIdleConns:          10,
		MaxIdleConnsPerHost:   2,
		IdleConnTimeout:       30 * time.Second,
		ResponseHeaderTimeout: 0,
		ExpectContinueTimeout: 1 * time.Second,
		TLSHandshakeTimeout:   10 * time.Second,
	}
	myClient := http.Client{
		Transport: myTransport,
		Timeout:   20 * time.Second,
	}

	var wg sync.WaitGroup
	wg.Add(len(domains))
	for _, domain := range domains {
		go func(domain string) {
			var logBuf strings.Builder
			var diff time.Duration
			defer func() {
				logBuf.WriteString(
					fmt.Sprintf("(elapsed time: %s)\n", diff))
				fmt.Println(logBuf.String())
				wg.Done()
			}()
			url := "https://" + domain
			logBuf.WriteString(fmt.Sprintf("Send request to %q\n", url))
			t1 := time.Now()
			resp, err := myClient.Get(url)
			diff = time.Now().Sub(t1)
			if err != nil {
				logBuf.WriteString(fmt.Sprintf("Error: %v\n", err))
				return
			}
			defer resp.Body.Close()
			line2 := resp.Proto + " " + resp.Status
			logBuf.WriteString(fmt.Sprintf("Response: %s\n", line2))
		}(domain)
	}
	wg.Wait()
}

func startServer1(wg *sync.WaitGroup) {
	defer wg.Done()
	var httpServer1 http.Server
	httpServer1.Addr = "127.0.0.1:8080"
	if err := httpServer1.ListenAndServe(); err != nil {
		if err == http.ErrServerClosed {
			log.Println("HTTP server 1 closed.")
		} else {
			log.Printf("HTTP server 1 error: %v\n", err)
		}
	}
}

func startServer2(wg *sync.WaitGroup) {
	defer wg.Done()
	mux1 := http.NewServeMux()
	mux1.HandleFunc("/hi", func(w http.ResponseWriter, req *http.Request) {
		if req.URL.Path != "/hi" {
			http.NotFound(w, req)
			return
		}
		name := req.FormValue("name")
		if name == "" {
			fmt.Fprint(w, "Welcome!")
		} else {
			fmt.Fprintf(w, "Hi, %s!", name)
		}
	})

	httpServer2 := http.Server{
		Addr:    "127.0.0.1:8081",
		Handler: mux1,
	}
	if err := httpServer2.ListenAndServe(); err != nil {
		if err == http.ErrServerClosed {
			log.Println("HTTP server 2 closed.")
		} else {
			log.Printf("HTTP server 2 error: %v\n", err)
		}
	}
}

func TestHttp3(t *testing.T) {
	var wg sync.WaitGroup
	wg.Add(2)
	go startServer1(&wg)
	go startServer2(&wg)
	wg.Wait()
}
