print.summary.RHuginDomain <- function(x, ...)
{
  if(x$domain$compiled) {
    cat("  A compiled RHugin domain : there are", length(x$node.names),
        "nodes and", sum(sapply(x$edge.list, function(u) length(u$edges))),
        "edges.\n")

    if(x$domain$evidence.propagated) {
      cat("  *Evidence has been propagated.\n")
      cat("    *The equilibrium is ", x$domain$equilibrium, ".\n", sep = "")
      cat("    *The evidence mode is ", x$domain$evidence.mode, ".\n", sep = "")
    }

    else
      cat("  8No evidence has been propagated.\n")

    if(x$domain$evidence.to.propagate)
      cat("  *Evidence has been entered since the last propagation.\n")

    if(x$domain$tables.to.propagate)
      cat("  *One or more tables have changed since the last propagation.\n")

  }

  else {
    cat("  An uncompiled RHugin domain : there are", length(x$node.names),
        "nodes and", sum(sapply(x$edge.list, function(u) length(u$edges))),
        "edges.\n")
  }

  cat("\n")

  for(name in names(x$nodes)) {
    cat(name, ":\n", sep = "")
    cat("      kind: ", x$nodes[[name]]$kind, "\n", sep = "")
    cat("  category: ", x$nodes[[name]]$category, "\n", sep = "")
    cat("   subtype: ", x$nodes[[name]]$subtype, "\n", sep = "")
    if(!is.null(x$nodes[[name]]$states))
      cat("    states: ", "{", paste(x$nodes[[name]]$states, collapse = ", "),
          "}\n\n", sep = "")
  }

  invisible(x)
}


