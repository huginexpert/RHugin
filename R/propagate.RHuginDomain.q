propagate.RHuginDomain <- function(object, equilibrium = c("sum", "max"),
                                   mode = c("normal", "fast"), ...)
{
  RHugin.check.args(object, character(0), character(0), "propagate")
  equilibrium <- match.arg(equilibrium)
  mode <- match.arg(mode)

  .Call("RHugin_domain_propagate", object, equilibrium, mode,
         PACKAGE = "RHugin")

  invisible()
}


