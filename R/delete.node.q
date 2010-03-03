delete.node <- function(domain, nodes)
{
  nodes <- unique(nodes)
  RHugin.check.args(domain, nodes, character(0), "delete.node")

  node.ptrs <- .Call("RHugin_domain_get_node_by_name", domain, nodes,
                      PACKAGE = "RHugin")
  .Call("RHugin_node_delete", node.ptrs, PACKAGE = "RHugin")

  invisible()
}


