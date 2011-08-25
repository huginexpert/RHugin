adapt <- function(domain)
{
  RHugin.check.domain(domain, "adapt")

  .Call(RHugin_domain_adapt, domain)

  invisible()
}


