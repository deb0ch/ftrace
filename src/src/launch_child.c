/*
** launch_child.c for strace in /home/ubuntu/rendu/AUSP_strace
**
** Made by chauvo_t
** Login   <chauvo_t@epitech.net>
**
** Started on  Fri May 16 19:22:26 2014 chauvo_t
** Last update Sat May 17 00:40:55 2014 chauvo_t
*/

#include "strace.h"

int	launch_child(char **cmd)
{
  if (ptrace(PTRACE_TRACEME, 0, NULL, NULL) == -1)
    {
      warn("ptrace PTRACE_TRACEME error");
      return (FAILURE);
    }
  (void)raise(SIGSTOP);
  (void)execvp(*cmd, cmd);
  warn("execvp error");
  return (FAILURE);
}
