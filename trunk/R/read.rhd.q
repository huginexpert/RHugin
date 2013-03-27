read.rhd <- function(filename, type = c("auto", "hkb", "net"), password = NULL,
                     generate.tables)
{
  filename <- path.expand(filename)

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
    "hkb" = {
      .Call(RHugin_kb_load_domain, filename, password)
    },

    "net" = {
      if(!is.null(password))
        warning(sQuote("password"), " not used in NET file")
      .Call(RHugin_net_parse_domain, filename)
    }
  )

  if(is.null(domain))
    stop("failed to read file")
  oldClass(domain) <- "RHuginDomain"

  nodes <- get.nodes(domain)
  index <- (nodes %in% RHUGIN.RESERVED)

  if(any(index))
    stop(dQuote(nodes[index][1]), " is a reserved word in RHugin and cannot be",
         " used as the name of a node")

  if(!missing(generate.tables)) {
    warning("RHugin 7.7 introduced support for models: ",
            sQuote("generate.tables"), " is depricated")
  }

  domain
}


