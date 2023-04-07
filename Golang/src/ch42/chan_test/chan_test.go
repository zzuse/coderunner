package chan_test

import (
	"fmt"
	"math/rand"
	"testing"
	"time"
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

func SendInt(ch chan<- int) {
	ch <- rand.Intn(1000)
	ch <- rand.Intn(1000)
	fmt.Printf("random")
}

func getIntChan() <-chan int {
	num := 5
	ch := make(chan int, num)
	for i := 0; i < num; i++ {
		ch <- i
	}
	close(ch)
	return ch
}

type GetIntChan func() <-chan int

func TestInChan(t *testing.T) {
	var uselessChan = make(chan<- int, 1)
	var anotherUselessChan = make(<-chan int, 1)
	fmt.Printf("The useless channels: %v, %v\n", uselessChan, anotherUselessChan)

	intChan1 := make(chan int, 3)
	SendInt(intChan1)

	intChan2 := getIntChan()
	for elem := range intChan2 {
		fmt.Printf("The element in intChan2: %v\n", elem)
	}
	_ = GetIntChan(getIntChan)
}

func TestOutChan(t *testing.T) {
	intChannels := [3]chan int{
		make(chan int, 1),
		make(chan int, 1),
		make(chan int, 1),
	}

	index := rand.Intn(3)
	fmt.Printf("The index: %d\n", index)
	intChannels[index] <- index
	select {
	case <-intChannels[0]:
		fmt.Printf("The first \n")
	case <-intChannels[1]:
		fmt.Printf("The second \n")
	case elem := <-intChannels[2]:
		fmt.Printf("The third is %d \n", elem)
	default:
		fmt.Printf("No candidate is selected! ")
	}
}

func TestChanCloseBlock(t *testing.T) {
	intChan := make(chan int, 1)
	time.AfterFunc(time.Second, func() {
		close(intChan)
	})
	select {
	case _, ok := <-intChan:
		if !ok {
			fmt.Println("The chan closed")
			break
		}
		fmt.Println("The candidate case is selected.")
	}
}
