compile <- function(domain, save = FALSE)
{
  RHugin.check.args(domain, character(0), character(0), "compile")
  status <- .Call("RHugin_domain_compile", domain$pointer, PACKAGE = "RHugin")
  RHugin.handle.error(status)

  if(save) {
    status <- .Call("RHugin_domain_save_to_memory", domain$pointer,
                     PACKAGE = "RHugin")
    RHugin.handle.error(status)
  }

  invisible(NULL)
}


