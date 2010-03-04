print.summary.RHuginDomain <- function(x, ...)
{
  if(!is.null(domain <- x$domain)) {
    cat("An RHugin domain:\n")

    if(domain[["triangulated"]])
      cat("  Triangulated: the domain is triangulated\n", sep = "")
    else
      cat("  Triangulated: the domain is not triangulated\n", sep = "")

    if(domain[["compiled"]]) {
      cat("  Compiled:     the domain is compiled\n", sep = "")

      if(domain[["compressed"]])
        cat("  Compressed:   the domain is compressed\n", sep = "")
      else
        cat("  Compressed:   the domain is not compressed\n", sep = "")

      if(domain[["evidence.propagated"]]) {
        cat("  Evidence:     evidence has been propagated\n")
        cat("    Equilibrium:   ", domain[["equilibrium"]], "\n", sep = "")
        cat("    Evidence mode: ", domain[["evidence.mode"]][1], "\n\n", sep = "")
      }

      else
        cat("  Evidence:     no evidence has been propagated\n\n")

      if(domain[["evidence.to.propagate"]])
        cat("  New evidence has been entered since the last propagation\n")
      else
        cat("  No evidence has been entered since the last propagation\n")

      if(domain[["tables.to.propagate"]])
        cat("  One or more tables have changed since the last propagation\n\n")
      else
        cat("  No tables have been altered since the last propagation\n\n")
    }

    else
      cat("  Compiled:     the domain is not compiled\n\n", sep = "")
  }

  if(!is.null(nodes <- x$nodes)) {
    for(name in names(nodes)) {
      cat(name, ":\n", sep = "")
      cat("  category: ", nodes[[name]]$category, "\n", sep = "")
      if(!is.null(nodes[[name]]$kind))
        cat("      kind: ", nodes[[name]]$kind, "\n", sep = "")
      if(!is.null(nodes[[name]]$subtype))
        cat("   subtype: ", nodes[[name]]$subtype, "\n", sep = "")
      if(!is.null(nodes[[name]]$states))
        cat("    states: ", "{", paste(nodes[[name]]$states, collapse = ", "),
            "}\n", sep = "")
      if(nodes[[name]]$experience.table)
        cat("  ", name, " has an experience table\n", sep = "")
      if(nodes[[name]]$fading.table)
        cat("  ", name, " has a fading table\n", sep = "")
      cat("\n")
    }
  }

  invisible(x)
}


