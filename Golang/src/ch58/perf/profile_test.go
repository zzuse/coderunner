package perf_test

import (
	"errors"
	"fmt"
	"go_learning/src/ch58/perf/common"
	"log"
	"net/http"
	"os"
	"path/filepath"
	"runtime"
	"runtime/pprof"
	"testing"
	"time"
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

var (
	blockProfileName = "block_profile.out"
	blockProfileRate = 2
	debug            = 0
)

func startBlockProfile() {
	runtime.SetBlockProfileRate(blockProfileRate)
}

func stopBlockProfile(f *os.File) error {
	if f == nil {
		return errors.New("nil file")
	}
	return pprof.Lookup("block").WriteTo(f, debug)
}

func TestBlockProfile(t *testing.T) {
	f, err := common.CreateFile("", blockProfileName)
	if err != nil {
		fmt.Printf("block profile creation error: %v\n", err)
		return
	}
	defer f.Close()
	startBlockProfile()
	if err = common.Execute(common.BlockProfile, 10); err != nil {
		fmt.Printf("execute error: %v\n", err)
		return
	}
	if err := stopBlockProfile(f); err != nil {
		fmt.Printf("block profile stop error: %v\n", err)
		return
	}
}

var profileNames = []string{
	"goroutine",
	"heap",
	"allocs",
	"threadcreate",
	"block",
	"mutex",
}

var profileOps = map[string]common.OpFunc{
	"goroutine":    common.BlockProfile,
	"heap":         common.MemProfile,
	"allocs":       common.MemProfile,
	"threadcreate": common.BlockProfile,
	"block":        common.BlockProfile,
	"mutex":        common.BlockProfile,
}

var debugOpts = []int{
	0,
	1,
	2,
}

func genProfile(dir string, name string, debug int) error {
	fmt.Printf("Generating %s profile (debug:%d)\n", name, debug)
	fileName := fmt.Sprintf("%s_%d.out", name, debug)
	f, err := common.CreateFile(dir, fileName)
	if err != nil {
		fmt.Printf("create error: %v (%s)\n", err, fileName)
		return err
	}
	defer f.Close()
	if err = common.Execute(profileOps[name], 10); err != nil {
		fmt.Printf("execute error: %v (%s)\n", err, fileName)
		return err
	}
	profile := pprof.Lookup(name)
	err = profile.WriteTo(f, debug)
	if err != nil {
		fmt.Printf("write error: %v (%s)\n", err, fileName)
		return err
	}
	return nil
}

func createDir() (string, error) {
	currDir, err := os.Getwd()
	if err != nil {
		return "", err
	}
	path := filepath.Join(currDir, "profiles")
	err = os.Mkdir(path, 0766)
	if err != nil && !os.IsExist(err) {
		return "", err
	}
	return path, nil
}

func prepare() {
	runtime.MemProfileRate = 8
	runtime.SetBlockProfileRate(2)
}

func TestProfile(t *testing.T) {
	prepare()
	dir, err := createDir()
	if err != nil {
		fmt.Printf("dir creation error: %v\n", err)
		return
	}
	for _, name := range profileNames {
		for _, debug := range debugOpts {
			err = genProfile(dir, name, debug)
			if err != nil {
				return
			}
			time.Sleep(time.Millisecond)
		}
	}
}

func TestListen(t *testing.T) {
	log.Println(http.ListenAndServe("localhost:8082", nil))
}
