write.rhd <- function(domain, filename, type = c("hkb", "net"), password = NULL)
{
  RHugin.check.args(domain, character(0), character(0), "write.hkb")
  type <- match.arg(type)

  status <- switch(type,
    "hkb" = {
      .Call("RHugin_domain_save_as_kb", domain, filename,
             password, PACKAGE = "RHugin")
    },

    "net" = {
      if(!is.null(password))
        warning(sQuote("password"), " not used in NET file")
      .Call("RHugin_domain_save_as_net", domain, filename,
             PACKAGE = "RHugin")
    }
  )

  RHugin.handle.error(status)
  invisible(NULL)
}


