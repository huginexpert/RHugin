as.graph.RHuginDomain <- function(x, ...)
{
  nodes <- get.nodes(x)
  edge.list <- get.edges(x)
  for(node in nodes)
    edge.list[[node]]$edges <- as.numeric(match(edge.list[[node]]$edges, nodes))

  new("graphNEL", nodes = nodes, edgeL = edge.list, edgemode = "directed")
}


