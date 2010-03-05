get.conflict <- function(domain)
{
  RHugin.check.domain(domain, "get.conflict")

  .Call("RHugin_domain_get_conflict", domain, PACKAGE = "RHugin")
}


