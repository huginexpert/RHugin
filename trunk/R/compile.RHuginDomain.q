compile.RHuginDomain <- function(object, save = FALSE, ...)
{
  RHugin.check.args(object, character(0), character(0), "compile")
  status <- .Call("RHugin_domain_compile", object, PACKAGE = "RHugin")
  RHugin.handle.error(status)

  if(save) {
    status <- .Call("RHugin_domain_save_to_memory", object,
                     PACKAGE = "RHugin")
    RHugin.handle.error(status)
  }

  invisible(NULL)
}


