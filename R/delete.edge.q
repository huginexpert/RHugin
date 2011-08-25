delete.edge <- function(domain, node, parent)
{
  RHugin.check.args(domain, c(node, parent), character(0), "delete.edge")

  node.ptr <- .Call(RHugin_domain_get_node_by_name, domain, node)
  parent.ptr <- .Call(RHugin_domain_get_node_by_name, domain, parent)
  .Call(RHugin_node_remove_parent, node.ptr, parent.ptr)

  invisible()
}


