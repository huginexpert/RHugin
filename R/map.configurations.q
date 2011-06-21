map.configurations <- function(domain, nodes, pmin)
{
  RHugin.check.args(domain, nodes, character(0), "map.configurations")

  if(pmin <= 0.0 || pmin > 1.0)
    stop("pmin is not between 0 and 1")

  n.nodes <- length(nodes)
  node.ptrs <- .Call("RHugin_domain_get_node_by_name", domain, nodes,
                      PACKAGE = "RHugin")

  .Call("RHugin_domain_find_map_configurations", domain, node.ptrs, pmin,
         PACKAGE = "RHugin")

  n.confs <- .Call("RHugin_domain_get_number_of_map_configurations",
                    domain, PACKAGE = "RHugin")

  confs <- matrix(-1, n.confs, n.nodes)
  probs <- numeric(n.confs)

  for(i in 1:n.confs) {
    confs[i,] <- .Call("RHugin_domain_get_map_configuration", domain, i-1,
                        n.nodes, PACKAGE = "RHugin")
    probs[i] <- .Call("RHugin_domain_get_probability_of_map_configuration",
                       domain, i-1, PACKAGE = "RHugin")
  }

  confs <- confs + 1

  ans <- list()

  for(j in 1:n.nodes) {
    states <- get.states(domain, nodes[j])
    ans[[nodes[j]]] <- states[confs[,j]]
  }

  ans[["Prob"]] <- probs
  
  as.data.frame(ans)
}


