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

func TestContainerList(t *testing.T) {
	var li list.List
	fmt.Printf("List original size is %d\n", li.Len())
	li.PushBack("1")
	front := li.Front()
	li.InsertAfter("3", front)
	back := li.Back()
	li.InsertBefore("2", back)
	li.MoveToBack(li.Front())
	li.MoveBefore(li.Back(), li.Front())
	li.PushFront("5")
	li.PushBack("4")
	front = li.Front()
	back = li.Back()
	li.MoveAfter(front, back)
	li.MoveAfter(li.Front(), li.Back())
	li.MoveToFront(li.Back())

	fmt.Printf("List size is %d\n", li.Len())
	for i := li.Front(); i != nil; i = i.Next() {
		fmt.Print(i)
	}
}

func TestRing(t *testing.T) {
	var r ring.Ring
	fmt.Printf("Ring original size is %d\n", r.Len())
	r1 := ring.New(3)
	head1 := r1
	r1.Value = "apple"
	r1 = r1.Next()
	r1.Value = "banana"
	r1 = r1.Next()
	r1.Value = "cherry"

	r2 := ring.New(2)
	head2 := r2
	r2.Value = "pear"
	r2 = r2.Next()
	r2.Value = "Orange"

	r1.Link(head2)
	fmt.Printf("Ring 1 size is %d\n", head1.Len())
	fmt.Printf("Ring 2 size is %d\n", head2.Len())
	head1.Do(func(x interface{}) {
		fmt.Println(x)
	})
	head2.Do(func(x interface{}) {
		fmt.Println(x)
	})
}
