clone.node <- function(domain, node, new.name)
{
  RHugin.check.args(domain, node, new.name, "clone.node")

  node.ptr <- .Call("RHugin_domain_get_node_by_name", domain, node,
                     PACKAGE = "RHugin")
  RHugin.handle.error()
  new.node <- .Call("RHugin_node_clone", node.ptr, PACKAGE = "RHugin")
  RHugin.handle.error()
  status <- .Call("RHugin_node_set_name", new.node, new.name,
                   PACKAGE = "RHugin")
  RHugin.handle.error(status)

  invisible(NULL)
}

