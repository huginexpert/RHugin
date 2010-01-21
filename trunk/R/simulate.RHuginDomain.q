simulate.RHuginDomain <- function(object, nsim = 1, seed = NULL, ...)
{
  RHugin.check.args(object, character(0), character(0), "simulate.RHuginDomain")

  ds <- summary(object)$domain[c("equilibrium", "evidence.mode")]

  if(ds[["equilibrium"]] != "sum")
    stop("the domain ", deparse(substitute(object)),
         " is not in sum-equilibrium")
  if(!is.element("normal", ds[["evidence.mode"]]))
    stop("the evidence in ", deparse(substitute(object)), " was not",
         " incorporated in normal mode")

  if(!is.null(seed)) {
    .Call("RHugin_domain_seed_random", object, as.integer(abs(seed)),
           PACKAGE = "RHugin")
    RHugin.handle.error()
  }

  nodes <- get.nodes(object)
  node.ptrs <- .Call("RHugin_domain_get_node_by_name", object,
                      as.character(nodes), PACKAGE = "RHugin")
  kinds <- .Call("RHugin_node_get_kind", node.ptrs, PACKAGE = "RHugin")

  ans <- list()

  for(node in nodes)
    ans[[node]] <- numeric(nsim)

  for(i in 1:nsim) {
    status <- .Call("RHugin_domain_simulate", object, PACKAGE = "RHugin")
    RHugin.handle.error()

    for(node in nodes) {
      ans[[node]][i] <- switch(kinds[node],
        "discrete" = .Call("RHugin_node_get_sampled_state", node.ptrs[node],
                            PACKAGE = "RHugin"),
        "continuous" = .Call("RHugin_node_get_sampled_value", node.ptrs[node],
                              PACKAGE = "RHugin"))
      RHugin.handle.error()
    }
  }

  for(node in nodes) {
    if(kinds[node] == "discrete") {
      states <- get.states(object, node)
      ans[[node]] <- factor(states[ans[[node]] + 1], levels = states)
    }
  }

  as.data.frame(ans)
}


