/*
** map_file.c for ftrace in /home/ubuntu/rendu/ftrace
**
** Made by chauvo_t
** Login   <chauvo_t@epitech.net>
**
** Started on  Sun Jul  6 15:34:10 2014 chauvo_t
** Last update Sun Jul  6 17:34:08 2014 bourge_i
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
      warn("open error YOLO on file %s", file_name);
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
  char	pathname_symlink[4096];
  char	pathname[4096];

  pathname_symlink[0] = '\0';
  pathname[0] = '\0';
  /* sprintf(pathname_symlink, "/proc/%d/exe", pid); */
  if (readlink(pathname_symlink, pathname, 4096) == -1)
    {
      warn("readlink error");
      return (FAILURE);
    }
  /* printf("pathname_symlink = %s, pathname = %s\n", pathname_symlink, pathname); */
  return (load_file(file, pathname));
}
