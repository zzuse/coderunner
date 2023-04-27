package mutex

import (
	"bytes"
	"errors"
	"fmt"
	"io"
	"log"
	"sync"
	"testing"
	"time"
)

type singleHandler func() (data string, n int, err error)

type handlerConfig struct {
	handler   singleHandler
	goNum     int
	number    int
	interval  time.Duration
	counter   int
	counterMu sync.Mutex
}

func (hc *handlerConfig) count(increment int) int {
	hc.counterMu.Lock()
	defer hc.counterMu.Unlock()
	hc.counter += increment
	return hc.counter
}

func TestMutex2(t *testing.T) {
	var mu sync.Mutex
	genWriter := func(writer io.Writer) singleHandler {
		return func() (data string, n int, err error) {
			data = fmt.Sprintf("%s\t", time.Now().Format(time.StampNano))
			mu.Lock()
			defer mu.Unlock()
			n, err = writer.Write([]byte(data))
			return
		}
	}

	genReader := func(reader io.Reader) singleHandler {
		return func() (data string, n int, err error) {
			buffer, ok := reader.(*bytes.Buffer)
			if !ok {
				err = errors.New("unsupported reader")
				return
			}
			mu.Lock()
			defer mu.Unlock()
			data, err = buffer.ReadString('\t')
			n = len(data)
			return
		}
	}

	var buffer bytes.Buffer
	writingConfig := handlerConfig{
		handler:  genWriter(&buffer),
		goNum:    5,
		number:   4,
		interval: time.Millisecond * 100,
	}
	readingConfig := handlerConfig{
		handler:  genReader(&buffer),
		goNum:    10,
		number:   2,
		interval: time.Millisecond * 100,
	}
	sign := make(chan struct{}, writingConfig.goNum+readingConfig.goNum)

	for i := 1; i <= writingConfig.goNum; i++ {
		go func(i int) {
			defer func() {
				sign <- struct{}{}
			}()
			for j := 1; j <= writingConfig.number; j++ {
				time.Sleep(writingConfig.interval)
				data, n, err := writingConfig.handler()
				if err != nil {
					log.Printf("writer [%d-%d]: error: %s", i, j, err)
					continue
				}
				total := writingConfig.count(n)
				log.Printf("writer [%d-%d]: %s (total:%d)", i, j, data, total)
			}
		}(i)
	}

	for i := 1; i <= readingConfig.goNum; i++ {
		go func(i int) {
			defer func() {
				sign <- struct{}{}
			}()
			for j := 1; j <= readingConfig.number; j++ {
				time.Sleep(readingConfig.interval)
				var data string
				var n int
				var err error
				for {
					data, n, err = readingConfig.handler()
					if err == nil || err != io.EOF {
						break
					}
					time.Sleep(readingConfig.interval)
				}
				if err != nil {
					log.Printf("reader [%d-%d]: error: %s", i, j, err)
					continue
				}
				total := readingConfig.count(n)
				log.Printf("reader [%d-%d]: %s (total: %d)", i, j, data, total)
			}
		}(i)
	}

	signNumber := writingConfig.goNum + readingConfig.goNum
	for j := 0; j < signNumber; j++ {
		<-sign
	}
}
