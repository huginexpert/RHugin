print.RHuginDomain <- function(x, ...)
{
  nodes <- get.nodes(x)
  edge.list <- get.edges(x)

  if(length(nodes) > 10) {
    cat("  A Hugin domain: there are", length(nodes),
        "nodes and", sum(sapply(edge.list, function(u) length(u$edges))),
        "edges\n\n")
  }

  else {
    edges <- character(0)
    for(node in nodes)
      if(length(edge.list[[node]]$edges))
        edges <- c(edges, paste(node, edge.list[[node]]$edges, sep = " -> "))

    cat("A Hugin domain\n")
    cat("Nodes: ")
    cat(nodes)
    cat("\n")
    cat("Edges:\n")
    for(edge in edges) {
      cat("  ")
      cat(edge)
      cat("\n")
    }
  }

  invisible(x)
}


