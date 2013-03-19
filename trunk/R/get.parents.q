get.parents <- function(domain, node)
{
  node <- node[1]
  RHugin.check.args(domain, node, character(0), "get.parents")

  node.ptr <- .Call(RHugin_domain_get_node_by_name, domain, node)
  
  names(.Call(RHugin_node_get_parents, node.ptr)[[node]])
}


