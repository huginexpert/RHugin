get.value <- function(domain, node)
{
  node.ptr <- nodePointersFromNames(domain, node[1])
  .Call(RHugin_node_get_value, node.ptr)
}


