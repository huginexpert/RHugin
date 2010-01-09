get.edges <- function(domain)
{
  RHugin.check.args(domain, character(0), character(0), "get.edges")

  node.ptrs <- .Call("RHugin_domain_get_node_by_name", domain,
                      get.nodes(domain), PACKAGE = "RHugin")

  children <- .Call("RHugin_node_get_children", node.ptrs, PACKAGE = "RHugin")

  lapply(children, function(u) list(edges = names(u)))
}


