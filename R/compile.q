compile <- function(domain, save = FALSE)
{
  RHugin.check.args(domain, character(0), character(0), "compile")
  status <- .Call("RHugin_domain_compile", domain, PACKAGE = "RHugin")
  RHugin.handle.error(status)

  if(save) {
    status <- .Call("RHugin_domain_save_to_memory", domain,
                     PACKAGE = "RHugin")
    RHugin.handle.error(status)
  }

  invisible(NULL)
}


