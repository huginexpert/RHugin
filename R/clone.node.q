clone.node <- function(domain, node, name)
{
  RHugin.check.args(domain, node, name, "clone.node")

  node.ptr <- .Call(RHugin_domain_get_node_by_name, domain, node)
  clone.ptr <- .Call(RHugin_node_clone, node.ptr)
  .Call(RHugin_node_set_name, clone.ptr, name)

  invisible()
}


