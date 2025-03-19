hugin.domain.class <- function(class)
{
  domain <- .Call(RHugin_class_create_domain, class)
  oldClass(domain) <- "RHuginDomain"
  domain
}


 