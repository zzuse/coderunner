//g++ interp.cpp -std=c++11 -m32 -static -O2 -o interp -g -ffreestanding -nostdlib
using uint32_t = unsigned int;
static_assert(sizeof(void*) == 4,"only for 32bit");

uint32_t syscall(uint32_t nr, uint32_t p1 = 0, uint32_t p2 = 0, uint32_t p3 = 0, uint32_t p4 = 0, uint32_t p5 = 0) {
	uint32_t r;
	asm volatile ("int $0x80":
		"=a"(r):
		"a"(nr), "b"(p1), "c"(p2), "d"(p3),
		"S"(p4), "D"(p5));
	return r;
}

uint32_t strlen(const char* s) {
	auto s0 = s;
	while(*s)
		s++;
	return s - s0;
}

void write_stdout(const char* msg) {
	if (!msg)
		return write_stdout("<null>");
	syscall(4, 1, (uint32_t)msg, strlen(msg));
}

const char* num2str(uint32_t n) {
	static char s[9];
	for (int i = 0; i < 8; ++i) {
		char c = n % 16;
		if (c >= 10) {
			c = c - 10 + 'A';
		} else {
			c += '0';
		}
		n >>= 4;
		s[7 - i] = c;
	}
	s[8] = 0;
	return s;
}

void write_stdout(uint32_t n) {
	write_stdout(num2str(n));
}

void write_stdout(void* p) {
	write_stdout(num2str((uint32_t)p));
}

void print() {}
template<typename Arg0, typename ...Args>
void print(Arg0&& arg0, Args&&...args) {
	write_stdout(arg0);
	print(args...);
}

struct Elf32_auxv_t {
	uint32_t type, val;
};

extern "C"
void entry(int *argcp) {
	print("argc ", argcp, "\n");
	print("*argc ", *argcp, "\n");
	char** argv = (char**)(argcp + 1);
	for (int i = 0; i < *argcp; ++i) {
		print("argv[", i, "]=", argv[i], "\n");
	}
	char** env= argv + *argcp + 1;
	int idx = 0;
	while (*env) {
		if (idx == 3) {
			print("...\n");
		} else if (idx < 3) {
			print("env[", idx, "]=", *env, "\n");
		}
		++idx;
		++env;
	}
	print("# env vars: ", idx, "\n");
	auto aux = reinterpret_cast<Elf32_auxv_t*>(env + 1);
	char* entry = 0;
	while (aux->type) {
		if (aux->type == 9) {
			print("entry=", aux->val, "\n");
			entry = (char*)(aux->val);
		}
		++ aux;
	}
	print("elf content: ", entry, "\n");
	syscall(1, 0); //exit(0)
}

asm (R"__start__(
.globl _start
_start:
	push %esp
	call entry
)__start__"
);
