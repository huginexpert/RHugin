get.normalization.constant <- function(domain)
{
  RHugin.check.args(domain, character(0), character(0),
                   "get.normalization.constant")
  const <- .Call("RHugin_domain_get_normalization_constant", domain$pointer,
                  PACKAGE = "RHugin")
  RHugin.handle.error()
  const
}


