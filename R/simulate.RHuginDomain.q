simulate.RHuginDomain <- function(object, nsim = 1, seed = NULL, ...)
{
  RHugin.check.args(object, character(0), character(0), "simulate.RHuginDomain")

  if(!is.null(seed)) {
    .Call("RHugin_domain_seed_random", object, as.integer(abs(seed)),
           PACKAGE = "RHugin")
    RHugin.handle.error()
  }

  nodes <- get.nodes(object)
  node.summary <- summary(object)
  node.list <- list()
  ans <- list()

  for(node in nodes) {
    node.list[[node]] <- .Call("RHugin_domain_get_node_by_name", object,
                                node, PACKAGE = "RHugin")
    RHugin.handle.error()
    ans[[node]] <- numeric(nsim)
  }

  for(i in 1:nsim) {
    status <- .Call("RHugin_domain_simulate", object, PACKAGE = "RHugin")
    RHugin.handle.error()

    for(node in nodes) {
      ans[[node]][i] <- switch(node.summary[[node]]$kind,
        "discrete" = .Call("RHugin_node_get_sampled_state", node.list[[node]],
                            PACKAGE = "RHugin"),
        "continuous" = .Call("RHugin_node_get_sampled_value", node.list[[node]],
                              PACKAGE = "RHugin"))
      RHugin.handle.error()
    }
  }

  for(node in nodes) {
    if(node.summary[[node]]$kind == "discrete")
      ans[[node]] <- get.states(object, node)[ans[[node]] + 1]
  }

  as.data.frame(ans, stringsAsFactors = TRUE)
}


