get.utility <- function(domain, node)
{
  RHugin.check.args(domain, node, character(0), "get.utility")

  node.ptr <- .Call("RHugin_domain_get_node_by_name", domain, node,
                     PACKAGE = "RHugin")

  states <- get.states(domain, node)
  states.idx <- 0:(length(states) - 1)

  utility <- .Call("RHugin_node_get_expected_utility", node.ptr, states.idx,
                    PACKAGE = "RHugin")

  names(utility) <- states
  utility
}


