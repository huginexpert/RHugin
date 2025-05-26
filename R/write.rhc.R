write.rhc <- function(class, filename, type = c("oobn", "hkb", "net"), password = NULL)
{
  filename <- path.expand(filename)
  type <- match.arg(type)

  switch(type,
    "hkb" = {
      .Call(RHugin_class_save_as_kb, class, filename, password)
    },

    "net" = {
      if(!is.null(password))
        warning(sQuote("password"), " not used in NET file")
      .Call(RHugin_class_save_as_net, class, filename)
    },

    "oobn" = {
      if(!is.null(password))
        warning(sQuote("password"), " not used in NET file")
      .Call(RHugin_class_save_as_net, class, filename)
    }
  )

  invisible()
}


