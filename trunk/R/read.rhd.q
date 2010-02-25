read.rhd <- function(filename, type = c("auto", "hkb", "net"), password = NULL,
                     generate.tables = TRUE)
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
    "hkb" = {
      .Call("RHugin_kb_load_domain", as.character(filename),
             as.character(password), PACKAGE = "RHugin")
    },

    "net" = {
      if(!is.null(password))
        warning(sQuote("password"), " not used in NET file")
      .Call("RHugin_net_parse_domain", as.character(filename),
             PACKAGE = "RHugin")
    }
  )

  RHugin.handle.error()
  if(is.null(domain))
    stop("failed to read file")
  oldClass(domain) <- "RHuginDomain"

  nodes <- get.nodes(domain)
  reserved <- c("Freq", "Value", "Cost", "Utility", "Counts", "Lambda")
  index <- nodes %in% reserved

  if(any(index))
    stop(dQuote(nodes[index][1]), " is a reserved word in RHugin and cannot be",
         " used as the name of a node")

  if(generate.tables) {
    node.ptrs <- .Call("RHugin_domain_get_node_by_name", domain, nodes,
                        PACKAGE = "RHugin")
    model.ptrs <- .Call("RHugin_node_get_model", node.ptrs, PACKAGE = "RHugin")
    model.ptrs <- model.ptrs[sapply(model.ptrs, function(u) !is.null(u))]
    models <- names(model.ptrs)

    .Call("RHugin_node_generate_table", node.ptrs[models], PACKAGE = "RHugin")
    .Call("RHugin_model_delete", model.ptrs, PACKAGE = "RHugin")
  }

  domain
}


