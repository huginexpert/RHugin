set.cases <- function(domain, data, counts)
{
  RHugin.check.args(domain, character(0), character(0), "set.cases")

  data.names <- names(data)
  n <- nrow(data)

  data.class <- sapply(data, class)
  factors <- names(data.class)[data.class == "factor"]
  for(var in factors)
    data[[var]] <- as.character(data[[var]])
  data.class <- sapply(data, class)

  nodes <- get.nodes(domain)
  NA.nodes <- setdiff(nodes, data.names)
  nodes <- intersect(nodes, data.names)

  status <- .Call("RHugin_domain_set_number_of_cases", domain$pointer,
                   as.integer(n), PACKAGE = "RHugin")
  RHugin.handle.error(status)

  index.set <- as.integer(0:(n-1))

  for(node in nodes) {
    node.ptr <- .Call("RHugin_domain_get_node_by_name", domain$pointer, node,
                       PACKAGE = "RHugin")
    RHugin.handle.error()

    if(data.class[node] == "character") {
      status <- .Call("RHugin_node_set_case_state", node.ptr,
                       as.integer(index.set), data[[node]], PACKAGE = "RHugin")
      RHugin.handle.error(status)
    }

    else {
      status <- .Call("RHugin_node_set_case_value", node.ptr,
                       as.integer(index.set), as.numeric(data[[node]]),
                       PACKAGE = "RHugin")
      RHugin.handle.error(status)
    }
  }

  for(node in NA.nodes) {
    node.ptr <- .Call("RHugin_domain_get_node_by_name", domain$pointer, node,
                       PACKAGE = "RHugin")
    RHugin.handle.error()

    status <- .Call("RHugin_node_unset_case", node.ptr, as.integer(index.set),
                     PACKAGE = "RHugin")
    RHugin.handle.error(status)
  }

  if(!missing(counts)) {
    if(is.character(counts) && !is.null(data[[counts]]))
      counts <- data[[counts]]

    status <- .Call("RHugin_domain_set_case_count", domain$pointer,
                     as.integer(index.set), as.numeric(counts),
                     PACKAGE = "RHugin")
    RHugin.handle.error(status)
  }

  invisible(NULL)
}


