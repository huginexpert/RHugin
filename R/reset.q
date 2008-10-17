reset <- function(domain)
{
  RHugin.check.args(domain, character(0), character(0), "reset")
  status <- .Call("RHugin_domain_reset_inference_engine", domain,
                   PACKAGE = "RHugin")
  RHugin.handle.error(status)
  invisible(NULL)
}

