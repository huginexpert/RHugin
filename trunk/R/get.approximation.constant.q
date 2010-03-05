get.approximation.constant <- function(domain)
{
  RHugin.check.domain(domain, "get.approximation.constant")

  .Call("RHugin_domain_get_approximation_constant", domain, PACKAGE = "RHugin")
}


