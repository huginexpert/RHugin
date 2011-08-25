compile.RHuginDomain <- function(object, save = FALSE, approximate = NULL, ...)
{
  RHugin.check.domain(object, "compile")

  .Call(RHugin_domain_compile, object)

  if(!is.null(approximate)) {
    factor <- .Call(RHugin_domain_approximate, object, approximate)
    factor <- compress(object)
  }

  if(save)
    .Call(RHugin_domain_save_to_memory, object)

  invisible()
}


