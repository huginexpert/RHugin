switch.parent <- function(domain, child, parent, new.parent)
{
  child.ptr <- nodePointersFromNames(domain, child[1])
  parent.ptr <- nodePointersFromNames(domain, parent[1])
  new.parent.ptr <- nodePointersFromNames(domain, new.parent[1])
  .Call(RHugin_node_switch_parent, child.ptr, parent.ptr, new.parent.ptr)

  invisible()
}


