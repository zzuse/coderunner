package goroutine_test

import (
	"fmt"
	"sync/atomic"
	"testing"
	"time"
)

func TestGoruotine(t *testing.T) {
	for i := 0; i < 10; i++ {
		go func() {
			fmt.Println(i)
		}()
	}
	//一旦主 goroutine 中的代码（也就是main函数中的那些代码）执行完毕，当前的 Go 程序就会结束运行。
	//如此一来，如果在 Go 程序结束的那一刻，还有 goroutine 未得到运行机会，那么它们就真的没有运行机会了
}

func TestChan(t *testing.T) {
	num := 10
	sign := make(chan struct{}, num)
	for i := 0; i < num; i++ {
		go func() {
			fmt.Println(i)
			sign <- struct{}{}
		}()
	}
	// method 1
	//time.Sleep(time.Millisecond * 500)
	// method 2
	for j := 0; j < num; j++ {
		<-sign
	}
}

func TestAtomic(t *testing.T) {
	var count uint32
	trigger := func(i uint32, fn func()) {
		for {
			if n := atomic.LoadUint32(&count); n == i {
				fn()
				atomic.AddUint32(&count, 1)
				break
			}
			time.Sleep(time.Nanosecond)
		}
	}
	for i := uint32(0); i < 10; i++ {
		go func(i uint32) {
			fn := func() {
				fmt.Println(i)
			}
			trigger(i, fn)
		}(i)
	}
	trigger(10, func() {})
}
