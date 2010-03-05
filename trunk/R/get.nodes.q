get.nodes <- function(domain)
{
  RHugin.check.domain(domain, "get.nodes")

  nodes <- character(0)
  node.ptr <- .Call("RHugin_domain_get_first_node", domain, PACKAGE = "RHugin")

  while(!is.null(node.ptr)) {
    nodes <- c(.Call("RHugin_node_get_name", node.ptr, PACKAGE = "RHugin"),
               nodes)
    node.ptr <- .Call("RHugin_node_get_next", node.ptr, PACKAGE = "RHugin")
  }

  nodes
}


