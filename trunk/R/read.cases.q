read.cases <- function(domain, filename)
{
  RHugin.check.domain(domain, "read.cases")
  filename <- path.expand(filename)

  .Call("RHugin_domain_parse_cases", domain, filename, PACKAGE = "RHugin")

  invisible()
}


