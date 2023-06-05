package perf

import (
	"bytes"
	"encoding/json"
	"errors"
	"fmt"
	"math/rand"
	"os"
	"path/filepath"
	"strconv"
	"sync"
	"time"
)

func send(ch1 chan int, wg *sync.WaitGroup, repeat int) {
	defer wg.Done()
	time.Sleep(time.Millisecond * 10)
	for k := 0; k < repeat; k++ {
		elem := rand.Intn(repeat)
		ch1 <- elem
	}
}

func receive(ch1 chan int, wg *sync.WaitGroup) {
	defer wg.Done()
	for elem := range ch1 {
		_ = elem
	}
}

func BlockProfile() error {
	max := 100
	senderNum := max / 2
	receiverNum := max / 4
	ch1 := make(chan int, max/4)

	var senderGroup sync.WaitGroup
	senderGroup.Add(senderNum)
	repeat := 50000
	for j := 0; j < senderNum; j++ {
		go send(ch1, &senderGroup, repeat)
	}

	go func() {
		senderGroup.Wait()
		close(ch1)
	}()

	var receiverGroup sync.WaitGroup
	receiverGroup.Add(receiverNum)
	for j := 0; j < receiverNum; j++ {
		go receive(ch1, &receiverGroup)
	}
	receiverGroup.Wait()
	return nil
}

func CPUProfile() error {
	max := 10000000
	var buf bytes.Buffer
	for j := 0; j < max; j++ {
		num := rand.Int63n(int64(max))
		str := strconv.FormatInt(num, 10)
		buf.WriteString(str)
	}
	_ = buf.String()
	return nil
}

type box struct {
	Str   string
	Code  rune
	Bytes []byte
}

func createBox(seed int) box {
	if seed <= 0 {
		seed = 1
	}
	var array []byte
	size := seed * 8
	for i := 0; i < size; i++ {
		array = append(array, byte(seed))
	}
	return box{
		Str:   string(seed),
		Code:  rune(seed),
		Bytes: array,
	}
}

func genJSON(one box) ([]byte, error) {
	return json.Marshal(one)
}

func MemProfile() error {
	max := 50000
	var buf bytes.Buffer
	for j := 0; j < max; j++ {
		seed := rand.Intn(95) + 32
		one := createBox(seed)
		b, err := genJSON(one)
		if err != nil {
			return err
		}
		buf.Write(b)
		buf.WriteByte('\t')
	}
	_ = buf.String()
	return nil
}

type OpFunc func() error

func Execute(op OpFunc, times int) (err error) {
	if op == nil {
		return errors.New("nil operation function")
	}
	if times <= 0 {
		return fmt.Errorf("invaid times: %d", times)
	}
	var t1 time.Time
	defer func() {
		diff := time.Now().Sub(t1)
		fmt.Printf("(elapsed time: %s)\n", diff)
		if p := recover(); p != nil {
			return
		}
	}()
	t1 = time.Now()
	for i := 0; i < times; i++ {
		if err = op(); err != nil {
			return
		}
		time.Sleep(time.Microsecond)
	}
	return
}

func CreateFile(dir, name string) (*os.File, error) {
	if dir == "" {
		var err error
		dir, err = os.Getwd()
		if err != nil {
			return nil, err
		}
	}
	path := filepath.Join(dir, name)
	return os.Create(path)
}
