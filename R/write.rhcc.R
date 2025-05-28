write.rhcc <- function(cc, filename, type = c("hkb", "net"), password = NULL)
{
  filename <- path.expand(filename)
  type <- match.arg(type)

  switch(type,
    "hkb" = {
      .Call(RHugin_cc_save_as_kb, cc, filename, password)
    },

    "net" = {
      if(!is.null(password))
        warning(sQuote("password"), " not used in NET file")
      .Call(RHugin_cc_save_as_net, cc, filename)
    }
  )

  invisible()
}
