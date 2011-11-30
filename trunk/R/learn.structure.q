learn.structure <- function(domain, alpha = 0.05, constraints = NULL)
{
  RHugin.check.args(domain, unlist(constraints), character(0), "learn.structure")

  .Call(RHugin_domain_set_significance_level, domain, alpha)

  if(!is.null(constraints)) {
    if(!is.null(directed <- constraints[["directed"]])) {
      if(!is.null(required <- directed[["required"]])) {
        for(i in 1:length(required)) {
          node.ptrs <- .Call(RHugin_domain_get_node_by_name, domain,
                             required[[i]])
         .Call(RHugin_node_set_edge_constraint, node.ptrs[1], node.ptrs[2],
              "forward_edge_required")
        }
      }
      if(!is.null(forbidden <- directed[["forbidden"]])) {
        for(i in 1:length(forbidden)) {
          node.ptrs <- .Call(RHugin_domain_get_node_by_name, domain,
                             forbidden[[i]])
          .Call(RHugin_node_set_edge_constraint, node.ptrs[1], node.ptrs[2],
               "forward_edge_forbidden")
        }
      }
    }
    if(!is.null(undirected <- constraints[["undirected"]])) {
      if(!is.null(required <- undirected[["required"]])) {
        for(i in 1:length(required)) {
          node.ptrs <- .Call(RHugin_domain_get_node_by_name, domain,
                             required[[i]])
          .Call(RHugin_node_set_edge_constraint, node.ptrs[1], node.ptrs[2],
               "edge_required")
        }
      }
      if(!is.null(forbidden <- undirected[["forbidden"]])) {
        for(i in 1:length(forbidden)) {
          node.ptrs <- .Call(RHugin_domain_get_node_by_name, domain,
                             forbidden[[i]])
          .Call(RHugin_node_set_edge_constraint, node.ptrs[1], node.ptrs[2],
               "edge_forbidden")
        }
      }
    }
  }

  .Call(RHugin_domain_learn_structure, domain)

  invisible()
}

