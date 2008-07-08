delete.node <- function(domain, node)
{
  RHugin.check.args(domain, node, character(0), "delete.node")

  node.ptr <- .Call("RHugin_domain_get_node_by_name", domain$pointer, node,
                     PACKAGE = "RHugin")
  RHugin.handle.error()
  status <- .Call("RHugin_node_delete", node.ptr, PACKAGE = "RHugin")
  RHugin.handle.error(status)

  invisible(NULL)
}


