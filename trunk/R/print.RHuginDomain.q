print.RHuginDomain <- function(x, ...)
{
  cat("A Hugin domain\n")
  cat("Node set: ")
  cat(get.nodes(x))
  cat("\n")
  cat("Edge Set:\n")
  edges <- get.edges(x)
  for(edge in edges) {
    cat("  ")
    cat(edge)
    cat("\n")
  }
  invisible(x)
}


