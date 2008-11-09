read.rhd <- function(filename, type = c("auto", "hkb", "net"), password = NULL)
{
  type <- match.arg(type)
  if(type == "auto") {
    type <- c("hkb", "net")
    extension <- strsplit(filename[1], split = ".", fixed = TRUE)[[1]]
    extension <- casefold(extension[length(extension)])
    type <- type[match(extension, type)]
    if(!length(type))
      stop("unable to determine file type; the ", sQuote("type"),
           " argument may be used to specify the file type")
  }

  domain <- switch(type,
    "hkb" = .Call("RHugin_kb_load_domain", filename, password,
                   PACKAGE = "RHugin"),
    "net" = {
      if(!is.null(password))
        warning(sQuote("password"), " not used in NET file")
      .Call("RHugin_net_parse_domain", filename, PACKAGE = "RHugin")
    }
  )

  RHugin.handle.error()
  if(is.null(domain))
    stop("failed to read file")

  oldClass(domain) <- "RHuginDomain"
  domain
}


