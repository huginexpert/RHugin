get.conflict <- function(domain)
{
  RHugin.check.args(domain, character(0), character(0), "get.conflict")
  .Call("RHugin_domain_get_conflict", domain, PACKAGE = "RHugin")
}


