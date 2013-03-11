set.logfile <- function(domain, filename)
{
  RHugin.check.domain(domain, "set.logfile")

  if(!is.null(filename))
    filename <- path.expand(filename)

  .Call(RHugin_domain_set_log_file, domain, filename)

  invisible()
}


