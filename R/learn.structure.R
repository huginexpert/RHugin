learn.structure <- function(domain, alpha = 0.05, constraints = NULL)
{
  .Call(RHugin_domain_set_significance_level, domain, alpha)

  if(!is.null(constraints)) {
    if(!is.null(directed <- constraints[["directed"]])) {
      if(!is.null(required <- directed[["required"]])) {
        for(i in 1:length(required)) {
          node.ptrs <- nodePointersFromNames(domain, required[[i]])
         .Call(RHugin_node_set_edge_constraint, node.ptrs[1], node.ptrs[2],
              "forward_edge_required")
        }
      }
      if(!is.null(forbidden <- directed[["forbidden"]])) {
        for(i in 1:length(forbidden)) {
          node.ptrs <- nodePointersFromNames(domain, forbidden[[i]])
          .Call(RHugin_node_set_edge_constraint, node.ptrs[1], node.ptrs[2],
               "forward_edge_forbidden")
        }
      }
    }
    if(!is.null(undirected <- constraints[["undirected"]])) {
      if(!is.null(required <- undirected[["required"]])) {
        for(i in 1:length(required)) {
          node.ptrs <- nodePointersFromNames(domain, required[[i]])
          .Call(RHugin_node_set_edge_constraint, node.ptrs[1], node.ptrs[2],
               "edge_required")
        }
      }
      if(!is.null(forbidden <- undirected[["forbidden"]])) {
        for(i in 1:length(forbidden)) {
          node.ptrs <- nodePointersFromNames(domain, forbidden[[i]])
          .Call(RHugin_node_set_edge_constraint, node.ptrs[1], node.ptrs[2],
               "edge_forbidden")
        }
      }
    }
  }

  .Call(RHugin_domain_learn_structure, domain)

  invisible()
}


