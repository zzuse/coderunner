package haha

import (
	"fmt"
	"testing"
	"time"
)

func TestHello(t *testing.T) {
	var name string
	greeting, err := hello(name)
	if err == nil {
		t.Errorf("The error is nil, but it should not be. (name=%q)", name)
	}
	if greeting != "" {
		t.Errorf("nonempty greeing, but it should not be. (name=%q)", name)
	}
	name = "Robert"
	greeting, err = hello(name)
	if err != nil {
		t.Errorf("The error is not nil, but it should be. (name=%q)", name)
	}
	if greeting == "" {
		t.Errorf("Empty greeting, but it should not be. (name=%q)", name)
	}
	expected := fmt.Sprintf("Hello , %s!", name)
	if greeting != expected {
		t.Errorf("The actual greeting %q is not the expected.(name=%q)", greeting, name)
	}
	t.Logf("The expected greeting is %q\n", expected)
}

func TestIntroduce(t *testing.T) {
	intro := introduce()
	expected := "Welcome to my golang column."
	if intro != expected {
		t.Errorf("The actual introduce %q is not the expected.", intro)
	}
	t.Logf("The expected introduce is %q\n", expected)
}

func TestFail(t *testing.T) {
	t.FailNow()
	t.Log("Failed.")
}

// go test -bench=. -run=^$ $PWD/test_test
// . means all the benchmark function(regexp)
// ^$ means function testing name is null(regexp)
func BenchmarkGetPrimes(b *testing.B) {
	for i := 0; i < b.N; i++ {
		GetPrimes(1000)
	}
}

var expectedPrimes = []int{
	2, 3, 5, 7, 11, 13, 17, 19,
	23, 29, 31, 37, 41, 43, 47, 53,
	59, 61, 67, 71, 73, 79, 83, 89,
	97, 101, 103, 107, 109, 113, 127, 131,
	137, 139, 149, 151, 157, 163, 167, 173,
	179, 181, 191, 193, 197, 199, 211, 223,
	227, 229, 233, 239, 241, 251, 257, 263,
	269, 271, 277, 281, 283, 293, 307, 311,
	313, 317, 331, 337, 347, 349, 353, 359,
	367, 373, 379, 383, 389, 397, 401, 409,
	419, 421, 431, 433, 439, 443, 449, 457,
	461, 463, 467, 479, 487, 491, 499, 503,
	509, 521, 523, 541, 547, 557, 563, 569,
	571, 577, 587, 593, 599, 601, 607, 613,
	617, 619, 631, 641, 643, 647, 653, 659,
	661, 673, 677, 683, 691, 701, 709, 719,
	727, 733, 739, 743, 751, 757, 761, 769,
	773, 787, 797, 809, 811, 821, 823, 827,
	829, 839, 853, 857, 859, 863, 877, 881,
	883, 887, 907, 911, 919, 929, 937, 941,
	947, 953, 967, 971, 977, 983, 991, 997,
}

func TestGetPrimesWith1000(t *testing.T) {
	max := 1000
	primes := GetPrimes(max)
	for i, prime := range primes {
		expectedPrimes := expectedPrimes[i]
		if prime != expectedPrimes {
			t.Errorf("%dth prime number %d is not the expected value %d", i, prime, expectedPrimes)
		}
	}
	if t.Failed() == false {
		t.Logf("The primes less than %d are all correct.", max)
	}
}

func TestGetPrimesWith1000Paralle(t *testing.T) {
	t.Parallel()
	max := 1000
	primes := GetPrimes(max)
	for i, prime := range primes {
		expectedPrimes := expectedPrimes[i]
		if prime != expectedPrimes {
			t.Errorf("%dth prime number %d is not the expected value %d", i, prime, expectedPrimes)
		}
	}
	if t.Failed() == false {
		t.Logf("The primes less than %d are all correct.", max)
	}
}

func BenchmarkGetPrimesWith100(b *testing.B) {
	for i := 0; i < b.N; i++ {
		GetPrimes(100)
	}
}

func BenchmarkGetPrimesWith10000(b *testing.B) {
	for i := 0; i < b.N; i++ {
		GetPrimes(10000)
	}
}

func BenchmarkGetPrimesWith1000000(b *testing.B) {
	for i := 0; i < b.N; i++ {
		GetPrimes(1000000)
	}
}

func TestGetPrimesWithAbnormalParam(t *testing.T) {
	t.Parallel()
	invalidParams := []int{1, 0, -1, -2, -3}
	for _, ip := range invalidParams {
		result := GetPrimes(ip)
		if result == nil {
			t.Error("The result is nil, but it should not be.")
		}
		if len(result) > 0 {
			t.Errorf("The result is not empty, but it should be.")
		}
	}
}

func comparePrimes(primes []int) (err error) {
	for i, prime := range primes {
		expectedPrime := expectedPrimes[i]
		if prime != expectedPrime {
			err = fmt.Errorf("%dth prime number %d is not the expected value %d", i, prime, expectedPrime)
			break
		}
	}
	return
}

// go test -count=3 -v -run=TestGetPrimesParallel $PWD/test_test
func TestGetPrimesParallel(t *testing.T) {
	for _, max := range []int{1, 2, 3, 4, 5} {
		max := max * 200
		t.Run(fmt.Sprintf("TestGetPrimesWith%d", max),
			func(t *testing.T) {
				t.Parallel()
				primes := GetPrimes(max)
				err := comparePrimes(primes)
				if err != nil {
					t.Error(err)
				} else {
					t.Logf("The primes less than %d are all correct.", max)
				}
			})
	}
}

func BenchmarkGetPrimes2(b *testing.B) {
	b.StopTimer()
	time.Sleep(time.Millisecond * 500)
	max := 10000
	b.StartTimer()

	for i := 0; i < b.N; i++ {
		GetPrimes(max)
	}
}
