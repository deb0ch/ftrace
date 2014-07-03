/*
** graph.c for ftrace in /home/max/e-wip/ftrace
** 
** Made by bourge_i
** Login   <max@epitech.net>
** 
** Started on  Fri Jun 27 17:29:42 2014 bourge_i
** Last update Wed Jul  2 15:05:25 2014 bourge_i
*/

#include <stdlib.h>
#include <string.h>
#include "../include/graph.h"

t_graph_node            *add_node(struct s_graph *this, char *fct_name, t_graph_node *parent)
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
  fprintf(this->graph_file, "\"%s\" -> \"%s\";\n",
          (parent) ? parent->fct_name : "_START_", fct_name);
  if (current != NULL)
    current->next = node;
  else
    this->graph_list = node;
  current = node;
  id++;
  return (current);
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
  fprintf(this->graph_file, "digraph{\n");
  fprintf(this->graph_file, "node [shape=box, style=filled, color=lightblue];\n");
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
  return (graph);
}
