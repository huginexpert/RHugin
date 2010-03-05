reset <- function(domain)
{
  RHugin.check.domain(domain, "reset")

  .Call("RHugin_domain_reset_inference_engine", domain, PACKAGE = "RHugin")

  invisible()
}


