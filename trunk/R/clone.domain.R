clone.domain <- function(domain)
{
  clone <- .Call(RHugin_domain_clone, domain)
  oldClass(clone) <- "RHuginDomain"
  clone
}


