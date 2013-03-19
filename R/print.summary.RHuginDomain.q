print.summary.RHuginDomain <- function(x, ...)
{
  if(!is.null(domain <- x$domain)) {
    cat("Hugin Domain:\n")

    if(!is.null(domain[["logfile"]]))
      cat("      Log File: ", domain[["logfile"]], "\n", sep = "")

    if(domain[["triangulated"]])
      cat("  Triangulated: the domain is triangulated\n", sep = "")
    else
      cat("  Triangulated: the domain is not triangulated\n", sep = "")

    if(domain[["compiled"]]) {
      cat("      Compiled: the domain is compiled\n", sep = "")

      if(domain[["compressed"]])
        cat("    Compressed: the domain is compressed\n", sep = "")
      else
        cat("    Compressed: the domain is not compressed\n", sep = "")

      if(domain[["evidence.propagated"]]) {
        cat("      Evidence: evidence has been propagated\n")
        cat("   Equilibrium: ", domain[["equilibrium"]], "\n", sep = "")
        cat(" Evidence mode: ", domain[["evidence.mode"]][1], "\n\n", sep = "")
      }

      else
        cat("      Evidence: no evidence has been propagated\n\n")

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
      cat("      Compiled: the domain is not compiled\n\n", sep = "")
  }

  if(!is.null(nodes <- x$nodes)) {
    cat("Nodes:\n")

    for(name in names(nodes)) {
      cat("  ", name, ":\n", sep = "")
      cat("    category: ", nodes[[name]]$category, "\n", sep = "")
      if(!is.null(nodes[[name]]$kind))
        cat("        kind: ", nodes[[name]]$kind, "\n", sep = "")
      if(!is.null(nodes[[name]]$subtype))
        cat("     subtype: ", nodes[[name]]$subtype, "\n", sep = "")
      if(!is.null(nodes[[name]]$states))
        cat("      states: ", "{", paste(nodes[[name]]$states, collapse = ", "),
            "}\n", sep = "")
      if(!is.null(nodes[[name]]$size))
        cat("        size: ", nodes[[name]]$size, "\n", sep = "")
      if(!is.null(nodes[[name]]$cgsize) && nodes[[name]]$cgsize > 0)
        cat("      cgsize: ", nodes[[name]]$cgsize, "\n", sep = "")
      cat("       model: ", ifelse(nodes[[name]]$model, "yes", "no"), "\n", sep = "")
      if(nodes[[name]]$model)
        cat("  model.size: ", nodes[[name]]$model.size, "\n", sep = "")
      tables <- c(nodes[[name]]$experience.table, nodes[[name]]$fading.table)
      tables <- c("experience", "fading")[tables]
      if(length(tables))
        cat("      tables: ", paste(tables, collapse = ", "), sep = "")
      cat("\n")
    }
  }

  if(!is.null(jt <- x$jt)) {
    for(i in 1:length(jt)) {
      if(length(jt) == 1)
        cat("Junction Tree:")
      else
        cat("Junction Tree ", i, ":", sep = "")

      cat("\n       size:", jt[[i]]$size)
      cat("\n     cgsize:", jt[[i]]$cgsize)
      cat("\n\n    clique membership:\n")
      cliques <- jt[[1]]$cliques
      for(j in 1:length(cliques)) {
        cat("      ", names(cliques)[j], ": {", sep = "")
        cat(paste(cliques[[j]], collapse = " "))
        cat("}\n")
      }
      cat("\n")
    }
  }

  invisible(x)
}


