add.edge <- function(domain, child, parent)
{
  RHugin.check.args(domain, c(child, parent), character(0), "add.edge")

  child <- .Call("RHugin_domain_get_node_by_name", domain, child,
                  PACKAGE = "RHugin")
  RHugin.handle.error()

  for(node in parent) {
    node <- .Call("RHugin_domain_get_node_by_name", domain, node,
                   PACKAGE = "RHugin")
    RHugin.handle.error()
    status <- .Call("RHugin_node_add_parent", child, node, PACKAGE = "RHugin")
    RHugin.handle.error(status)
  }
 
  invisible(NULL)
}


