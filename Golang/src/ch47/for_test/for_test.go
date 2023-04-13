package for_test

import (
	"fmt"
	"testing"
)

func TestFooLoop(t *testing.T) {
	numbers1 := []int{1, 2, 3, 4, 5, 6}
	for i := range numbers1 {
		if i == 3 {
			numbers1[i] |= i
		}
	}
	fmt.Println(numbers1)
	fmt.Println()
}

func TestForLoopArray(t *testing.T) {
	numbers2 := [...]int{1, 2, 3, 4, 5, 6}
	maxIndex2 := len(numbers2) - 1
	for i, e := range numbers2 {
		if i == maxIndex2 {
			numbers2[0] += e
		} else {
			numbers2[i+1] += e
		}
	}
	fmt.Println(numbers2)
}

func TestForLoopSlice(t *testing.T) {
	numbers2 := []int{1, 2, 3, 4, 5, 6}
	maxIndex2 := len(numbers2) - 1
	for i, e := range numbers2 {
		if i == maxIndex2 {
			numbers2[0] += e
		} else {
			numbers2[i+1] += e
		}
	}
	fmt.Println(numbers2)
}

func TestSwitch(t *testing.T) {
	value1 := [...]int8{0, 1, 2, 3, 4, 5, 6}
	switch int8(1 + 3) {
	case value1[0], value1[1]:
		fmt.Println("0 or 1")
	case value1[2], value1[3]:
		fmt.Println("2 or 3")
	case value1[4], value1[5], value1[6]:
		fmt.Println("4 or 5 or 6")
	}
	//case表达式中子表达式的结果值是无类型的常量
	switch value1[4] {
	case 0, 1:
		fmt.Println("0 or 1")
	case 2, 3:
		fmt.Println("2 or 3")
	case 4, 5, 6:
		fmt.Println("4 or 5 or 6")
	}
	switch value1[4] {
	case value1[0], value1[1], value1[2]:
		fmt.Println("0 or 1 or 2")
	case value1[2], value1[3], value1[4]:
		fmt.Println("2 or 3 or 4")
	case value1[4], value1[5], value1[6]:
		fmt.Println("4 or 5 or 6")
	}
}

func TestSwitchInterface(t *testing.T) {
	value6 := interface{}(byte(127))
	switch t := value6.(type) {
	//case uint8:
	//	fmt.Println("uint8 ")
	case uint16:
		fmt.Println("unint16")
	case byte:
		fmt.Printf("byte")
	default:
		fmt.Printf("unsupported type: %T", t)
	}
}
