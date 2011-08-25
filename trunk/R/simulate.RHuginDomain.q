simulate.RHuginDomain <- function(object, nsim = 1, seed = NULL, ...)
{
  RHugin.check.domain(object, "simulate")

  equilibrium.is.sum <- .Call(RHugin_domain_equilibrium_is, object, "sum")
  evidence.mode.is.normal <- .Call(RHugin_domain_evidence_mode_is, object,
                                  "normal")

  if(!equilibrium.is.sum)
    stop(deparse(substitute(object)), " is not in sum-equilibrium")

  if(!evidence.mode.is.normal)
    stop("the evidence in ", deparse(substitute(object)), " was not",
         " incorporated in normal mode")

  if(!is.null(seed))
    .Call(RHugin_domain_seed_random, object, abs(seed))

  nodes <- get.nodes(object)
  node.ptrs <- .Call(RHugin_domain_get_node_by_name, object, nodes)
  kinds <- .Call(RHugin_node_get_kind, node.ptrs)

  ans <- list()

  for(node in nodes)
    ans[[node]] <- numeric(nsim)

  for(i in 1:nsim) {
    .Call(RHugin_domain_simulate, object)

    for(node in nodes) {
      ans[[node]][i] <- switch(kinds[node],
        "discrete" = .Call(RHugin_node_get_sampled_state, node.ptrs[node]),
        "continuous" = .Call(RHugin_node_get_sampled_value, node.ptrs[node])
      )
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


