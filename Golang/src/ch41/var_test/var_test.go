package var_test

import (
	"container/list"
	"container/ring"
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

var container = []string{"zero", "one", "two"}

func TestContainerType(t *testing.T) {
	container := map[int]string{0: "zero", 1: "one", 2: "two"}
	fmt.Printf("The element is %q.\n", container[1])
	value, ok := interface{}(container).([]string)
	if ok == true {
		print(value)
	} else if value == nil {
		print("not string slice")
	}
}

func TestSliceCapacity(t *testing.T) {
	s3 := []int{1, 2, 3, 4, 5, 6, 7, 8}
	s4 := s3[3:6]
	fmt.Printf("The length of s4: %d\n", len(s4))
	fmt.Printf("The capacity of s4: %d\n", cap(s4))
	fmt.Printf("The value of s4: %d\n", s4)
}

func TestList(t *testing.T) {
	var li list.List
	li.PushBack("1")
	front := li.Front()
	fmt.Println(front)
	li.InsertBefore(2, front)
	back := li.Back()
	li.InsertAfter("3", back)
	li.PushFront("4")
	li.PushBack("5")
	li.MoveAfter(front, back)
	li.MoveBefore(li.Back(), li.Front())
	li.MoveToFront(li.Back())
	li.MoveToBack(li.Front())
	fmt.Println(li.Front())

	fmt.Printf("List size is %d", li.Len())
}

func TestRing(t *testing.T) {
	var r ring.Ring
	fmt.Printf("Ring size is %d", r.Len())
}
