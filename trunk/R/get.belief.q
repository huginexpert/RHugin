get.belief <- function(domain, node)
{
  RHugin.check.args(domain, node, character(0), "get.belief")

  node.ptr <- .Call("RHugin_domain_get_node_by_name", domain,
                     as.character(node[1]), PACKAGE = "RHugin")
  kind <- .Call("RHugin_node_get_kind", node.ptr, PACKAGE = "RHugin")
  RHugin.handle.error()

  belief <- NULL

  if(kind == "discrete") {
    states <- get.states(domain, node)
    states.idx <- 0:(length(states) - 1)

    belief <- .Call("RHugin_node_get_belief", node.ptr,
                     as.integer(states.idx), PACKAGE = "RHugin")
    RHugin.handle.error()

    names(belief) <- states
  }

  if(kind == "continuous") {
    belief <- numeric(2)
    belief[1] <- .Call("RHugin_node_get_mean", node.ptr, PACKAGE = "RHugin")
    RHugin.handle.error()
    belief[2] <- .Call("RHugin_node_get_variance", node.ptr, PACKAGE = "RHugin")
    RHugin.handle.error()
    names(belief) <- c("(Mean)", "(Variance)")
  }

  belief
}


