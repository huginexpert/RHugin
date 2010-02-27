get.cases <- function(domain)
{
  RHugin.check.args(domain, character(0), character(0), "get.cases")

  nodes <- get.nodes(domain)
  data <- list()
  n.cases <- .Call("RHugin_domain_get_number_of_cases", domain,
                    PACKAGE = "RHugin")

  if(n.cases < 1)
    return(invisible())

  indices <- as.integer(0:(n.cases - 1))

  node.ptrs <- .Call("RHugin_domain_get_node_by_name", domain, nodes,
                      PACKAGE = "RHugin")
  kinds <- .Call("RHugin_node_get_kind", node.ptrs, PACKAGE = "RHugin")
  subtypes <- .Call("RHugin_node_get_subtype", node.ptrs, PACKAGE = "RHugin")

  for(node in nodes) {
    if(kinds[node]  == "discrete") {
      state.indices <- .Call("RHugin_node_get_case_state", node.ptrs[node],
                              indices, PACKAGE = "RHugin")

      states <- get.states(domain, node)

      if(is.element(subtypes[node], c("labeled", "interval")))
        data[[node]] <- factor(states[state.indices + 1], levels = states)
      else
        data[[node]] <- states[state.indices + 1]
    }

    else
      data[[node]] <- .Call("RHugin_node_get_case_value", node.ptrs[node],
                             indices, PACKAGE = "RHugin")
  }

  data[["Freq"]] <- .Call("RHugin_domain_get_case_count", domain, indices,
                           PACKAGE = "RHugin")

  as.data.frame(data)
}


