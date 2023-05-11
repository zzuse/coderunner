package Others

import (
	"fmt"
	"strings"
	"testing"
)

func TestString(t *testing.T) {
	var builder1 strings.Builder
	builder1.WriteString("A Builder is used to efficiently build a string using Write methods.")
	fmt.Printf("The first output(%d):\n%q\n", builder1.Len(), builder1.String())
	fmt.Println()
	builder1.WriteByte(' ')
	builder1.WriteString("It minimizes memory copying. The zero value is ready to use.")
	builder1.Write([]byte{'\n', '\n'})
	builder1.WriteString("Do not copy a non-zero Builder.")
	fmt.Printf("The second output(%d):\n\"%s\"\n", builder1.Len(), builder1.String())
	fmt.Println()

	fmt.Println("Grow the builder...")
	builder1.Grow(10)
	fmt.Printf("The length of contents in the builder is %d.\n", builder1.Len())
	fmt.Println()

	fmt.Println("Reset the builder ...")
	builder1.Reset()
	fmt.Printf("The third output(%d):\n%q\n", builder1.Len(), builder1.String())

	builder1.Grow(1)
	f1 := func(b strings.Builder) {
		//b.Grow(1)
	}
	f1(builder1)

	ch1 := make(chan strings.Builder, 1)
	ch1 <- builder1
	builder2 := <-ch1
	//builder2.Grow(1)
	_ = builder2

	builder3 := builder1
	// builder3.Grow(1)
	_ = builder3
	f2 := func(bp *strings.Builder) {
		(*bp).Grow(1)
		builder4 := *bp
		// builder4.Grow(1)
		_ = builder4
	}
	f2(&builder1)
	builder1.Reset()
	builder5 := builder1
	builder5.Grow(1)
}
