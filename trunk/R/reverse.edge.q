reverse.edge <- function(domain, node1, node2)
{
  RHugin.check.args(domain, c(node1, node2), character(0), "reverse.edge")

  node1.ptr <- .Call("RHugin_domain_get_node_by_name", domain, node1,
                      PACKAGE = "RHugin")
  node2.ptr <- .Call("RHugin_domain_get_node_by_name", domain, node2,
                      PACKAGE = "RHugin")
  .Call("RHugin_node_reverse_edge", node1.ptr, node2.ptr, PACKAGE = "RHugin")

  invisible()
}


