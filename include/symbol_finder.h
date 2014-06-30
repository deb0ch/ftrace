/*
** symbol_finder.h for ftrace in /home/ubuntu/rendu/ftrace
**
** Made by chauvo_t
** Login   <chauvo_t@epitech.net>
**
** Started on  Mon Jun 23 17:25:32 2014 chauvo_t
** Last update Mon Jun 23 19:53:30 2014 chauvo_t
*/

#ifndef SYMBOL_FINDER_H_
# define SYMBOL_FINDER_H_

typedef struct	s_libelf_data
{
  Elf_Data	*edata;
  Elf_Scn	*scn;
  Elf		*elf;
}		t_libelf_data;

#endif /* !SYMBOL_FINDER_H_ */
