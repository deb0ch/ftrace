/*
** trace.c for strace in /home/ubuntu/rendu/AUSP_strace
**
** Made by chauvo_t
** Login   <chauvo_t@epitech.net>
**
** Started on  Wed May 14 21:58:47 2014 chauvo_t
** Last update Sun May 18 20:11:45 2014 chauvo_t
*/

#include "strace.h"

pid_t	g_tracee_pid = -1;

extern t_prototype	g_syscalls[];

static int	step_instruction(pid_t pid, int *status)
{
  handle_exit(status);
  if (ptrace(PTRACE_SINGLESTEP, pid, NULL, NULL) == -1)
    {
      warn("trace PTRACE_SINGLESTEP error");
      return (FAILURE);
    }
  if (waitpid(pid, status, 0) == -1)
    {
      warn("wait error");
      return (FAILURE);
    }
  return (SUCCESS);
}

static int		analyse_syscall(struct user_regs_struct *registers,
					pid_t pid, int *status)
{
  unsigned long long	syscall_number;

  syscall_number = registers->rax;
  if (syscall_number > MAX_SYSCALL
      || print_syscall(syscall_number, registers) == FAILURE)
    return (FAILURE);
  if (syscall_number != 60 && syscall_number != 231)
    {
      if (syscall_number == 1)
	fprintf(stderr, "\033[0m\n");
      if (step_instruction(pid, status) == FAILURE
	  || ptrace(PTRACE_GETREGS, pid, NULL, registers) == -1)
	return (FAILURE);
    }
  (void)print_return_value(syscall_number,
			   g_syscalls[syscall_number].ret_type, registers);
  if (syscall_number == 60 || syscall_number == 231)
    {
      (void)printf(" was returned by tracee");
      (void)system("echo -n $?");
      (void)printf("\n");
      exit(EXIT_SUCCESS);
    }
  return (SUCCESS);
}

static int		analyse_registers(struct user_regs_struct *registers,
					  pid_t pid, int *status)
{
  long			rip_pointed_data;

  if ((rip_pointed_data = ptrace(PTRACE_PEEKDATA, pid,
				 registers->rip, NULL)) == -1)
    return (FAILURE);
  rip_pointed_data &= 0xffff;
  if (rip_pointed_data == SYSCALL_OPCODE)
    {
      if (analyse_syscall(registers, pid, status) == FAILURE)
	return (FAILURE);
    }
  return (SUCCESS);
}

int				trace_process(pid_t pid)
{
  struct user_regs_struct	registers;
  int				status;

  if (waitpid(pid, &status, 0) == -1)
    {
      warn("wait error");
      return (FAILURE);
    }
  while (42)
    {
      if (ptrace(PTRACE_GETREGS, pid, NULL, &registers) == -1)
	{
	  warn("ptrace PTRACE_GETREGS error");
	  return (FAILURE);
	}
      if (analyse_registers(&registers, pid, &status) == FAILURE)
	return (FAILURE);
      if (step_instruction(pid, &status) == FAILURE)
	return (FAILURE);
    }
}
