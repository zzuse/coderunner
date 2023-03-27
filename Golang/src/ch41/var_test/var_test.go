package var_test

import (
	"flag"
	"fmt"
	"io"
	"os"
	"testing"
)

func TestFlagVar(t *testing.T) {
	var name string
	flag.StringVar(&name, "name", "everyone", "The greeting object.")
	flag.Parse()
	fmt.Printf("Hello, %v\n", name)
}

func TestFlagVar2(t *testing.T) {
	var name = flag.String("name", "everyone", "The greeting object.")
	flag.Parse()
	fmt.Printf("Hello, %v\n", *name)
}

func TestFlagVar3(t *testing.T) {
	name := flag.String("name", "everyone", "The greeting object.")
	flag.Parse()
	fmt.Printf("Hello, %v\n", *name)
}

func getTheFlag() *string {
	return flag.String("name", "everyone", "The greeting object.")
}

func TestFlagVar4(t *testing.T) {
	var name = getTheFlag()
	flag.Parse()
	fmt.Printf("Hello, %v\n", *name)
}

func TestReVar5(t *testing.T) {
	var err error
	n, err := io.WriteString(os.Stdout, "Hello, everyone!\n") // 这里对`err`进行了重声明。
	if err != nil {
		fmt.Printf("Error: %v\n", err)
	}
	fmt.Printf("%d byte(s) were written.\n", n)
}

func TestIntConv(t *testing.T) {
	var srcInt = int16(-255)
	disInt := int8(srcInt)
	fmt.Print(srcInt, disInt)
}
