get.children <- function(domain, node)
{
  node.ptr <- nodePointersFromNames(domain, node[1])
  names(.Call(RHugin_node_get_children, node.ptr)[[node]])
}


