propagate.RHuginDomain <- function(object, equilibrium = c("sum", "max"),
                                   mode = c("normal", "fast"), ...)
{
  RHugin.check.args(object, character(0), character(0), "propagate")
  equilibrium <- match.arg(equilibrium)
  mode <- match.arg(mode)
  status <- .Call("RHugin_domain_propagate", object, as.character(equilibrium),
                   as.character(mode), PACKAGE = "RHugin")
  RHugin.handle.error(status)

  invisible(NULL)
}


