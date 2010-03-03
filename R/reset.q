reset <- function(domain)
{
  RHugin.check.args(domain, character(0), character(0), "reset")

  .Call("RHugin_domain_reset_inference_engine", domain, PACKAGE = "RHugin")

  invisible()
}


