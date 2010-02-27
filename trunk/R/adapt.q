adapt <- function(domain)
{
  RHugin.check.args(domain, character(0), character(0), "adapt")

  .Call("RHugin_domain_adapt", domain, PACKAGE = "RHugin")

  invisible()
}


