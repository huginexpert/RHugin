switch.parent <- function(domain, child, parent, new.parent)
{
  RHugin.check.args(domain, c(child, parent, new.parent), character(0),
                   "switch.parent")

  child.ptr <- .Call("RHugin_domain_get_node_by_name", domain,
                      as.character(child[1]), PACKAGE = "RHugin")
  RHugin.handle.error()
  parent.ptr <- .Call("RHugin_domain_get_node_by_name", domain,
                       as.character(parent[1]), PACKAGE = "RHugin")
  RHugin.handle.error()
  new.parent.ptr <- .Call("RHugin_domain_get_node_by_name", domain,
                           as.character(new.parent[1]), PACKAGE = "RHugin")
  RHugin.handle.error()
  status <- .Call("RHugin_node_switch_parent", child.ptr, parent.ptr,
                   new.parent.ptr, PACKAGE = "RHugin")
  RHugin.handle.error(status)

  invisible(NULL)
}


