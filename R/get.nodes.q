get.nodes <- function(domain)
{
  RHugin.check.domain(domain, "get.nodes")

  nodes <- character(0)
  node.ptr <- .Call(RHugin_domain_get_first_node, domain)

  while(!is.null(node.ptr)) {
    nodes <- c(.Call(RHugin_node_get_name, node.ptr), nodes)
    node.ptr <- .Call(RHugin_node_get_next, node.ptr)
  }

  nodes
}


