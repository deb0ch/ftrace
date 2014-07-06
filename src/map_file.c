/*
** map_file.c for ftrace in /home/ubuntu/rendu/ftrace
**
** Made by chauvo_t
** Login   <chauvo_t@epitech.net>
**
** Started on  Sun Jul  6 15:34:10 2014 chauvo_t
** Last update Sun Jul  6 16:59:44 2014 chauvo_t
*/

#include "../include/strace.h"

static size_t	file_size(int fd)
{
  size_t	size;

  size = lseek(fd, 0, SEEK_END);
  lseek(fd, 0, SEEK_SET);
  return (size);
}

int	load_file(t_mapped_file *file, char *file_name)
{
  int	fd;

  if ((fd = open(file_name, O_RDONLY)) == -1)
    {
      warn("open error on file %s", file_name);
      return (FAILURE);
    }
  file->size = file_size(fd);
  if ((file->content = mmap(NULL, file->size, PROT_READ, MAP_SHARED, fd, 0))
      == MAP_FAILED)
    {
      warn("mmap error");
      return (FAILURE);
    }
  if (close(fd) == -1)
    warn("close error");
  return (SUCCESS);
}

int	map_by_pid(t_mapped_file *file, pid_t pid)
{
  char	pathname[4096];

  sprintf(pathname, "/proc/%d/exe", pid);
  if (readlink(pathname, pathname, 4096) == -1)
    {
      warn("readlink error");
      return (FAILURE);
    }
  return (load_file(file, pathname));
}
