switch.parent <- function(domain, child, parent, new.parent)
{
  RHugin.check.args(domain, c(child, parent, new.parent), character(0),
                   "switch.parent")

  child.ptr <- .Call("RHugin_domain_get_node_by_name", domain, child,
                      PACKAGE = "RHugin")
  parent.ptr <- .Call("RHugin_domain_get_node_by_name", domain, parent,
                       PACKAGE = "RHugin")
  new.parent.ptr <- .Call("RHugin_domain_get_node_by_name", domain, new.parent,
                           PACKAGE = "RHugin")
  .Call("RHugin_node_switch_parent", child.ptr, parent.ptr, new.parent.ptr,
         PACKAGE = "RHugin")

  invisible()
}


