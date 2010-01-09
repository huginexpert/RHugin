delete.node <- function(domain, node)
{
  RHugin.check.args(domain, node, character(0), "delete.node")

  node.ptrs <- .Call("RHugin_domain_get_node_by_name", domain, node,
                      PACKAGE = "RHugin")
  invisible(.Call("RHugin_node_delete", node.ptrs, PACKAGE = "RHugin"))
}


