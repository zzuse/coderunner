package groutine

import (
	"fmt"
	"testing"
	"time"
)

func TestGroutine(t *testing.T) {
	for i := 0; i < 10; i++ {
		// i is copied
		go func(i int) {
			fmt.Println(i)
		}(i)
	}
	time.Sleep(time.Millisecond * 50)
	for i := 0; i < 10; i++ {
		// i is shared
		go func() {
			fmt.Println(i)
		}()
	}
	time.Sleep(time.Millisecond * 50)
}
