package bdd

import (
	. "github.com/smartystreets/goconvey/convey"
	"testing"
)

// for web test, start $GOPATH/bin/goconvey in cwd
func TestSpec(t *testing.T) {
	Convey("Given 2 even numbers", t, func() {
		a := 3
		b := 4
		Convey("When add the two numbers", func() {
			c := a + b
			Convey("Then the result is still even", func() {
				So(c%2, ShouldEqual, 0)
			})
		})
	})
}
