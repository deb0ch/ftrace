#include "../include/symbol_finder.h"

int	main(int ac, char **av)
{
  struct stat	elf_stats;
  char		*file_ptr;

  char		*symbol;
  int		fd;

  if (ac < 3)
    errx(EX_USAGE, "USAGE: %s [PROGRAM_NAME] [ADDRESS]", *av);
  if ((fd = open(av[1], O_RDONLY, 0)) < 0)
    err(EX_NOINPUT, "open %s failed ", av[1]);
  if (elf_version(EV_CURRENT) == EV_NONE)
    errx(EX_SOFTWARE, "ELF library initialization failed : %s", elf_errmsg(-1));

  /* if ((symbol = symbol_finder_fd(fd, strtol(av[2], NULL, 16))) != NULL) */
  /*   printf("%s found at 0x%lx\n", symbol, strtol(av[2], NULL, 16)); */

    if ((fstat(fd, &elf_stats)))
    {
      printf("could not fstat\n");
      close(fd);
      return (EXIT_FAILURE);
    }
  if ((file_ptr = (char *)malloc(elf_stats.st_size)) == NULL)
    {
      printf("could not malloc\n");
      close(fd);
      return (EXIT_FAILURE);
    }
  if ((read(fd, file_ptr, elf_stats.st_size)) < elf_stats.st_size)
    {
      printf("could not read file_ptr\n");
      free(file_ptr);
      close(fd);
      return (EXIT_FAILURE);
    }
  if ((symbol = symbol_finder_ptr(file_ptr, elf_stats.st_size, strtol(av[2], NULL, 16))) != NULL)
    printf("%s found at 0x%lx\n", symbol, strtol(av[2], NULL, 16));

  printf("file size = %lu\n", elf_stats.st_size);
  /* (void)elf_end(g_elf_data.elf); */
  (void)close(fd);
  exit(EX_OK);
  return (0);
}
