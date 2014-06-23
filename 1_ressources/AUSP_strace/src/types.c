/*
** types.c for strace in /home/ubuntu/rendu/AUSP_strace
**
** Made by chauvo_t
** Login   <chauvo_t@epitech.net>
**
** Started on  Thu May 15 09:34:50 2014 chauvo_t
** Last update Sat May 17 00:30:30 2014 chauvo_t
*/

#include "strace.h"

const t_types	g_types[] =
  {
    {"void", &print_nothing},
    {"char *", &print_string},
    {"char **", &print_string_tab},
    {"int", &print_int},
    {"int[2]", &print_pointer},
    {"uint32_t", &print_uint},
    {"unsigned int", &print_uint},
    {"long", &print_long},
    {"unsigned long", &print_ulong},
    {"u64", &print_ulong},
    {"size_t", &print_ulong},
    {"ssize_t", &print_long},
    {"caddr_t", &print_string},
    {"ndfs_t", &print_int},
    {"off_t", &print_ulong},
    {"key_t", &print_ulong},
    {"pid_t", &print_int},
    {"socklen_t", &print_ulong},
    {"uid_t", &print_int},
    {"gid_t", &print_int},
    {"gid_t[]", &print_pointer},
    {"clock_t", &print_ulong},
    {"cap_user_header_t", &print_pointer},
    {"cap_huser_data_t", &print_pointer},
    {"dev_t", &print_ulong},
    {"off64_t", &print_ulong},
    {"cpu_set_t", &print_ulong},
    {"aio_context_t", &print_ulong},
    {"mqd_t", &print_int},
    {"idtype_t", &print_ulong},
    {"key_serial_t", &print_ulong},
    {"unimplemented", &print_unimplemented},
    {"default", &print_pointer},
    {NULL, NULL}
  };
