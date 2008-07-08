propagate <- function(domain, equilibrium = c("sum", "max"),
                      mode = c("normal", "fast"))
{
  RHugin.check.args(domain, character(0), character(0), "propagate")
  equilibrium <- match.arg(equilibrium)
  mode <- match.arg(mode)

  status <- .Call("RHugin_domain_propagate", domain$pointer, equilibrium, mode,
                   PACKAGE = "RHugin")
  RHugin.handle.error(status)

  invisible(NULL)
}

