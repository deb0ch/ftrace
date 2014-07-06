/*
** symbol_finder.h for ftrace in /home/ubuntu/rendu/ftrace
**
** Made by chauvo_t
** Login   <chauvo_t@epitech.net>
**
** Started on  Mon Jun 23 17:25:32 2014 chauvo_t
** Last update Sun Jul  6 22:06:59 2014 chauvo_t
*/

#ifndef SYMBOL_FINDER_H_
# define SYMBOL_FINDER_H_

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

typedef struct	s_libelf_data
{
  Elf_Data	*edata;
  Elf_Scn	*scn;
  Elf		*elf;
}		t_libelf_data;

char	*symbol_finder_ptr(void* file_ptr, size_t file_size,
			   long long unsigned address);
char	*symbol_finder_fd(int fd, long long unsigned address);

#endif /* !SYMBOL_FINDER_H_ */
