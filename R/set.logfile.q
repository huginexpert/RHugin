set.logfile <- function(domain, filename)
{
  if(!is.null(filename))
    filename <- path.expand(filename)

  .Call(RHugin_domain_set_log_file, domain, filename)

  invisible()
}


