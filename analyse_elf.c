#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>

#include <err.h>
#include <fcntl.h>
#include <sysexits.h>

#include <libelf.h>
#include <gelf.h>
#include <bsd/vis.h>


int     main(int argc, char *argv[])
{
  int           fd;
  int           i;
  
  Elf           *e;
  char          *id;
  char          bytes[5];
  size_t        n;

  GElf_Ehdr     ehdr;

  if (argc != 2)
    errx(EX_USAGE, "usage: %s file-name", argv[0]);
  if (elf_version(EV_CURRENT) == EV_NONE)
    errx(EX_SOFTWARE, "ELF library initialisation failde: %s", elf_errmsg(-1));
  if ((fd = open(argv [1], O_RDONLY, 0)) < 0)
    err(EX_NOINPUT, " open \%s \" failed ", argv [1]);
  if ((e = elf_begin(fd, ELF_C_READ, NULL)) == NULL)
    errx (EX_SOFTWARE, " elf_begin () failed : %s . ", elf_errmsg(-1));

  if (elf_kind(e) != ELF_K_ELF)
    errx(EX_DATAERR, "\"%s\" is not an ELF object", argv[1]);
  if (gelf_getehdr(e, & ehdr) == NULL)
    errx(EX_SOFTWARE, "getehdr() failed: %s .", elf_errmsg(-1));
  if (( i = gelf_getclass ( e )) == ELFCLASSNONE )
    errx(EX_SOFTWARE, "getclass() failed: %s .", elf_errmsg(-1));
  
  (void)printf("%s: %d-bit ELF object \n", argv [1], i == ELFCLASS32 ? 32 : 64);

  if ((id = elf_getident(e, NULL)) == NULL)
    errx (EX_SOFTWARE, "getident() failed: %s .", elf_errmsg(-1));
  (void)printf("%3s e_ident[0..%1d] %7s", " ", EI_ABIVERSION, " ");
  
  for (i = 0; i <= EI_ABIVERSION; ++i)
    {
      (void)vis(bytes, id[i], VIS_WHITE, 0);
      (void)printf(" ['%s' %X]", bytes, id[i]);
    }
  (void)printf("\n");

# define PRINT_FMT "%-20s 0x%jx\n"
# define PRINT_FIELD(N) do { \
    (void)printf(PRINT_FMT, #N, (uintmax_t) ehdr.N); \
  } while (0)

  PRINT_FIELD(e_type);
  PRINT_FIELD(e_machine);
  PRINT_FIELD(e_version);
  PRINT_FIELD(e_entry);
  PRINT_FIELD(e_phoff);
  PRINT_FIELD(e_shoff);
  PRINT_FIELD(e_flags);
  PRINT_FIELD(e_ehsize);
  PRINT_FIELD(e_phentsize);
  PRINT_FIELD(e_shentsize);

  if (elf_getshnum(e, &n) != 0)
    errx(EX_SOFTWARE, "getshdrstrndx() failed: %s .", elf_errmsg(-1));
  (void)printf(PRINT_FMT, "(shstrndx)", (uintmax_t)n);

  if (elf_getphnum(e, &n) != 0)
    errx(EX_SOFTWARE, "getphdrnum() failed: %s.", elf_errmsg(-1));
  (void)printf(PRINT_FMT, "(phnum)", (uintmax_t)n);
  
  (void)elf_end(e);
  (void)close(fd);
  
  exit(EX_OK);
}


















