package Others

import (
	bytes2 "bytes"
	"fmt"
	"io"
	"os"
	"path/filepath"
	"reflect"
	"testing"
)

var ioTypes = []reflect.Type{
	reflect.TypeOf((*io.Reader)(nil)).Elem(),
	reflect.TypeOf((*io.Writer)(nil)).Elem(),
	reflect.TypeOf((*io.Closer)(nil)).Elem(),

	reflect.TypeOf((*io.ByteReader)(nil)).Elem(),
	reflect.TypeOf((*io.RuneReader)(nil)).Elem(),
	reflect.TypeOf((*io.ReaderAt)(nil)).Elem(),
	reflect.TypeOf((*io.Seeker)(nil)).Elem(),
	reflect.TypeOf((*io.WriterTo)(nil)).Elem(),
	reflect.TypeOf((*io.ByteWriter)(nil)).Elem(),
	reflect.TypeOf((*io.WriterAt)(nil)).Elem(),
	reflect.TypeOf((*io.ReaderFrom)(nil)).Elem(),

	reflect.TypeOf((*io.ByteScanner)(nil)).Elem(),
	reflect.TypeOf((*io.RuneScanner)(nil)).Elem(),
	reflect.TypeOf((*io.ReadSeeker)(nil)).Elem(),
	reflect.TypeOf((*io.ReadCloser)(nil)).Elem(),
	reflect.TypeOf((*io.WriteCloser)(nil)).Elem(),
	reflect.TypeOf((*io.WriteSeeker)(nil)).Elem(),
	reflect.TypeOf((*io.ReadWriter)(nil)).Elem(),
	reflect.TypeOf((*io.ReadWriteSeeker)(nil)).Elem(),
	reflect.TypeOf((*io.ReadWriteCloser)(nil)).Elem(),
}

func TestFile(t *testing.T) {
	file1 := (*os.File)(nil)
	fileType := reflect.TypeOf(file1)
	var buf bytes2.Buffer
	fmt.Fprintf(&buf, "Type %T implements\n", file1)
	for _, t := range ioTypes {
		if fileType.Implements(t) {
			buf.WriteString(t.String())
			buf.WriteByte(',')
			buf.WriteByte('\n')
		}
	}
	output := buf.Bytes()
	output[len(output)-2] = '.'
	fmt.Printf("%s\n", output)

	fileName1 := "something1.txt"
	filePath1 := filepath.Join(os.TempDir(), fileName1)
	var paths []string
	paths = append(paths, filePath1)
	dir, _ := os.Getwd()
	paths = append(paths, filepath.Join(dir[:len(dir)-1], fileName1))
	for _, path := range paths {
		fmt.Printf("Create a file with path %s ...\n", path)
		_, err := os.Create(path)
		if err != nil {
			var underlyingErr string
			if _, ok := err.(*os.PathError); ok {
				underlyingErr = "(path error)"
			}
			fmt.Printf("error: %v %s\n", err, underlyingErr)
			continue
		}
		fmt.Println("The file has been created.")
	}
	fmt.Println()
}
