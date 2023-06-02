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
}
