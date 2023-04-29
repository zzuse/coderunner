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
				sendCond.Wait()
			}
			log.Printf("sender [%d]: the mailbox is empty.", i)
			mailbox = 1
			log.Printf("sender [%d]: the letter has been sent.", i)
			lock.Unlock()
			recvCond.Signal()
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
