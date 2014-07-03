/*
** main.c for ftrace in /home/max/e-wip/ftrace/src
** 
** Made by bourge_i
** Login   <max@epitech.net>
** 
** Started on  Wed Jul  2 14:02:14 2014 bourge_i
** Last update Wed Jul  2 14:59:39 2014 bourge_i
*/

#include <stdlib.h>
#include "../include/graph.h"

int main(void)
{
  t_graph       *my_graph;
  t_graph_node  *my_node;
  t_graph_node  *save;
  
  my_graph = graph_init();
  my_node = my_graph->add_node(my_graph, "test1", NULL);
  save = my_node = my_graph->add_node(my_graph, "test2", my_node);
  my_node = my_graph->add_node(my_graph, "test3", my_node);
  my_node = my_graph->add_node(my_graph, "test4000", save);
  my_graph->close_graph(my_graph);
  print_graph(my_graph);
  free_graph(my_graph);
  return (0);
}










