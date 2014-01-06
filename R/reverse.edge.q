reverse.edge <- function(domain, node1, node2)
{
  node1.ptr <- nodePointersFromNames(domain, node1[1])
  node2.ptr <- nodePointersFromNames(domain, node2[1])
  .Call(RHugin_node_reverse_edge, node1.ptr, node2.ptr)

  invisible()
}


