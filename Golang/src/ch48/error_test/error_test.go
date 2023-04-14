package error_test

import (
	"errors"
	"fmt"
	"os"
	"os/exec"
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

}