uncompile <- function(domain)
{
  RHugin.check.args(domain, character(0), character(0), "uncompile")

  .Call("RHugin_domain_uncompile", domain, PACKAGE = "RHugin")

  invisible()
}


