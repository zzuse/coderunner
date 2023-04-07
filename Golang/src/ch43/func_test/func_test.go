package func_test

import (
	"errors"
	"fmt"
	"testing"
)

type Printer func(contents string) (n int, err error)

func printToStd(contents string) (bytesNum int, err error) {
	return fmt.Println(contents)
}

func TestFunc(t *testing.T) {
	var p Printer
	p = printToStd
	p("something")
}

type operate func(x, y int) int
type calculateFunc func(x, y int) (int, error)

func calculate(x int, y int, op operate) (int, error) {
	if op == nil {
		return 0, errors.New("invalid operation")
	}
	return op(x, y), nil
}

func genCalculator(op operate) calculateFunc {
	return func(x int, y int) (int, error) {
		if op == nil {
			return 0, errors.New("invalid operation")
		}
		return op(x, y), nil
	}
}

func TestAdd(t *testing.T) {
	op := func(x, y int) int {
		return x + y
	}
	x, y := 56, 78
	result, err := calculate(x, y, op)
	fmt.Printf("The result: %d (error: %v\n", result, err)
	add := genCalculator(op)
	result, err = add(x, y)
	fmt.Printf("The result: %d (error: %v\n", result, err)
}
