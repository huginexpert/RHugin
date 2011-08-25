delete.node <- function(domain, node)
{
  node <- unique(node)
  RHugin.check.args(domain, node, character(0), "delete.node")

  node.ptrs <- .Call(RHugin_domain_get_node_by_name, domain, node)
  .Call(RHugin_node_delete, node.ptrs)

  invisible()
}


