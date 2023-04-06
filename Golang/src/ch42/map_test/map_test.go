package map_test

import (
	"fmt"
	"testing"
)

func TestMap(t *testing.T) {
	aMap := map[string]int{
		"one":   1,
		"two":   2,
		"three": 3,
	}
	k := "two"
	v, ok := aMap[k]
	if ok {
		fmt.Printf("The element of key %q: %d\n", k, v)
	} else {
		fmt.Println("Not found!")
	}
	delete(aMap, k)
	println(aMap["two"])
	aMap["two"] = v
	println(aMap["two"])
}

func TestBadMap(t *testing.T) {
	var badMap2 = map[interface{}]int{
		"1":      1,
		[]int{2}: 2, // 这里会引发panic。
		3:        3,
	}
	fmt.Print(badMap2)
}
