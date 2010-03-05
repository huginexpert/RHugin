uncompile <- function(domain)
{
  RHugin.check.domain(domain, "uncompile")

  .Call("RHugin_domain_uncompile", domain, PACKAGE = "RHugin")

  invisible()
}


