add.edge <- function(domain, child, parent)
{
  RHugin.check.args(domain, c(child, parent), character(0), "add.edge")

  child <- .Call("RHugin_domain_get_node_by_name", domain$pointer, child,
                  PACKAGE = "RHugin")
  RHugin.handle.error()
  parent <- .Call("RHugin_domain_get_node_by_name", domain$pointer, parent,
                   PACKAGE = "RHugin")
  RHugin.handle.error()
  status <- .Call("RHugin_node_add_parent", child, parent, PACKAGE = "RHugin")
  RHugin.handle.error(status)

  invisible(NULL)
}


