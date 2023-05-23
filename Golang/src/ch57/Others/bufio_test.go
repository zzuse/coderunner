package Others

import (
	"bufio"
	bytes2 "bytes"
	"fmt"
	"strings"
	"testing"
)

func TestBuffIO(t *testing.T) {
	comment := "Package bufio implements bufferd I/O." +
		"It wraps an io.Reader or io.Writer object, " +
		"creating another object (Reader or Writer) that " +
		"also implements the interface but provides buffering and " +
		"some help for textual I/O."
	basicReader := strings.NewReader(comment)
	fmt.Printf("The size of basic reader: %d\n", basicReader.Size())
	fmt.Println()

	fmt.Println("New a buffered reader ...")
	reader1 := bufio.NewReader(basicReader)
	fmt.Printf("The default size of buffered reader: %d\n", reader1.Size())
	fmt.Printf("The number of unread bytes in the buffer: %d\n", reader1.Buffered())
	fmt.Println()

	bytes, err := reader1.Peek(7)
	if err != nil {
		fmt.Printf("error: %v\n", err)
	}
	fmt.Printf("Peeked contents(%d): %q\n", len(bytes), bytes)
	fmt.Printf("The number of unread bytes in the buffer: %d\n", reader1.Buffered())
	fmt.Println()

	buf1 := make([]byte, 7)
	n, err := reader1.Read(buf1)
	if err != nil {
		fmt.Printf("error: %v\n", err)
	}
	fmt.Printf("Read contents(%d): %q\n", n, buf1)
	fmt.Printf("The number of unread bytes in the buffer: %d\n", reader1.Buffered())
	fmt.Println()

	fmt.Printf("Reset the basic reader (size: %d) ...\n", len(comment))
	basicReader.Reset(comment)
	fmt.Printf("Reset the buffered reader (size: %d) ...\n", reader1.Size())
	reader1.Reset(basicReader)
	peekNum := len(comment) + 1
	fmt.Printf("Peek %d bytes ...\n", peekNum)
	bytes, err = reader1.Peek(peekNum)
	if err != nil {
		fmt.Printf("error: %v\n", err)
	}
	fmt.Printf("The number of peeked bytes: %d\n", len(bytes))
	fmt.Println()

	fmt.Printf("Reset the basic reader (size: %d) ...\n", len(comment))
	basicReader.Reset(comment)
	size := 300
	fmt.Printf("New a buffered reader with size %d ...\n", size)
	reader2 := bufio.NewReaderSize(basicReader, size)
	peekNum = size + 1
	fmt.Printf("Peek %d bytes ...\n", peekNum)
	bytes, err = reader2.Peek(peekNum)
	if err != nil {
		fmt.Printf("error: %v\n", err)
	}
	fmt.Printf("The number of peeked bytes: %d\n", len(bytes))
}

