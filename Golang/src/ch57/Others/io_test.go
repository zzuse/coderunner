package Others

import (
	"bytes"
	"fmt"
	"io"
	"strings"
	"testing"
)

func TestIO(t *testing.T) {
	builder := new(strings.Builder)
	_ = interface{}(builder).(io.Writer)
	_ = interface{}(builder).(io.ByteWriter)
	_ = interface{}(builder).(fmt.Stringer)

	reader := strings.NewReader("")
	_ = interface{}(reader).(io.Reader)
	_ = interface{}(reader).(io.ReaderAt)
	_ = interface{}(reader).(io.ByteReader)
	_ = interface{}(reader).(io.RuneReader)
	_ = interface{}(reader).(io.Seeker)
	_ = interface{}(reader).(io.ByteScanner)
	_ = interface{}(reader).(io.RuneScanner)
	_ = interface{}(reader).(io.WriterTo)

	buffer := bytes.NewBuffer([]byte{})
	_ = interface{}(buffer).(io.Reader)
	_ = interface{}(buffer).(io.ByteReader)
	_ = interface{}(buffer).(io.RuneReader)
	_ = interface{}(buffer).(io.ByteScanner)
	_ = interface{}(buffer).(io.RuneScanner)
	_ = interface{}(buffer).(io.WriterTo)

	_ = interface{}(buffer).(io.Writer)
	_ = interface{}(buffer).(io.ByteWriter)
	_ = interface{}(buffer).(io.ReaderFrom)

	_ = interface{}(buffer).(fmt.Stringer)

	src := strings.NewReader("CopyN copies n bytes (or until an error) from src to dst. " +
		"It returns the number of bytes copies and " +
		"the earliest error encountered while copying.")
	dst := new(strings.Builder)
	written, err := io.CopyN(dst, src, 58)
	if err != nil {
		fmt.Printf("error: %v\n", err)
	} else {
		fmt.Printf("Written(%d): %q\n", written, dst.String())
	}

	comments := "Because these interfaces and primitives wrap lower-level operations with various implementations, " +
		"unless otherwise informed clients should not assume they are safe for parallel execution."
	basicReader := strings.NewReader(comments)
	basicWriter := new(strings.Builder)

	reader1 := io.LimitReader(basicReader, 98)
	_ = interface{}(reader1).(io.Reader)

	reader2 := io.NewSectionReader(basicReader, 98, 89)
	_ = interface{}(reader2).(io.Reader)
	_ = interface{}(reader2).(io.ReaderAt)
	_ = interface{}(reader2).(io.Seeker)

	reader3 := io.TeeReader(basicReader, basicWriter)
	_ = interface{}(reader3).(io.Reader)

	reader4 := io.MultiReader(reader1)
	_ = interface{}(reader4).(io.Reader)

	writer1 := io.MultiWriter(basicWriter)
	_ = interface{}(writer1).(io.Writer)

	pReader, pWriter := io.Pipe()
	_ = interface{}(pReader).(io.Reader)
	_ = interface{}(pReader).(io.Closer)
	_ = interface{}(pWriter).(io.Writer)
	_ = interface{}(pWriter).(io.Closer)
}

func executeIfNoErr(err error, f func()) {
	if err != nil {
		fmt.Printf("error: %v\n", err)
		return
	}
	f()
}

func TestIOs(t *testing.T) {
	comment := "Package io provides basic interfaces to I/O primitives. " +
		"Its primary job is to wrap existing implementations of such primitives, " +
		"such as those in package os, " +
		"into shared public interfaces that abstract the functionality, " +
		"plus some other related primitives."

	fmt.Println("New a string reader and name it \"reader1\" ...")
	reader1 := strings.NewReader(comment)
	buf1 := make([]byte, 7)
	n, err := reader1.Read(buf1)
	var offset1 int64
	var index1 int64
	executeIfNoErr(err, func() {
		fmt.Printf("Read(%d): %q\n", n, buf1[:n])
		offset1 = int64(53)
		index1, err = reader1.Seek(offset1, io.SeekCurrent)
	})
	executeIfNoErr(err, func() {
		fmt.Printf("The new index after seeking from current with offset %d: %d\n",
			offset1, index1)
		n, err = reader1.Read(buf1)
	})
	executeIfNoErr(err, func() {
		fmt.Printf("Read(%d): %q\n", n, buf1[:n])
	})
	fmt.Println()

	reader1.Reset(comment)
}
