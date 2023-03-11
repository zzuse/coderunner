package panic_recover

import (
	"errors"
	"fmt"
	"os"
	"testing"
)

func TestPanicVxExit(t *testing.T) {
	defer func() {
		if err := recover(); err != nil {
			fmt.Println("Finally!", err)
		}
	}()
	fmt.Println("Start")
	panic(errors.New("Something wrong!"))
	os.Exit(-1)
}
