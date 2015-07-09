/*
** symbol_finder.c for tp_ftrace in /home/ubuntu/TP/unix_avance_ftrace/step_1
**
** Made by chauvo_t
** Login   <chauvo_t@epitech.net>
**
** Started on  Thu Jun  5 14:43:13 2014 chauvo_t
** Last update Sun Jul  6 22:16:26 2014 chauvo_t
*/

#include "../include/symbol_finder.h"

t_libelf_data	g_elf_data;

static char	*do_find_symbol(long long unsigned address)
{
  GElf_Sym	sym;
  GElf_Shdr	shdr;
  int		symbol_count;
  int		i;

  while ((g_elf_data.scn = elf_nextscn(g_elf_data.elf,
				       g_elf_data.scn)) != NULL)
    {
      gelf_getshdr(g_elf_data.scn, &shdr);
      if (shdr.sh_type == SHT_SYMTAB)
        {
	  g_elf_data.edata = elf_getdata(g_elf_data.scn, g_elf_data.edata);
	  symbol_count = shdr.sh_size / shdr.sh_entsize;
	  i = 0;
	  while (i < symbol_count)
	    {
	      gelf_getsym(g_elf_data.edata, i, &sym);
	      if (sym.st_value == address)
		return (elf_strptr(g_elf_data.elf, shdr.sh_link, sym.st_name));
	      ++i;
	    }
	}
    }
  return ("unknown symbol");
}

char	*symbol_finder_fd(int fd, long long unsigned address)
{
  if (elf_version(EV_CURRENT) == EV_NONE)
    errx(EX_SOFTWARE, "ELF library initialization failed : %s", elf_errmsg(-1));
  if ((g_elf_data.elf = elf_begin(fd, ELF_C_READ, NULL)) == NULL)
    errx(EX_SOFTWARE, "elf_begin() failed : %s .", elf_errmsg(-1));
  return (do_find_symbol(address));
}

char	*symbol_finder_ptr(void* file_ptr, size_t file_size,
			   long long unsigned address)
{
  if (elf_version(EV_CURRENT) == EV_NONE)
    errx(EX_SOFTWARE, "ELF library initialization failed : %s", elf_errmsg(-1));
  if ((g_elf_data.elf = elf_memory(file_ptr, file_size)) == NULL)
    errx(EX_SOFTWARE, "elf_memory() failed : %s .", elf_errmsg(-1));
  return (do_find_symbol(address));
}
