package panic_test

import (
	"errors"
	"fmt"
	"testing"
)

func TestPanic(t *testing.T) {
	s1 := []int{0, 1, 2, 3, 4}
	e5 := s1[5]
	_ = e5
}

func TestCaller(t *testing.T) {
	fmt.Println("Enter funciton main.")
	caller1()
	fmt.Println("Exit functiion main.")
}

func caller1() {
	fmt.Println("Enter function caller1.")
	caller2()
	fmt.Println("Exit function caller1.")
}

func caller2() {
	fmt.Println("Enter function caller2.")
	s1 := []int{0, 1, 2, 3, 4}
	e5 := s1[5]
	_ = e5
	fmt.Println("Exit function caller2.")
}

func TestRecoverCanDoNothing(t *testing.T) {
	fmt.Println("Enter function main.")
	panic(errors.New("something wrong"))
	// panic happened, recover can do nothing
	p := recover()
	fmt.Printf("panic: %s\n", p)
	fmt.Printf("Exit function main.")
}

func TestDeferRecover(t *testing.T) {
	fmt.Println("Enter function main.")
	defer func() {
		fmt.Println("Enter defer function.")
		if p := recover(); p != nil {
			fmt.Printf("panic: %s\n", p)
		}
		fmt.Println("Exit defer function.")
	}()
	panic(errors.New("something wrong."))
	fmt.Println("Exit function main.")
}

func TestDeferOrder(t *testing.T) {
	// defer order is the stack order
	defer fmt.Println("first defer")
	for i := 0; i < 3; i++ {
		defer fmt.Printf("defer in for [%d]\n", i)
	}
	defer fmt.Println("last defer")
}
