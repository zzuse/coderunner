package var_test

import (
	"flag"
	"fmt"
	"testing"
)

func TestVar(t *testing.T) {
	var name string
	flag.StringVar(&name, "name", "everyone", "The greeting object.")
	flag.Parse()
	fmt.Printf("Hello, %v\n", name)
}
