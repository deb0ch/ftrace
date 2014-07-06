/*
** graph.c for ftrace in /home/max/e-wip/ftrace
** 
** Made by bourge_i
** Login   <max@epitech.net>
** 
** Started on  Fri Jun 27 17:29:42 2014 bourge_i
** Last update Sun Jul  6 17:05:42 2014 bourge_i
*/

#include <stdlib.h>
#include <string.h>
#include "../include/graph.h"

t_graph_node            *add_node(struct s_graph *this, char *fct_name,
                                  t_graph_node *parent, int is_syscall)
{
  static t_graph_node   *current = NULL;
  t_graph_node          *node;
  static int            id = 0;
  
  if ((node = malloc(sizeof(t_graph_node))) == NULL)
    {
      printf("MALLOC() Failed\n");
      return (NULL);
    }
  node->id = id;
  node->fct_name = strdup(fct_name);
  node->parent_id = (parent) ? parent->id : -1;
  node->next = NULL;
  fprintf(this->graph_file, "node [shape=box, style=rounded, color=%s];\n", (is_syscall) ? "red" : "lightblue");
  fprintf(this->graph_file, "\"%s\" -> \"%s\";\n",
          (parent) ? parent->fct_name : "_START_", fct_name);
  if (current != NULL)
    current->next = node;
  else
    this->graph_list = node;
  current = node;
  if (!is_syscall)
    this->current = node;
  id++;
  return (current);
}

void            pop(struct s_graph *this)
{
  t_graph_node  *parent;

  printf("1\n");
  parent = find_parent_node(this, this->current);
  if (parent == NULL)
    {
      printf("Parent not found, fct_name : %s\n", this->current->fct_name);
      return ;
    }
  free(this->current->fct_name);
  free(this->current);
  printf("2\n");
  this->current = parent;
  printf("3\n");
  this->current->next = NULL;
}

int             close_graph(struct s_graph *this)
{
  fprintf(this->graph_file, "}\n");
  fclose(this->graph_file);
  if (system("dot -Tpng graph.dot -o graph.png") == -1)
    return (-1);
  return (0);
}

int             create_graph(struct s_graph *this)
{
  if ((this->graph_file = fopen("graph.dot", "w+")) == NULL)
    {
      printf("FOPEN() failed\n");
      return (-1);
    }
  fprintf(this->graph_file, "strict digraph{\n");
  fprintf(this->graph_file, "node [shape=box, style=rounded, color=lightblue];\n");
  fprintf(this->graph_file, "rankdir=TB;\n");
  fprintf(this->graph_file, "label=\"Ftrace\";\n");
  return(0);
}

t_graph*        graph_init()
{
  t_graph       *graph;

  if ((graph = malloc(sizeof(t_graph))) == NULL)
    {
      printf("MALLOC() failed\n");
      return (NULL);
    }
  create_graph(graph);
  graph->add_node = &add_node;
  graph->close_graph = &close_graph;
  graph->pop = &pop;
  graph->current = NULL;
  return (graph);
}
