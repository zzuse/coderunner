package string_test

import "testing"

func TestString(t *testing.T) {
	var s string
	t.Log(s)
	s = "hello"
	t.Log(len(s))
	s = "\xE4\xB8\xAD"
	t.Log(s)
	t.Log(len(s))
	s = "中"
	t.Log(len(s))

	// rune 取出 unicode
	c := []rune(s)
	t.Log(len(c))
	t.Logf("中 unicode %x", c[0])
	t.Logf("中 UTF8 %x", s)
}

func TestStringToRune(t *testing.T) {
	s := "中华人民共和国"
	for _, c := range s {
		// all 2 format using input 1
		t.Logf("%[1]c %[1]x", c)
	}
}
