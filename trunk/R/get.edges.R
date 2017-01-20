get.edges <- function(domain)
{
  node.ptrs <- nodePointersFromNames(domain, get.nodes(domain))
  children <- .Call(RHugin_node_get_children, node.ptrs)

  lapply(children, function(u) list(edges = names(u)))
}


