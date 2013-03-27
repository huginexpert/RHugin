get.value <- function(domain, node)
{
  node <- node[1]
  RHugin.check.args(domain, node, character(0), "get.value")

  node.ptr <- .Call(RHugin_domain_get_node_by_name, domain, node)

  .Call(RHugin_node_get_value, node.ptr)
}


