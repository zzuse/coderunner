package cond_test

import (
	"log"
	"sync"
	"testing"
	"time"
)

func TestCond(t *testing.T) {
	// mailbox 代表信箱。
	// 0代表信箱是空的，1代表信箱是满的。
	var mailbox uint8
	// lock 代表信箱上的锁
	var lock sync.RWMutex
	// sendCond 代表专用于发信的条件变量
	sendCond := sync.NewCond(&lock)
	// recvCond 代表专用于收信的条件变量
	recvCond := sync.NewCond(lock.RLocker())
	sign := make(chan struct{}, 3)
	max := 5
	go func(max int) {
		defer func() {
			sign <- struct{}{}
		}()
		for i := 1; i <= max; i++ {
			time.Sleep(time.Millisecond * 500)
			lock.Lock()
			for mailbox == 1 {
				// below will UnLock lock, goroutine get suspended
				sendCond.Wait()
				// after will Lock() lock, goroutine will wake up
			}
			log.Printf("sender [%d]: the mailbox is empty.", i)
			mailbox = 1
			log.Printf("sender [%d]: the letter has been sent.", i)
			lock.Unlock()
			recvCond.Signal()
			//Wait方法总会把当前的 goroutine 添加到通知队列的队尾，
			//而它的Signal方法总会从通知队列的队首开始，查找可被唤醒的 goroutine
		}
	}(max)
	go func(max int) {
		defer func() {
			sign <- struct{}{}
		}()
		for j := 1; j <= max; j++ {
			time.Sleep(time.Millisecond * 500)
			lock.RLock()
			for mailbox == 0 {
				recvCond.Wait()
			}
			log.Printf("receiver [%d]: the mailbox is full.", j)
			mailbox = 0
			log.Printf("receiver [%d]: the letter has been receibed.", j)
			lock.RUnlock()
			sendCond.Signal()
		}
	}(max)
	<-sign
	<-sign
}

func TestCond2(t *testing.T) {
	var mailbox uint8
	var lock sync.Mutex
	// sendCond 代表专用于发信的条件变量。
	sendCond := sync.NewCond(&lock)
	// recvCond 代表专用于收信的条件变量。
	recvCond := sync.NewCond(&lock)

	// send 代表用于发信的函数。
	send := func(id, index int) {
		lock.Lock()
		for mailbox == 1 {
			sendCond.Wait()
		}
		log.Printf("sender [%d-%d]: the mailbox is empty.", id, index)
		mailbox = 1
		log.Printf("sender [%d-%d]: the letter has been sent.", id, index)
		lock.Unlock()
		recvCond.Broadcast()
	}

	recv := func(id, index int) {
		lock.Lock()
		for mailbox == 0 {
			recvCond.Wait()
		}
		log.Printf("receiver [%d-%d]: the mailbox is full.", id, index)
		mailbox = 0
		log.Printf("receiber [%d-%d]: the letter has been received.", id, index)
		lock.Unlock()
		sendCond.Signal()
	}

	sign := make(chan struct{}, 3)
	max := 6
	go func(id, max int) {
		defer func() {
			sign <- struct{}{}
		}()
		for i := 1; i <= max; i++ {
			time.Sleep(time.Millisecond * 500)
			send(id, i)
		}
	}(0, max)
	go func(id, max int) {
		defer func() {
			sign <- struct{}{}
		}()
		for j := 1; j <= max; j++ {
			time.Sleep(time.Millisecond * 200)
			recv(id, j)
		}
	}(1, max/2)
	go func(id, max int) {
		defer func() {
			sign <- struct{}{}
		}()
		for k := 1; k <= max; k++ {
			time.Sleep(time.Millisecond * 200)
			recv(id, k)
		}
	}(2, max/2)
	<-sign
	<-sign
	<-sign
}
