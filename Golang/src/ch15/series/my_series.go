package series

import "fmt"

// package name rule
// go mod init go_learning
// import "go_learning/src/ch15/xxx_package"

func GetFibonacciSerie(n int) []int {
	ret := []int{1, 1}
	for i := 2; i < n; i++ {
		ret = append(ret, ret[i-2]+ret[i-1])
	}
	return ret
}

// export fun name must bi Capitalized
func Square(n int) int {
	return n * n
}

// init is special default method
func init() {
	fmt.Println("init1")
}

// init can have multiple
func init() {
	fmt.Println("init2")
}
