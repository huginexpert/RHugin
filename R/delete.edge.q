delete.edge <- function(domain, child, parent)
{
  RHugin.check.args(domain, c(child, parent), character(0), "delete.edge")

  child.ptr <- .Call("RHugin_domain_get_node_by_name", domain, child,
                      PACKAGE = "RHugin")
  RHugin.handle.error()
  parent.ptr <- .Call("RHugin_domain_get_node_by_name", domain, parent,
                       PACKAGE = "RHugin")
  RHugin.handle.error()
  status <- .Call("RHugin_node_remove_parent", child.ptr, parent.ptr,
                   PACKAGE = "RHugin")
  RHugin.handle.error(status)

  invisible(NULL)
}


