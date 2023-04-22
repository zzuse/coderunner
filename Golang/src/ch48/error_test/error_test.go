package error_test

import (
	"errors"
	"fmt"
	"os"
	"os/exec"
	"runtime"
	"strconv"
	"testing"
)

func echo(request string) (response string, err error) {
	if request == "" {
		err = errors.New("empty request")
		return
	}
	response = fmt.Sprintf("echo: %s", request)
	return
}

func TestError(t *testing.T) {
	for _, req := range []string{"", "hello!"} {
		fmt.Printf("request: %s\n", req)
		resp, err := echo(req)
		if err != nil {
			fmt.Printf("error:%s\n", err)
			continue
		}
		fmt.Printf("response: %s\n", resp)
	}
	err1 := fmt.Errorf("invalid contents: %s", "#$%")
	println(err1)
	err2 := errors.New(fmt.Sprintf("invalid contents: %s", "#$%"))
	if err1.Error() == err2.Error() {
		fmt.Println("The error message in err1 and err2 are the same.")
	}
}

func underlyingError(err error) error {
	switch err := err.(type) {
	case *os.PathError:
		return err.Err
	case *os.LinkError:
		return err.Err
	case *os.SyscallError:
		return err.Err
	case *exec.Error:
		return err.Err
	}
	return err
}

func TestOSError(t *testing.T) {
	r, w, err := os.Pipe()
	if err != nil {
		fmt.Printf("unexpected error: %s\n", err)
		return
	}
	r.Close()
	_, err = w.Write([]byte("hi"))
	uError := underlyingError(err)
	fmt.Printf("underlying error: %s (type: %T)\n", uError, uError)
	fmt.Println()

	var f *os.File
	var index int
	paths := []string{
		os.Args[0],
		"/it/must/not/exist",
		os.DevNull,
	}
	printError := func(i int, err error) {
		if err == nil {
			fmt.Println("nil error")
			return
		}
		err = underlyingError(err)
		switch err {
		case os.ErrClosed:
			fmt.Printf("error(closed)[%d]: %s\n", i, err)
		case os.ErrInvalid:
			fmt.Printf("error(invalid)[%d]:%s\n", i, err)
		case os.ErrPermission:
			fmt.Printf("error(permission)[%d]: %s\n", i, err)
		}
	}
	{
		index = 0
		f, err = os.Open(paths[index])
		if err != nil {
			fmt.Printf("unexpected error: %s\n", err)
			return
		}
		f.Close()
		_, err = f.Read([]byte{})
		printError(index, err)
	}
	{
		index = 1
		f, _ = os.Open(paths[index])
		_, err = f.Stat()
		printError(index, err)
	}
	{
		index = 2
		_, err = exec.LookPath(paths[index])
		printError(index, err)
	}
	if f != nil {
		f.Close()
	}
	fmt.Println()

	paths2 := []string{
		runtime.GOROOT(),
		"/it/must/not/exist",
		os.DevNull,
	}
	printError2 := func(i int, err error) {
		if err == nil {
			fmt.Println("nil error")
			return
		}
		err = underlyingError(err)
		if os.IsExist(err) {
			fmt.Printf("error(exist)[%d]: %s\n", i, err)
		} else if os.IsNotExist(err) {
			fmt.Printf("error(not exist)[%d]: %s\n", i, err)
		} else if os.IsPermission(err) {
			fmt.Printf("error(permission)[%d]: %s\n", i, err)
		} else {
			fmt.Printf("error(other)[%d]: %s\n", i, err)
		}
	}
	{
		index = 0
		err = os.Mkdir(paths2[index], 0700)
		printError2(index, err)
	}
	{
		index = 1
		f, err = os.Open(paths[index])
		printError2(index, err)
	}
	{
		index = 2
		_, err = exec.LookPath(paths[index])
		printError2(index, err)
	}
	if f != nil {
		f.Close()
	}
}

type Errno int

func (e Errno) Error() string {
	return "errno " + strconv.Itoa(int(e))
}

func TestOs(t *testing.T) {
	var err error

	_, err = exec.LookPath(os.DevNull)
	fmt.Printf("error: %s\n", err)
	if execErr, ok := err.(*exec.Error); ok {
		// error can be changed
		execErr.Name = os.TempDir()
		execErr.Err = os.ErrNotExist
	}
	fmt.Printf("error: %s\n", err)
	fmt.Println()

	err = os.ErrPermission
	if os.IsPermission(err) {
		fmt.Printf("error(permission): %s\n", err)
	} else {
		fmt.Printf("error(other): %s\n", err)
	}
	os.ErrPermission = os.ErrExist

	if os.IsPermission(err) {
		fmt.Printf("error(permission): %s\n", err)
	} else {
		fmt.Printf("error(other): %s\n", err)
	}
	fmt.Println()

	const (
		ERR0 = Errno(0)
		ERR1 = Errno(1)
		ERR2 = Errno(2)
	)
	var myErr error = Errno(0)
	switch myErr {
	case ERR0:
		fmt.Println("ERR0")
	case ERR1:
		fmt.Println("ERR1")
	case ERR2:
		fmt.Println("ERR2")
	}
}
