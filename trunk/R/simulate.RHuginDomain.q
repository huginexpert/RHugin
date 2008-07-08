simulate.RHuginDomain <- function(object, nsim = 1, seed = NULL, ...)
{
  RHugin.check.args(object, character(0), character(0), "simulate.RHuginDomain")

  if(!is.null(seed)) {
    .Call("RHugin_domain_seed_random", object$pointer, as.integer(abs(seed)),
           PACKAGE = "RHugin")
    RHugin.handle.error()
  }

  nodes <- get.nodes(object)
  node.list <- list()
  ans <- list()

  for(node in nodes) {
    node.list[[node]] <- .Call("RHugin_domain_get_node_by_name", object$pointer,
                                node, PACKAGE = "RHugin")
    RHugin.handle.error()
    ans[[node]] <- numeric(nsim)
  }

  node.index <- 1:length(node.list)

  for(i in 1:nsim) {
    status <- .Call("RHugin_domain_simulate", object$pointer,
                     PACKAGE = "RHugin")
    RHugin.handle.error()

    for(j in node.index) {
      kind <- .Call("RHugin_node_get_kind", node.list[[j]], PACKAGE = "RHugin")
      RHugin.handle.error()

      if(kind == "discrete")
        ans[[j]][i] <- .Call("RHugin_node_get_sampled_state", node.list[[j]],
                              PACKAGE = "RHugin")
      else
        ans[[j]][i] <- .Call("RHugin_node_get_sampled_value", node.list[[j]],
                              PACKAGE = "RHugin")

      RHugin.handle.error()
    }
  }

  for(j in node.index) {
    kind <- .Call("RHugin_node_get_kind", node.list[[j]], PACKAGE = "RHugin")
    RHugin.handle.error()

    if(kind == "discrete")
      ans[[j]] <- get.states(object, nodes[j])[ans[[j]] + 1]
  }

  as.data.frame(ans, stringsAsFactors = FALSE)
}


