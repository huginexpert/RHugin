RHugin.control <- function(domain, concurrency.level, grain.size)
{
  if(!missing(concurrency.level))
    .Call(RHugin_domain_set_concurrency_level, domain, concurrency.level)

  if(!missing(grain.size))
    .Call(RHugin_domain_set_grain_size, domain, grain.size)

  concurrency.level <- .Call(RHugin_domain_get_concurrency_level, domain)
  grain.size <- .Call(RHugin_domain_get_grain_size, domain)

  list(concurrency.level = concurrency.level, grain.size = grain.size)
}


