compress <- function(domain)
{
  RHugin.check.args(domain, character(0), character(0), "compress")
  factor <- .Call("RHugin_domain_compress", domain, PACKAGE = "RHugin")
  RHugin.handle.error()
  factor
}


