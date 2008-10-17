get.cases <- function(domain)
{
  nodes <- get.nodes(domain)
  data <- list()

  n <- .Call("RHugin_domain_get_number_of_cases", domain,
              PACKAGE = "RHugin")
  RHugin.handle.error()

  if(n < 1)
    return(invisible(NULL))

  index.set <- as.integer(0:(n-1))

  for(node in nodes) {
    node.ptr <- .Call("RHugin_domain_get_node_by_name", domain, node,
                       PACKAGE = "RHugin")
    RHugin.handle.error()

    kind <- .Call("RHugin_node_get_kind", node.ptr, PACKAGE = "RHugin")
    RHugin.handle.error()

    if(kind  == "discrete") {
      state.indices <- .Call("RHugin_node_get_case_state", node.ptr,
                              as.integer(index.set), PACKAGE = "RHugin")
      RHugin.handle.error()

      data[[node]] <- get.states(domain, node)[state.indices + 1]
    }

    else {
      data[[node]] <- .Call("RHugin_node_get_case_value", node.ptr,
                             as.integer(index.set), PACKAGE = "RHugin")
      RHugin.handle.error()
    }
  }

  data[["Freq"]] <- .Call("RHugin_domain_get_case_count", domain,
                           as.integer(index.set), PACKAGE = "RHugin")
  RHugin.handle.error()

  as.data.frame(data, stringsAsFactors = TRUE)
}


