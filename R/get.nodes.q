get.nodes <- function(domain)
{
  nodes <- character(0)
  node.ptr <- .Call(RHugin_domain_get_first_node, domain)

  while(!is.null(node.ptr)) {
    nodes <- c(nodes, .Call(RHugin_node_get_name, node.ptr))
    node.ptr <- .Call(RHugin_node_get_next, node.ptr)
  }

  nodes
}


