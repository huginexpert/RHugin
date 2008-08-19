get.cases <- function(domain)
{
  nodes <- get.nodes(domain)
  data <- list()

  n <- .Call("RHugin_domain_get_number_of_cases", domain$pointer,
              PACKAGE = "RHugin")
  RHugin.handle.error()

  index.set <- as.integer(0:(n-1))

  for(node in nodes) {
    node.ptr <- .Call("RHugin_domain_get_node_by_name", domain$pointer, node,
                       PACKAGE = "RHugin")
    RHugin.handle.error()

    kind <- .Call("RHugin_node_get_kind", node.ptr, PACKAGE = "RHugin")
    RHugin.handle.error()

    if(kind  == "discrete") {
      data[[node]] <- .Call("RHugin_node_get_case_state", node.ptr,
                             as.integer(index.set), PACKAGE = "RHugin")
      RHugin.handle.error()
    }

    else {
      data[[node]] <- .Call("RHugin_node_get_case_value", node.ptr,
                             as.integer(index.set), PACKAGE = "RHugin")
      RHugin.handle.error()
    }
  }

  data[["Freq"]] <- .Call("RHugin_domain_get_case_count", domain$pointer,
                           as.integer(index.set), PACKAGE = "RHugin")
  RHugin.handle.error()

  as.data.frame(data, stringsAsFactors = TRUE)
}


