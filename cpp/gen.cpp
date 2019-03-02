//g++ gen.cpp -std=c++11 -o gen
#include <cstring>
#include <cstdio>
#include <elf.h>
#include <sys/stat.h>

int main() {
	uint8_t buf[1024] = {0};
	auto hdr = reinterpret_cast<Elf32_Ehdr*>(buf);
	memcpy(hdr->e_ident, "\177ELF", 4);
	hdr->e_ident[EI_CLASS] = ELFCLASS32;
	hdr->e_ident[EI_DATA] = ELFDATA2LSB;
	hdr->e_ident[EI_VERSION] = EV_CURRENT;
	hdr->e_phentsize = sizeof(Elf32_Phdr);
	hdr->e_phnum = 2;
	hdr->e_type = ET_EXEC;
	hdr->e_machine = EM_386;
	hdr->e_version = EV_CURRENT;
	hdr->e_ehsize = sizeof(*hdr);
	
	Elf32_Phdr *phdr_payload = reinterpret_cast<Elf32_Phdr*>(hdr + 1), *phdr_interp = phdr_payload + 1;
	
	char* payload = reinterpret_cast<char*>(phdr_interp + 1);
	strcpy(payload, "hello, world!");
	phdr_payload->p_type = PT_LOAD;
	phdr_payload->p_offset = 0;
	phdr_payload->p_paddr = phdr_payload->p_vaddr = 0x02340000;
	phdr_payload->p_filesz = phdr_payload->p_memsz = sizeof(buf);
	phdr_payload->p_flags = PF_R | PF_X;
	phdr_payload->p_align = 0x1000;
	
	char* interp = payload + strlen(payload) + 1;
	strcpy(interp, "./interp");
	size_t interp_size = strlen(interp) + 1;
	phdr_interp->p_type = PT_INTERP;
	phdr_interp->p_offset = phdr_interp->p_paddr = phdr_interp->p_vaddr = interp - (char*)hdr;
	phdr_interp->p_filesz = phdr_interp->p_memsz = interp_size;
	phdr_interp->p_flags = PF_R;
	phdr_interp->p_align = 1;
	
	hdr->e_entry = phdr_payload->p_vaddr + payload - (char*)hdr;
	hdr->e_phoff = (uint8_t*) phdr_payload - (uint8_t*)hdr;
	
	FILE* fout = fopen("myelf", "wb");
	fwrite(buf, sizeof(buf), 1, fout);
	fclose(fout);
	chmod("myelf", 0755);
}
