reverse.edge <- function(domain, node1, node2)
{
  RHugin.check.args(domain, c(node1, node2), character(0), "reverse.edge")

  node1.ptr <- .Call("RHugin_domain_get_node_by_name", domain,
                      as.character(node1), PACKAGE = "RHugin")
  RHugin.handle.error()
  node2.ptr <- .Call("RHugin_domain_get_node_by_name", domain,
                      as.character(node2), PACKAGE = "RHugin")
  RHugin.handle.error()
  status <- .Call("RHugin_node_reverse_edge", node1.ptr, node2.ptr,
                   PACKAGE = "RHugin")
  RHugin.handle.error(status)

  invisible(NULL)
}


