initialize.domain <- function(domain)
{
  RHugin.check.domain(domain, "initialize.domain")

  .Call(RHugin_domain_initialize, domain)

  invisible()
}


