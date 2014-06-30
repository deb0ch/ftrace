/*
** symbol_finder.c for tp_ftrace in /home/ubuntu/TP/unix_avance_ftrace/step_1
**
** Made by chauvo_t
** Login   <chauvo_t@epitech.net>
**
** Started on  Thu Jun  5 14:43:13 2014 chauvo_t
** Last update Mon Jun 30 16:02:10 2014 chauvo_t
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

#include "../include/symbol_finder.h"

static t_libelf_data	g_libelf_data;

char	*symbol_finder(int fd, long long unsigned address)
{
  struct stat	elf_stats;
  GElf_Sym	sym;
  GElf_Shdr	shdr;
  char		*base_ptr;
  int		symbol_count;
  int		i;

  if ((fstat(fd, &elf_stats)))
    {
      printf("could not fstat\n");
      close(fd);
      return ("unknown symbol");
    }
  if ((base_ptr = (char *)malloc(elf_stats.st_size)) == NULL)
    {
      printf("could not malloc\n");
      close(fd);
      return ("unknown symbol");
    }
  if ((read(fd, base_ptr, elf_stats.st_size)) < elf_stats.st_size)
    {
      printf("could not read file\n");
      free(base_ptr);
      close(fd);
      return ("unknown symbol");
    }
  if ((g_libelf_data.elf = elf_begin(fd, ELF_C_READ, NULL )) == NULL )
    errx(EX_SOFTWARE, "elf_begin() failed : %s .", elf_errmsg(-1));
  while ((g_libelf_data.scn = elf_nextscn(g_libelf_data.elf,
					 g_libelf_data.scn)) != NULL)
    {
      gelf_getshdr(g_libelf_data.scn, &shdr);
      if (shdr.sh_type == SHT_SYMTAB)
        {
	  g_libelf_data.edata = elf_getdata(g_libelf_data.scn, g_libelf_data.edata);
	  symbol_count = shdr.sh_size / shdr.sh_entsize; /* TODO: possible FPE */
	  i = 0;
	  while (i < symbol_count)
	    {
	      gelf_getsym(g_libelf_data.edata, i, &sym);
	      if (sym.st_value == address)
		return (elf_strptr(g_libelf_data.elf, shdr.sh_link, sym.st_name));
	      ++i;
	    }
	}
    }
  return ("unknown symbol");
}

/* int	main(int ac, char **av) */
/* { */
/*   char		*symbol; */
/*   int		fd; */

/*   if (ac < 3) */
/*     errx(EX_USAGE, "USAGE: %s [PROGRAM_NAME] [ADDRESS]", *av); */
/*   if ((fd = open(av[1], O_RDONLY, 0)) < 0) */
/*     err(EX_NOINPUT, "open %s failed ", av[1]); */
/*   if (elf_version(EV_CURRENT) == EV_NONE) */
/*     errx(EX_SOFTWARE, "ELF library initialization failed : %s", elf_errmsg(-1)); */
/*   if ((symbol = symbol_finder(fd, strtol(av[2], NULL, 16))) != NULL) */
/*     printf("%s found at 0x%lx\n", symbol, strtol(av[2], NULL, 16)); */
/*   (void)elf_end(g_libelf_data.elf); */
/*   (void)close(fd); */
/*   exit(EX_OK); */
/*   return (0); */
/* } */
