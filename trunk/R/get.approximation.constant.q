get.approximation.constant <- function(domain)
{
  RHugin.check.args(domain, character(0), character(0),
                   "get.approximation.constant")
  const <- .Call("RHugin_domain_get_approximation_constant", domain,
                  PACKAGE = "RHugin")
  RHugin.handle.error()
  const
}


