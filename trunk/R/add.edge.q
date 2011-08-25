add.edge <- function(domain, child, parent)
{
  RHugin.check.args(domain, c(child, parent), character(0), "add.edge")

  child <- .Call(RHugin_domain_get_node_by_name, domain, child)
  parent <- .Call(RHugin_domain_get_node_by_name, domain, parent)
  .Call(RHugin_node_add_parent, child, parent)
 
  invisible()
}


