add.edge <- function(domain, child, parent)
{
  child.ptr <- nodePointersFromNames(domain, child[1])
  parent.ptr <- nodePointersFromNames(domain, parent)
  .Call(RHugin_node_add_parent, child.ptr, parent.ptr)
 
  invisible()
}


