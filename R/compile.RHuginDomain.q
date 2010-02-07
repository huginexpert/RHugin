compile.RHuginDomain <- function(object, save = FALSE, approximate = NULL, ...)
{
  RHugin.check.args(object, character(0), character(0), "compile")

  status <- .Call("RHugin_domain_compile", object, PACKAGE = "RHugin")
  RHugin.handle.error(status)

  if(!is.null(approximate)) {
    factor <- .Call("RHugin_domain_approximate", object, as.double(approximate),
                     PACKAGE = "RHugin")
    RHugin.handle.error()
  }

  if(save) {
    status <- .Call("RHugin_domain_save_to_memory", object,
                     PACKAGE = "RHugin")
    RHugin.handle.error(status)
  }

  invisible(NULL)
}


