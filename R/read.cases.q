read.cases <- function(domain, filename)
  invisible(.Call(RHugin_domain_parse_cases, domain, path.expand(filename)))


