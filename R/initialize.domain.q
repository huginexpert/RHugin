initialize.domain <- function(domain)
{
  RHugin.check.args(domain, character(0), character(0), "initialize.domain")
  status <- .Call("RHugin_domain_initialize", domain$pointer,
                   PACKAGE = "RHugin")
  RHugin.handle.error(status)
  invisible(NULL)
}

