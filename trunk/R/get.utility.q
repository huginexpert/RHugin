get.utility <- function(domain, node)
{
  RHugin.check.args(domain, node, character(0), "get.utility")

  node.ptr <- .Call("RHugin_domain_get_node_by_name", domain,
                     as.character(node[1]), PACKAGE = "RHugin")
  RHugin.handle.error()

  states <- get.states(domain, node)
  states.idx <- 0:(length(states) - 1)

  utility <- .Call("RHugin_node_get_expected_utility", node.ptr,
                   as.integer(states.idx), PACKAGE = "RHugin")
  RHugin.handle.error()

  names(utility) <- states

  utility
}


