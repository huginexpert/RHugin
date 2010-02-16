RHugin.control <- function(domain, concurrency = 1, grain.size = 10000)
{
  RHugin.check.args(domain, character(0), character(0), "RHugin.control")




  concurrency <- .Call("RHugin_domain_get_concurrency_level", domain,
                        PACKAGE = "RHugin")

  grain.size <- .Call("RHugin_domain_get_grain_size", domain,
                       PACKAGE = "RHugin")


  list(concurrency = concurrency, grain.size = grain.size)
}


