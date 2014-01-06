delete.edge <- function(domain, node, parent)
{
  node.ptr <- nodePointersFromNames(domain, node[1])
  parent.ptr <- nodePointersFromNames(domain, parent[1])
  .Call(RHugin_node_remove_parent, node.ptr, parent.ptr)

  invisible()
}


