get.belief <- function(domain, node)
{
  RHugin.check.args(domain, node, character(0), "get.belief")

  states <- get.states(domain, node)
  n.states <- length(states)

  node.ptr <- .Call("RHugin_domain_get_node_by_name", domain$pointer, node,
                     PACKAGE = "RHugin")
  RHugin.handle.error()

  belief <- .Call("RHugin_node_get_belief", node.ptr,
                   as.integer(0:(length(states) - 1)), PACKAGE = "RHugin")
  RHugin.handle.error()

  names(belief) <- states
  belief
}


