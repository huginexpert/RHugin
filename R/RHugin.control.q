RHugin.control <- function(domain, concurrency.level = 1, grain.size = 10000)
{
  RHugin.check.args(domain, character(0), character(0), "RHugin.control")

  status <- .Call("RHugin_domain_get_concurrency_level", domain,
                   as.ineteger(concurrency.level), PACKAGE = "RHugin")
  RHugin.handle.error(status)
  status <- .Call("RHugin_domain_set_grain_size", domain,
                   as.integer(grain.size), PACKAGE = "RHugin")
  RHugin.handle.error(status)

  concurrency.level <- .Call("RHugin_domain_get_concurrency_level", domain,
                              PACKAGE = "RHugin")
  grain.size <- .Call("RHugin_domain_get_grain_size", domain,
                       PACKAGE = "RHugin")

  list(concurrency.level = concurrency.level, grain.size = grain.size)
}


