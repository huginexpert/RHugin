read.cases <- function(domain, filename)
{
  RHugin.check.args(domain, character(0), character(0), "read.cases")

  .Call("RHugin_domain_parse_cases", domain, filename, PACKAGE = "RHugin")

  invisible()
}


