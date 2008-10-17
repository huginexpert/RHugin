hugin.domain <- function()
{
  domain <- .Call("RHugin_new_domain", PACKAGE = "RHugin")
  oldClass(domain) <- "RHuginDomain"
  RHugin.handle.error()
  domain
}


