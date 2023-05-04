package wait_group_test

import (
	"context"
	"errors"
	"fmt"
	"sync"
	"sync/atomic"
	"testing"
	"time"
)

func coordinateWithChan() {
	sign := make(chan struct{}, 2)
	num := int32(0)
	fmt.Printf("The number: %d [with chan struct{}]\n", num)
	max := int32(10)
	go addNum(&num, 1, max, func() {
		sign <- struct{}{}
	})
	go addNum(&num, 2, max, func() {
		sign <- struct{}{}
	})
	<-sign
	<-sign
}

func coordinateWithWaitGroup() {
	var wg sync.WaitGroup
	wg.Add(2)
	num := int32(0)
	fmt.Printf("The number: %d [with sync.WaitGroup]\n", num)
	max := int32(10)
	go addNum(&num, 3, max, wg.Done)
	go addNum(&num, 4, max, wg.Done)
	wg.Wait()
}

func addNum(numP *int32, id, max int32, deferFunc func()) {
	defer func() {
		deferFunc()
	}()
	for i := 0; ; i++ {
		currNum := atomic.LoadInt32(numP)
		if currNum >= max {
			break
		}
		newNum := currNum + 2
		time.Sleep(time.Millisecond * 200)
		if atomic.CompareAndSwapInt32(numP, currNum, newNum) {
			fmt.Printf("The number: %d [%d-%d]\n", newNum, id, i)
		} else {
			fmt.Printf("The CAS operation failed. [%d-%d]\n", id, i)
		}
	}
}

func coordinateWithWaitGroup2() {
	var total int32 = 12
	var stride int32 = 3
	var num int32
	fmt.Printf("The number: %d [with sync.WaitGroup]\n", num)
	var wg sync.WaitGroup
	var i int32 = 1
	var j int32 = 0
	for i = 1; i <= total; i = i + stride {
		wg.Add(int(stride))
		for j = 0; j < stride; j++ {
			go addNum(&num, i+j, 12, wg.Done)
		}
		wg.Wait()
	}
	fmt.Println("End.")
}

func coordinateWithContext() {
	var total int32 = 12
	var num int32
	var i int32
	fmt.Printf("The number: %d [with context.Context]\n", num)
	cxt, cancelFunc := context.WithCancel(context.Background())
	for i = 1; i <= total; i++ {
		go addNum(&num, i, 12, func() {
			if atomic.LoadInt32(&num) == total {
				cancelFunc()
			}
		})
	}
	<-cxt.Done()
	fmt.Println("End.")
}

func TestWaitGroup(t *testing.T) {
	coordinateWithChan()
	fmt.Println()
	coordinateWithWaitGroup()
	fmt.Println()
	coordinateWithWaitGroup2()
	fmt.Println()
	coordinateWithContext()
}

func TestWaitGroupOnce(t *testing.T) {
	// 1
	var counter uint32
	var once sync.Once
	once.Do(func() {
		atomic.AddUint32(&counter, 1)
	})
	fmt.Printf("The counter: %d\n", counter)
	once.Do(func() {
		atomic.AddUint32(&counter, 2)
	})
	fmt.Printf("The counter: %d\n", counter)
	fmt.Println()

	// 2
	once = sync.Once{}
	var wg sync.WaitGroup
	wg.Add(3)
	go func() {
		defer wg.Done()
		once.Do(func() {
			for i := 0; i < 3; i++ {
				fmt.Printf("Do task. [1-%d]\n", i)
				time.Sleep(time.Second)
			}
		})
		fmt.Println("Done. [1]")
	}()
	go func() {
		defer wg.Done()
		time.Sleep(time.Millisecond * 500)
		once.Do(func() {
			fmt.Println("Do task.[2]")
		})
		fmt.Println("Done. [2]")
	}()
	go func() {
		defer wg.Done()
		time.Sleep(time.Millisecond * 500)
		once.Do(func() {
			fmt.Println("Do task. [3]")
		})
		fmt.Println("Done. [3]")
	}()
	wg.Wait()
	fmt.Println()

	// 3
	once = sync.Once{}
	wg.Add(2)
	go func() {
		defer wg.Done()
		defer func() {
			if p := recover(); p != nil {
				fmt.Printf("fatal error: %v\n", p)
			}
		}()
		once.Do(func() {
			fmt.Println("Do task. [4]")
			panic(errors.New("something wrong"))
			fmt.Println("Done. [4]")
		})
	}()
	go func() {
		defer wg.Done()
		time.Sleep(time.Millisecond * 500)
		once.Do(func() {
			fmt.Println("Do task. [5]")
		})
		fmt.Println("Done [5]")
	}()
	wg.Wait()
}
