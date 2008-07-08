write.hkb <- function(domain, filename, password = NULL)
{
  RHugin.check.args(domain, character(0), character(0), "write.hkb")
  status <- .Call("RHugin_domain_save_as_kb", domain$pointer, filename,
                   password, PACKAGE = "RHugin")
  RHugin.handle.error(status)
  invisible(NULL)
}


