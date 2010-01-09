add.edge <- function(domain, child, parent)
{
  RHugin.check.args(domain, c(child, parent), character(0), "add.edge")

  child <- .Call("RHugin_domain_get_node_by_name", domain, child,
                  PACKAGE = "RHugin")

  parent <- .Call("RHugin_domain_get_node_by_name", domain, parent,
                   PACKAGE = "RHugin")

  status <- .Call("RHugin_node_add_parent", child, parent, PACKAGE = "RHugin")
 
  invisible(status)
}


