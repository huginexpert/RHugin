propagate <- function(object, ...) 
{
  UseMethod("propagate")
}


propagate.RHuginDomain <- function(object, equilibrium = c("sum", "max"),
                                   mode = c("normal", "fast"), ...)
{
  RHugin.check.domain(object, "propagate")
  equilibrium <- match.arg(equilibrium)
  mode <- match.arg(mode)

  .Call(RHugin_domain_propagate, object, equilibrium, mode)

  invisible()
}


