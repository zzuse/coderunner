package Others

import (
	"fmt"
	"net/http"
	"testing"
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
