/*
** graph_utils.c for ftrace in /home/max/e-wip/ftrace/src
**
** Made by bourge_i
** Login   <max@epitech.net>
**
** Started on  Wed Jul  2 14:02:24 2014 bourge_i
** Last update Sun Jul  6 22:09:06 2014 chauvo_t
*/

#include <stdlib.h>
#include "graph.h"

int		print_graph(t_graph *this)
{
  t_graph_node	*current;
  char		*name;

  current = this->graph_list;
  while (current != NULL)
    {
      printf("ID: \t[%d]\n", current->id);
      printf("Name: \t[%s]\n", current->fct_name);
      name = find_parent_name(this, current);
      printf("Parent: [%s]\n", (name) ? name : "NONE");
      printf("--------------------\n");
      current = current->next;
    }
  return (0);
}

int		free_graph(t_graph *this)
{
  t_graph_node	*current;
  t_graph_node	*old;

  current = this->graph_list;
  while (current != NULL)
    {
      old = current;
      current = current->next;
      free(old->fct_name);
      free(old);
    }
  free(this);
  return (0);
}

char		*find_parent_name(t_graph *this, t_graph_node *node)
{
  t_graph_node	*current;

  current = this->graph_list;
  while (current != NULL && current->id != node->parent_id)
    current = current->next;
  if (current != NULL && current->id != -1)
    return (current->fct_name);
  else
    return (NULL);
}

t_graph_node	*find_parent_node(t_graph *this, t_graph_node *node)
{
  t_graph_node	*current;

  current = this->graph_list;
  while (current != NULL && current->id != node->parent_id)
    current = current->next;
  if (current != NULL && current->id != -1)
    return (current);
  else
    return (NULL);
}
