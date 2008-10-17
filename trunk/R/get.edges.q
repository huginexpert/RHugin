get.edges <- function(domain)
{
  RHugin.check.args(domain, character(0), character(0), "get.edges")

  nodes <- get.nodes(domain)
  edges <- list()

  for(node in nodes) {
    node.ptr <- .Call("RHugin_domain_get_node_by_name", domain, node,
                       PACKAGE = "RHugin")
    RHugin.handle.error()

    children <- .Call("RHugin_node_get_children", node.ptr, PACKAGE = "RHugin")
    RHugin.handle.error()

    if(length(children))
      edges[[node]] <- list(edges = names(children))
    else
      edges[[node]] <- list(edges = character(0))
  }

  edges
}


