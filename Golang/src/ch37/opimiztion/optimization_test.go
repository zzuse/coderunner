package opimiztion

import "testing"

func TestCreateRequest(t *testing.T) {
	str := createRequest()
	t.Log(str)
}

func TestProcessRequestNew(t *testing.T) {
	reqs := []string{}
	reqs = append(reqs, createRequest())
	reps := processRequestNew(reqs)
	t.Log(reps[0])
}

func TestProcessRequestOld(t *testing.T) {
	reqs := []string{}
	reqs = append(reqs, createRequest())
	reps := processRequestOld(reqs)
	t.Log(reps[0])
}

// go test -bench=. -cpuprofile=cpu.prof
// go test -bench=. -memprofile=mem.prof
// go tool pprof cpu.prof
// go tool pprof mem.prof
func BenchmarkProcessRequestNew(b *testing.B) {
	reqs := []string{}
	reqs = append(reqs, createRequest())
	b.ResetTimer()
	for i := 0; i < b.N; i++ {
		_ = processRequestNew(reqs)
	}
	b.StopTimer()
}

func BenchmarkProcessRequestOld(b *testing.B) {
	reqs := []string{}
	reqs = append(reqs, createRequest())
	b.ResetTimer()
	for i := 0; i < b.N; i++ {
		_ = processRequestOld(reqs)
	}
	b.StopTimer()
}
