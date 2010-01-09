get.category <- function(domain, nodes)
{
  RHugin.check.args(domain, nodes, character(0), "get.category")

  node.ptrs <- .Call("RHugin_domain_get_node_by_name", domain, nodes,
                      PACKAGE = "RHugin")

  .Call("RHugin_node_get_category", node.ptrs, PACKAGE = "RHugin")
}


