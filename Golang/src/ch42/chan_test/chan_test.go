package chan_test

import (
	"fmt"
	"testing"
)

func TestChan(t *testing.T) {
	ch1 := make(chan int, 3)
	ch1 <- 2
	ch1 <- 1
	ch1 <- 3
	elem1 := <-ch1
	fmt.Printf("The first element received from channel ch1: %v \n", elem1)
}

func TestChanBlock1(t *testing.T) {
	ch1 := make(chan int, 1)
	ch1 <- 1
	ch1 <- 2 // 通道已满，因此这里会造成阻塞。
}

func TestChanBlock2(t *testing.T) {
	// 示例2。
	ch2 := make(chan int, 1)
	elem, ok := <-ch2 // 通道已空，因此这里会造成阻塞。
	_, _ = elem, ok
	ch2 <- 1
}

func TestChanBlock3(t *testing.T) {
	// 示例3。
	var ch3 chan int
	ch3 <- 1 // 通道的值为nil，因此这里会造成永久的阻塞！
	<-ch3    // 通道的值为nil，因此这里会造成永久的阻塞！
	_ = ch3
}

func TestChanClose(t *testing.T) {
	ch1 := make(chan int, 2)
	// 发送方。
	go func() {
		for i := 0; i < 10; i++ {
			fmt.Printf("Sender: sending element %v...\n", i)
			ch1 <- i
		}
		fmt.Println("Sender: close the channel...")
		close(ch1)
	}()

	// 接收方。
	for {
		elem, ok := <-ch1
		if !ok {
			fmt.Println("Receiver: closed channel")
			break
		}
		fmt.Printf("Receiver: received an element: %v\n", elem)
	}

	fmt.Println("End.")
}
