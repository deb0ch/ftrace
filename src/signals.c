/*
** signals.c for ftrace in /home/ubuntu/rendu/ftrace
**
** Made by chauvo_t
** Login   <chauvo_t@epitech.net>
**
** Started on  Sun Jul  6 21:00:00 2014 chauvo_t
** Last update Sun Jul  6 21:38:11 2014 chauvo_t
*/

#include "strace.h"

const t_signal	g_signals[] =
  {
    {0, "UNKNOWN"},
    {1, "SIGHUP"},
    {2, "SIGINT"},
    {3, "SIGQUIT"},
    {4, "SIGILL"},
    {5, "SIGTRAP"},
    {6, "SIGABRT"},
    {7, "SIGIOT"},
    {8, "SIGBUS"},
    {9, "SIGFPE"},
    {10, "SIGUSR1"},
    {11, "SIGSEGV"},
    {12, "SIGUSR2"},
    {13, "SIGPIPE"},
    {14, "SIGALRM"},
    {15, "SIGTERM"},
    {16, "SIGSTKFLT"},
    {17, "SIGCHLD"},
    {18, "SIGCONT"},
    {19, "SIGSTOP"},
    {20, "SIGTSTP"},
    {21, "SIGTTIN"},
    {22, "SIGTTOU"},
    {23, "SIGURG"},
    {24, "SIGXCPU"},
    {25, "SIGXFSZ"},
    {26, "SIGVTALRM"},
    {27, "SIGPROF"},
    {28, "SIGWINCH"},
    {29, "SIGIO"},
    {29, "SIGPOLL"},
    {30, "SIGPWR"},
    {31, "SIGSYS"},
    {0, NULL}
  };
