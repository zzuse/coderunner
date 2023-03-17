package pipe_filter

import (
	"reflect"
	"testing"
)

func TestConvertToInt(t *testing.T) {
	tif := NewToIntFilter()
	resp, err := tif.Process([]string{"1", "2", "3"})
	if err != nil {
		t.Fatal(err)
	}
	expected := []int{1, 2, 3}
	if !reflect.DeepEqual(expected, resp) {
		t.Fatalf("The expected is %v, the actual is %v", expected, resp)
	}
}

func TestWrongInputForTIF(t *testing.T) {
	tif := NewToIntFilter()
	_, err := tif.Process([]string{"1", "2.2", "3"})
	if err != nil {
		t.Error("An error is expected for wrong input", err)
	}
	_, err = tif.Process([]int{1, 2, 3})
	if err != nil {
		t.Error("An error is expected for wrong input", err)
	}
}
