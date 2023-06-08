package perf_test

import (
	"errors"
	"fmt"
	"go_learning/src/ch58/perf/common"
	"os"
	"runtime"
	"runtime/pprof"
	"testing"
)

var (
	cpuProfileName = "cpu_profile.out"
)

func startCPUProfile(f *os.File) error {
	if f == nil {
		return errors.New("nil file")
	}
	return pprof.StartCPUProfile(f)
}

func stopCPUProfile() {
	pprof.StopCPUProfile()
}

func TestCpuProfile(t *testing.T) {
	f, err := common.CreateFile("", cpuProfileName)
	if err != nil {
		fmt.Printf("CPU profile creation error: %v\n", err)
		return
	}
	defer f.Close()
	if err := startCPUProfile(f); err != nil {
		fmt.Printf("CPU profile start error: %v\n", err)
		return
	}
	if err = common.Execute(common.CPUProfile, 10); err != nil {
		fmt.Printf("execute error: %v\n", err)
		return
	}
	stopCPUProfile()
}

var (
	memProfileName = "mem_profile.out"
	memProfileRate = 8
)

func startMemProfile() {
	runtime.MemProfileRate = memProfileRate
}

func stopMemProfile(f *os.File) error {
	if f == nil {
		return errors.New("nil file")
	}
	return pprof.WriteHeapProfile(f)
}

func TestMemProfile(t *testing.T) {
	f, err := common.CreateFile("", memProfileName)
	if err != nil {
		fmt.Printf("memory profile creation error: %v\n", err)
		return
	}
	defer f.Close()
	startMemProfile()
	if err = common.Execute(common.MemProfile, 10); err != nil {
		fmt.Printf("execute error: %v\n", err)
		return
	}
	if err := stopMemProfile(f); err != nil {
		fmt.Printf("memory profile stop error: %v\n", err)
		return
	}
}
