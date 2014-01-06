delete.node <- function(domain, node)
{
  node.ptrs <- nodePointersFromNames(domain, unique(node))
  .Call(RHugin_node_delete, node.ptrs)

  invisible()
}


