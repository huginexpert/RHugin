write.rhd <- function(domain, filename, type = c("hkb", "net"), password = NULL)
{
  RHugin.check.domain(domain, "write.hkb")
  filename <- path.expand(filename)
  type <- match.arg(type)

  switch(type,
    "hkb" = {
      .Call(RHugin_domain_save_as_kb, domain, filename, password)
    },

    "net" = {
      if(!is.null(password))
        warning(sQuote("password"), " not used in NET file")
      .Call(RHugin_domain_save_as_net, domain, filename)
    }
  )

  invisible()
}