func TestBuffIO1(t *testing.T) {
	comment := "Package bufio implements buffered I/O. " +
		"It wraps an io.Reader or io.Writer object, " +
		"creating another object (Reader or Writer) that " +
		"also implments the interface but provides buffering and " +
		"some help for textual I/O. "
	basicReader := strings.NewReader(comment)
	fmt.Printf("The size of basic reader: %d\n", basicReader.Size())

	size := 300
	fmt.Printf("New a buffered reader with size %d ...\n", size)
	reader1 := bufio.NewReaderSize(basicReader, size)
	fmt.Println()

	fmt.Print("[ About 'Peek' method ]\n\n")

	peekNum := 38
	fmt.Printf("Peek %d bytes ...\n", peekNum)
	bytes, err := reader1.Peek(peekNum)
	if err != nil {
		fmt.Printf("error: %v\n", err)
	}
	fmt.Printf("Peeked contents(%d): %q\n", len(bytes), bytes)
	fmt.Printf("The number of unread bytes in the buffer: %d\n", reader1.Buffered())
	fmt.Println()

	fmt.Print("[ About 'Read' method ]\n\n")

	readNum := 38
	buf1 := make([]byte, readNum)
	fmt.Printf("Read %d bytes ...\n", readNum)
	n, err := reader1.Read(buf1)
	if err != nil {
		fmt.Printf("error: %v\n", err)
	}
	fmt.Printf("Read contents(%d): %q\n", n, buf1)
	fmt.Printf("The number of unread bytes in the buffer: %d\n", reader1.Buffered())
	fmt.Println()

	fmt.Print("[ About 'ReadSlice' method ]\n\n")
	fmt.Println("Reset the basic reader ...")
	basicReader.Reset(comment)
	fmt.Println("Reset the buffered reader ...")
	reader1.Reset(basicReader)
	fmt.Println()

	delimiter := byte('(')
	fmt.Printf("Read slice with delimiter %q...\n", delimiter)
	line, err := reader1.ReadSlice(delimiter)
	if err != nil {
		fmt.Printf("error: %v\n", err)
	}
	fmt.Printf("Read contents(%d): %q\n", len(line), line)
	fmt.Printf("The number of unread bytes in the buffer: %d\n", reader1.Buffered())
	fmt.Println()

	delimiter = byte('[')
	fmt.Printf("Read slice with delimiter %q...\n", delimiter)
	line, err = reader1.ReadSlice(delimiter)
	if err != nil {
		fmt.Printf("error: %v\n", err)
	}
	fmt.Printf("Read contents(%d): %q\n", len(line), line)
	fmt.Printf("The number of unread bytes in the buffer: %d\n", reader1.Buffered())
	fmt.Println()

	fmt.Println("Reset the basic reader ...")
	basicReader.Reset(comment)
	size = 200
	fmt.Printf("New a buffered reader with size %d ...\n", size)
	reader2 := bufio.NewReaderSize(basicReader, size)
	fmt.Println()

	delimiter = byte('[')
	fmt.Printf("Read slice with delimiter %q...\n", delimiter)
	line, err = reader2.ReadSlice(delimiter)
	if err != nil {
		fmt.Printf("error: %v\n", err)
	}
	fmt.Printf("Read contents(%d): %q\n", len(line), line)
	fmt.Printf("The number of unread bytes in the buffer: %d\n", reader2.Buffered())
	fmt.Println()

	fmt.Print("[ About 'ReadBytes' method ]\n\n")

	fmt.Println("Reset the basic reader ...")
	basicReader.Reset(comment)
	size = 200
	fmt.Printf("New a buffered reader with size %d ...\n", size)
	reader3 := bufio.NewReaderSize(basicReader, size)
	fmt.Println()

	delimiter = byte('[')
	fmt.Printf("Read bytes with delimiter %q...\n", delimiter)
	line, err = reader3.ReadBytes(delimiter)
	if err != nil {
		fmt.Printf("error: %v\n", err)
	}
	fmt.Printf("Read contents(%d): %q\n", len(line), line)
	fmt.Printf("The number of unread bytes in the buffer: %d\n", reader3.Buffered())
	fmt.Println()

	fmt.Print("[ About contents leak ]\n\n")
	basicReader = strings.NewReader(comment)
	fmt.Printf("The size of basic reader: %d\n", basicReader.Size())

	size = len(comment)
	fmt.Printf("New a buffered reader with size %d ...\n", size)
	reader4 := bufio.NewReaderSize(basicReader, size)
	fmt.Println()

	peekNum = 7
	fmt.Printf("Peek %d bytes ...\n", peekNum)
	bytes, err = reader4.Peek(peekNum)
	if err != nil {
		fmt.Printf("error: %v\n", err)
	}
	fmt.Printf("Peeked contents(%d): %q\n", len(bytes), bytes)
	fmt.Println()

	bytes = bytes[:cap(bytes)]
	fmt.Printf("The all of the contents in the buffer:\n%q\n", bytes)
	fmt.Println()

	blank := byte(' ')
	fmt.Println("Set blanks into the contents in the buffer ...")
	for _, i := range []int{55, 56, 57, 58, 66, 67, 68} {
		bytes[i] = blank
	}
	fmt.Println()

	peekNum = size
	fmt.Printf("Peek %d bytes ...\n", peekNum)
	bytes, err = reader4.Peek(peekNum)
	if err != nil {
		fmt.Printf("error: %v\n", err)
	}
	fmt.Printf("Peeked contents(%d):\n %q \n", len(bytes), bytes)
	fmt.Println()

	delimiter = byte(',')
	fmt.Printf("Read slice with delimiter %q...\n", delimiter)
	line, err = reader4.ReadSlice(delimiter)
	if err != nil {
		fmt.Printf("error: %v\n", err)
	}
	fmt.Printf("Read contents(%d): %q\n", len(line), line)
	fmt.Println()

	line = line[:cap(line)]
	fmt.Printf("The all of the contents in the buffer:\n%q\n", line)
	fmt.Println()

	underline := byte('_')
	fmt.Println("Set underlines into the contents in the buffer ...")
	for _, i := range []int{89, 92, 103} {
		line[i] = underline
	}
	fmt.Println()

	peekNum = size
	fmt.Printf("Peek %d bytes ...\n", peekNum)
	bytes, err = reader4.Peek(peekNum)
	if err != nil {
		fmt.Printf("error: %v\n", err)
	}
	fmt.Printf("Peeked contents(%d): %q\n", len(bytes), bytes)

	comment = "Writer implements buffering for an io.Writer object. " +
		"If an error occurs writing to a Writer, " +
		"no more data will be accepted and all subsequent writes, " +
		"and Flush, will return the error. After all data has been written, " +
		"the client should call the Flush method to guarantee all data " +
		"has been forwarded to the underlying io.Writer."

	basicWriter := &strings.Builder{}
	size = 300
	fmt.Printf("New a bufferd writer with size %d ...\n", size)
	writer1 := bufio.NewWriterSize(basicWriter, size)
	fmt.Println()

	begin, end := 0, 53
	fmt.Printf("Write %d bytes into the writer ...\n", end-begin)
	writer1.WriteString(comment[begin:end])
	fmt.Printf("The number of buffered bytes: %d\n", writer1.Buffered())
	fmt.Printf("The number of unused bytes in the buffer: %d\n", writer1.Available())
	fmt.Println("Flush the buffer in the writer ...")
	writer1.Flush()
	fmt.Printf("The number of buffered bytes: %d\n", writer1.Buffered())
	fmt.Printf("The number of unused bytes in the buffer: %d\n", writer1.Available())
	fmt.Println()

	begin, end = 0, 326
	fmt.Printf("Write %d bytes into the writer ...\n", end-begin)
	writer1.WriteString(comment[begin:end])
	fmt.Printf("The number of buffered bytes: %d\n", writer1.Buffered())
	fmt.Printf("The number of unused bytes in the buffer: %d\n", writer1.Available())
	fmt.Println("Flush the buffer in the writer ...")
	writer1.Flush()
	fmt.Println()

	basicWriter2 := &bytes2.Buffer{}
	fmt.Printf("Reset the writer with a bytes buffer(an implementation of io.ReaderFrom) ...\n")
	writer1.Reset(basicWriter2)
	reader := strings.NewReader(comment)
	fmt.Println("Read data from the reader...")
	writer1.ReadFrom(reader)
	fmt.Printf("The number of buffered bytes: %d\n", writer1.Buffered())
	fmt.Printf("The number of unused bytes in the buffer: %d\n", writer1.Available())
}
