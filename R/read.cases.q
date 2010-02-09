read.cases <- function(domain, filename)
{
  RHugin.check.args(domain, character(0), character(0), "read.cases")
  status <- .Call("RHugin_domain_parse_cases", domain, as.character(filename),
                   PACKAGE = "RHugin")
  RHugin.handle.error(status)
  invisible(NULL)
}


