print.summary.RHuginDomain <- function(x, ...)
{
  for(name in names(x)) {
    cat(name, ":\n", sep = "")
    cat("  category: ", x[[name]]$category, "\n", sep = "")
    cat("      kind: ", x[[name]]$kind, "\n", sep = "")
    cat("   subtype: ", x[[name]]$subtype, "\n\n", sep = "")
  }

  invisible(x)
}


