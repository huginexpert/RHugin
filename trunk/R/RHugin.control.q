RHugin.control <- function(domain, concurrency.level, grain.size)
{
  RHugin.check.domain(domain, "RHugin.control")

  if(!missing(concurrency.level))
    .Call("RHugin_domain_set_concurrency_level", domain, concurrency.level,
           PACKAGE = "RHugin")

  if(!missing(grain.size))
    .Call("RHugin_domain_set_grain_size", domain, grain.size,
           PACKAGE = "RHugin")

  concurrency.level <- .Call("RHugin_domain_get_concurrency_level", domain,
                              PACKAGE = "RHugin")

  grain.size <- .Call("RHugin_domain_get_grain_size", domain,
                       PACKAGE = "RHugin")

  list(concurrency.level = concurrency.level, grain.size = grain.size)
}


