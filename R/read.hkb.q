read.hkb <- function(filename, password = NULL)
{
  domain <- list(pointer = .Call("RHugin_kb_load_domain", filename, password,
                                  PACKAGE = "RHugin"))
  RHugin.handle.error()
  oldClass(domain) <- "RHuginDomain"
  domain
}


