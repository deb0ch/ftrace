/*
** print_types2.c for strace in /home/ubuntu/rendu/AUSP_strace
**
** Made by chauvo_t
** Login   <chauvo_t@epitech.net>
**
** Started on  Thu May 15 00:57:02 2014 chauvo_t
** Last update Sun May 18 16:57:31 2014 chauvo_t
*/

#include "strace.h"

extern pid_t	g_tracee_pid;

static void	print_char(char c)
{
  if (((c > 32 && c < 127) || c == ' ') && c != '\0')
    (void)fprintf(stderr, "%c", c);
  else if (c != '\n' && c != '\0')
    (void)fprintf(stderr, "\\%o", c);
}

void	print_string(unsigned long long int register_value)
{
  int	i;
  long	c;

  (void)fprintf(stderr, "\"");
  i = 0;
  c = -1;
  while ((char)c != '\0' && i < 42)
    {
      if ((c = ptrace(PTRACE_PEEKDATA, g_tracee_pid,
		      register_value, NULL)) == -1)
	{
	  fprintf(stderr, "\033[36mptrace PTRACE_PEEK_DATA error: ");
	  fprintf(stderr, "%s\033[33m\"", strerror(errno));
	  return ;
	}
      print_char(c);
      ++register_value;
      ++i;
    }
  (void)fprintf(stderr, "\"");
}

void			print_string_tab(unsigned long long int register_value)
{
  unsigned long long	str;
  int			i;

  (void)fprintf(stderr, "[");
  i = 0;
  str = (unsigned long long)-1;
  while ((void*)str != NULL && i < 6)
    {
      if ((str = ptrace(PTRACE_PEEKDATA, g_tracee_pid,
			register_value, NULL)) == (unsigned long long)-1)
	{
	  fprintf(stderr, "\033[36mptrace PTRACE_PEEK_DATA error: ");
	  fprintf(stderr, "%s\033[33m]", strerror(errno));
	  return ;
	}
      if (str)
	print_string(str);
      register_value += sizeof(char*);
      ++i;
    }
  (void)fprintf(stderr, "]");
  if (i >= 6)
    (void)fprintf(stderr, " ... ");
}

void	print_unimplemented(unsigned long long int register_value)
{
  (void)register_value;
  (void)fprintf(stderr, "unimplemented");
}

void	print_nothing(unsigned long long int register_value)
{
  (void)register_value;
}
