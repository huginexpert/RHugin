initialize.domain <- function(domain)
{
  RHugin.check.args(domain, character(0), character(0), "initialize.domain")
  .Call("RHugin_domain_initialize", domain, PACKAGE = "RHugin")
  invisible()
}

