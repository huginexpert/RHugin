clone.domain <- function(domain)
{
  RHugin.check.domain(domain, "clone.domain")
  clone <- .Call(RHugin_domain_clone, domain)
  oldClass(clone) <- "RHuginDomain"
  clone
}


