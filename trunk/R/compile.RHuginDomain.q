compile.RHuginDomain <- function(object, save = FALSE, approximate = NULL, ...)
{
  RHugin.check.domain(object, "compile")

  .Call("RHugin_domain_compile", object, PACKAGE = "RHugin")

  if(!is.null(approximate)) {
    factor <- .Call("RHugin_domain_approximate", object, approximate,
                     PACKAGE = "RHugin")
    factor <- compress(object)
  }

  if(save)
    .Call("RHugin_domain_save_to_memory", object, PACKAGE = "RHugin")

  invisible()
}


