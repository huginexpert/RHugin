RHugin.control <- function(domain, concurrency.level, grain.size)
{
  RHugin.check.args(domain, character(0), character(0), "RHugin.control")

  if(!missing(concurrency.level)) {
    status <- .Call("RHugin_domain_set_concurrency_level", domain,
                     as.integer(concurrency.level), PACKAGE = "RHugin")
    RHugin.handle.error(status)
  }

  if(!missing(grain.size)) {
    status <- .Call("RHugin_domain_set_grain_size", domain,
                     as.integer(grain.size), PACKAGE = "RHugin")
    RHugin.handle.error(status)
  }

  concurrency.level <- .Call("RHugin_domain_get_concurrency_level", domain,
                              PACKAGE = "RHugin")
  grain.size <- .Call("RHugin_domain_get_grain_size", domain,
                       PACKAGE = "RHugin")

  list(concurrency.level = concurrency.level, grain.size = grain.size)
}


