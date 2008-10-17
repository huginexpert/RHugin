get.belief <- function(domain, node, states = NULL)
{
  RHugin.check.args(domain, node, character(0), "get.belief")

  if(is.null(states)) {
    states <- get.states(domain, node)
    states.idx <- 0:(length(states) - 1)
  }
  else {
    states.idx <- match(as.character(states), get.states(domain, node),
                        nomatch = NA)
    if(any(is.na(states.idx)))
      stop("nonexistent state specified in ", sQuote("states"))
    n.states <- length(states)
    if(n.states < 1)
      return(numeric(0))
    states.idx <- states.idx - 1
  }

  node.ptr <- .Call("RHugin_domain_get_node_by_name", domain, node,
                     PACKAGE = "RHugin")
  RHugin.handle.error()

  belief <- .Call("RHugin_node_get_belief", node.ptr,
                   as.integer(states.idx), PACKAGE = "RHugin")
  RHugin.handle.error()

  names(belief) <- states
  belief
}


