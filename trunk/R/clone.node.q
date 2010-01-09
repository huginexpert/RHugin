clone.node <- function(domain, node, name)
{
  RHugin.check.args(domain, node, name, "clone.node")

  node.ptr <- .Call("RHugin_domain_get_node_by_name", domain, node,
                     PACKAGE = "RHugin")

  new.node <- .Call("RHugin_node_clone", node.ptr, PACKAGE = "RHugin")

  status <- .Call("RHugin_node_set_name", new.node, name, PACKAGE = "RHugin")

  invisible(status)
}


