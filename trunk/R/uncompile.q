uncompile <- function(domain)
{
  RHugin.check.args(domain, character(0), character(0), "uncompile")
  status <- .Call("RHugin_domain_uncompile", domain, PACKAGE = "RHugin")
  RHugin.handle.error(status)
  invisible(NULL)
}


