get.utility <- function(domain, node)
{
  if(missing(node)) {
    utility <- .Call(RHugin_domain_get_expected_utility, domain)
  }

  else {
    node.ptr <- nodePointersFromNames(domain, node[1])

    states <- get.states(domain, node)
    states.idx <- 0:(length(states) - 1)

    utility <- .Call(RHugin_node_get_expected_utility, node.ptr, states.idx)

    names(utility) <- states
  }

  utility
}


