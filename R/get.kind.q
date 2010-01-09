get.kind <- function(domain, nodes)
{
  RHugin.check.args(domain, nodes, character(0), "get.kind")

  node.ptrs <- .Call("RHugin_domain_get_node_by_name", domain, nodes,
                      PACKAGE = "RHugin")

  .Call("RHugin_node_get_kind", node.ptrs, PACKAGE = "RHugin")
}


