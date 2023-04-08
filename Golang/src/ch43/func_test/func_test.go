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

func modifyArray(a [3]string) [3]string {
	a[1] = "x"
	return a
}

func TestArray(t *testing.T) {
	array1 := [3]string{"a", "b", "c"}
	fmt.Printf("The array: %v\n", array1)
	array2 := modifyArray(array1)
	fmt.Printf("The modified array: %v\n", array2)
	fmt.Printf("The original array: %v\n", array1)
}

func modifySlice(a []string) []string {
	a[1] = "1"
	return a
}

func TestSlice(t *testing.T) {
	slice1 := []string{"x", "y", "z"}
	fmt.Printf("The slice: %v\n", slice1)
	slice2 := modifySlice(slice1)
	fmt.Printf("The modified slice: %v\n", slice2)
	fmt.Printf("The original slice: %v\n", slice1)
}

func modifyComplexArray(a [3][]string) [3][]string {
	a[1][1] = "s"
	a[2] = []string{"o", "p", "q"}
	return a
}

func TestComplexArray(t *testing.T) {
	complexArray1 := [3][]string{
		[]string{"d", "e", "f"},
		[]string{"g", "h", "i"},
		[]string{"j", "k", "l"},
	}
	fmt.Printf("The com array %v\n", complexArray1)
	complexArray2 := modifyComplexArray(complexArray1)
	fmt.Printf("The modified: %v\n", complexArray2)
	fmt.Printf("The original: %v\n", complexArray1)
}
