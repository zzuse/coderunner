package perf

import (
	"fmt"
	"testing"
)
import "go_learning/src/ch58/perf/common"

func TestCpuProfile(t *testing.T) {
	f, err := common.CreateFile("profile")
	if err != nil {
		fmt.Printf("CPU profile creation error: %v\n", err)
	}
}
