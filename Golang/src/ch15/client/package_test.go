package client

import (
	"go_learning/src/ch15/series"
	"testing"
)

func TestPackage(t *testing.T) {
	t.Log(series.GetFibonacciSerie(5))
	t.Log(series.Square(5))
	// t.Fatal("not implemented")
}
