print.RHuginDomain <- function(x, ...)
{
  nodes <- get.nodes(x)
  edge.list <- get.edges(x)
  edges <- character(0)
  for(node in nodes)
    if(length(edge.list[[node]]$edges))
      edges <- c(edges, paste(node, edge.list[[node]]$edges, sep = " -> "))

  cat("A Hugin domain\n")
  cat("Node set: ")
  cat(nodes)
  cat("\n")
  cat("Edge Set:\n")
  for(edge in edges) {
    cat("  ")
    cat(edge)
    cat("\n")
  }

  invisible(x)
}


