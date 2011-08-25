compress <- function(domain)
{
  RHugin.check.domain(domain, "compress")

  .Call(RHugin_domain_compress, domain)
}


