adapt <- function(domain)
{
  RHugin.check.args(domain, character(0), character(0), "adapt")
  status <- .Call("RHugin_domain_adapt", domain, PACKAGE = "RHugin")
  RHugin.handle.error(status)
  invisible(NULL)
}


