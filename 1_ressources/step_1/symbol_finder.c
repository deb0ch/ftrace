/*
** symbol_finder.c for tp_ftrace in /home/ubuntu/TP/unix_avance_ftrace/step_1
**
** Made by chauvo_t
** Login   <chauvo_t@epitech.net>
**
** Started on  Thu Jun  5 14:43:13 2014 chauvo_t
** Last update Fri Jun  6 12:36:22 2014 chauvo_t
*/

#include <err.h>
#include <fcntl.h>
#include <gelf.h>
#include <libelf.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sysexits.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

Elf		*elf;
Elf64_Ehdr	*elf_header;
Elf_Scn		*scn;		/* Section Descriptor */
Elf_Data	*edata;		/* Data Descriptor */
GElf_Sym	sym;
GElf_Shdr	shdr;		/* Section Header */

int	main(int ac, char **av)
{
  struct stat	elf_stats;	/* fstat struct */
  int		fd;
  char		*base_ptr;
  int		symbol_count;
  int		i;

  if (ac < 3)
    errx(EX_USAGE, "USAGE: %s [PROGRAM_NAME] [ADDRESS]", *av);

  if ((fd = open(av[1], O_RDONLY, 0)) < 0)
    err(EX_NOINPUT, "open %s failed ", av[1]);

  if((fstat(fd, &elf_stats)))
    {
      printf("could not fstat %s\n", av[1]);
      close(fd);
      return (EXIT_FAILURE);
    }

  if((base_ptr = (char *) malloc(elf_stats.st_size)) == NULL)
    {
      printf("could not malloc\n");
      close(fd);
      return (EXIT_FAILURE);
    }

  if((read(fd, base_ptr, elf_stats.st_size)) < elf_stats.st_size)
    {
      printf("could not read %s\n", *av);
      free(base_ptr);
      close(fd);
      return (EXIT_FAILURE);
    }

  if (elf_version(EV_CURRENT) == EV_NONE)
    errx(EX_SOFTWARE, "ELF library initialization failed : %s", elf_errmsg(-1));

  elf_header = (Elf64_Ehdr*)base_ptr;

  if((elf = elf_begin(fd, ELF_C_READ, NULL )) == NULL )
    errx(EX_SOFTWARE, "elf_begin() failed : %s .", elf_errmsg(-1));

  while((scn = elf_nextscn(elf, scn)) != NULL)
    {
      gelf_getshdr(scn, &shdr);
      // When we find a section header marked SHT_SYMTAB stop and get symbols
      if(shdr.sh_type == SHT_SYMTAB)
        {
	  // edata points to our symbol table
	  edata = elf_getdata(scn, edata);
	  // how many symbols are there? this number comes from the size of
	  // the section divided by the entry size
	  symbol_count = shdr.sh_size / shdr.sh_entsize;
	  // loop through to grab all symbols
	  for(i = 0; i < symbol_count; i++)
	    {
	      // libelf grabs the symbol data using gelf_getsym()
	      gelf_getsym(edata, i, &sym);
	      if (sym.st_value == strtol(av[2], NULL, 16))
		printf("%s found at 0x%lx\n", elf_strptr(elf, shdr.sh_link, sym.st_name),
		       strtol(av[2], NULL, 16)); /* TODO: check error */
	    }
	}
    }
  (void)elf_end(elf);
  (void)close(fd);
  exit(EX_OK);
  return (0);
}
