package Others

import (
	"bytes"
	"fmt"
	"testing"
)

// Len() method return have not reading length

func TestBuffer0(t *testing.T) {
	var buffer1 bytes.Buffer
	contents := "Simple byte buffer for marshaling data."
	fmt.Printf("Write contents %q ...\n", contents)
	buffer1.WriteString(contents)
	fmt.Printf("The length of %d\n", buffer1.Len())
	fmt.Printf("The capacity of %d\n", buffer1.Cap())
	fmt.Println()

	p1 := make([]byte, 7)
	n, _ := buffer1.Read(p1)
	fmt.Printf("%d bytes were read. (call Read)\n", n)
	fmt.Printf("The length of %d\n", buffer1.Len())
	fmt.Printf("The capacity of %d\n", buffer1.Cap())

}

func TestBuffer1(t *testing.T) {
	var contents string
	buffer1 := bytes.NewBufferString(contents)
	fmt.Printf("The length of new buffer with contents %q: %d\n", contents, buffer1.Len())
	fmt.Printf("The capacity of new buffer with contents %q: %d\n", contents, buffer1.Cap())
	fmt.Println()

	contents = "12345"
	fmt.Printf("Write contents %q ...\n", contents)
	buffer1.WriteString(contents)
	fmt.Printf("The length of new buffer with contents %q: %d\n", contents, buffer1.Len())
	fmt.Printf("The capacity of new buffer with contents %q: %d\n", contents, buffer1.Cap())
	fmt.Println()

	contents = "67"
	fmt.Printf("Write contents %q ...\n", contents)
	buffer1.WriteString(contents)
	fmt.Printf("The length of new buffer with contents %q: %d\n", contents, buffer1.Len())
	fmt.Printf("The capacity of new buffer with contents %q: %d\n", contents, buffer1.Cap())
	fmt.Println()

	contents = "89"
	fmt.Printf("Write contents %q ...\n", contents)
	buffer1.WriteString(contents)
	fmt.Printf("The length of new buffer with contents %q: %d\n", contents, buffer1.Len())
	fmt.Printf("The capacity of new buffer with contents %q: %d\n", contents, buffer1.Cap())
	fmt.Println()
	fmt.Println()

	contents = "abcdefghijk"
	buffer2 := bytes.NewBufferString(contents)
	fmt.Printf("The length of new buffer with contents %q: %d\n", contents, buffer2.Len())
	fmt.Printf("The capacity of new buffer with contents %q: %d\n", contents, buffer2.Cap())
	fmt.Println()

	n := 10
	fmt.Printf("Grow the buffer with %d ...\n", n)
	buffer2.Grow(n)
	fmt.Printf("The length of new buffer with contents %q: %d\n", contents, buffer2.Len())
	fmt.Printf("The capacity of new buffer with contents %q: %d\n", contents, buffer2.Cap())
	fmt.Println()

	var buffer3 bytes.Buffer
	fmt.Printf("The length of buffer: %d\n", buffer3.Len())
	fmt.Printf("The Capacity of buffer: %d\n", buffer3.Cap())
	fmt.Println()

	contents = "xyz"
	fmt.Printf("Write contents %q ...\n", contents)
	buffer3.WriteString(contents)
	fmt.Printf("The length of buffer: %d\n", buffer3.Len())
	fmt.Printf("The Capacity of buffer: %d\n", buffer3.Cap())

}

func TestBuffer2(t *testing.T) {
	contents := "ab"
	buffer1 := bytes.NewBufferString(contents)
	fmt.Printf("The length of new buffer with contents %q: %d\n", contents, buffer1.Len())
	fmt.Printf("The capacity of new buffer with contents %q: %d\n", contents, buffer1.Cap())
	fmt.Println()

	unreadBytes := buffer1.Bytes()
	fmt.Printf("The unread bytes of the buffer: %v\n", unreadBytes)

	contents = "cdefg"
	fmt.Printf("Write contents %q ...\n", contents)
	buffer1.WriteString(contents)
	fmt.Printf("The length of new buffer with contents %q: %d\n", contents, buffer1.Len())
	fmt.Printf("The capacity of new buffer with contents %q: %d\n", contents, buffer1.Cap())
	fmt.Println()

	unreadBytes = unreadBytes[:cap(unreadBytes)]
	fmt.Printf("The unread bytes of the buffer: %v\n", unreadBytes)
	fmt.Println()

	value := byte('X')
	fmt.Printf("Set a byte in the unread bytes to %v ...\n", value)
	unreadBytes[len(unreadBytes)-2] = value
	fmt.Printf("The unread bytes of the buffer: %v\n", buffer1.Bytes())
	fmt.Println()

	contents = "hijklmn"
	fmt.Printf("Write contents %q ...\n", contents)
	buffer1.WriteString(contents)
	fmt.Printf("The length of new buffer with contents %q: %d\n", contents, buffer1.Len())
	fmt.Printf("The capacity of new buffer with contents %q: %d\n", contents, buffer1.Cap())
	fmt.Println()

}
