clone.node <- function(domain, node, name)
{
  RHugin.check.args(domain, node, name, "clone.node")

  node.ptr <- .Call("RHugin_domain_get_node_by_name", domain, node,
                     PACKAGE = "RHugin")

  clone.ptr <- .Call("RHugin_node_clone", node.ptr, PACKAGE = "RHugin")

  .Call("RHugin_node_set_name", clone.ptr, name, PACKAGE = "RHugin")

  invisible()
}


