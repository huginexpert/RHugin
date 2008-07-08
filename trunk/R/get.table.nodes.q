get.table.nodes <- function(domain, node)
{
  RHugin.check.args(domain, node, character(0), "get.table.nodes")
  node.ptr <- .Call("RHugin_domain_get_node_by_name", domain$pointer, node,
                     PACKAGE = "RHugin")
  RHugin.handle.error()
  table.ptr <- .Call("RHugin_node_get_table", node.ptr, PACKAGE = "RHugin")
  RHugin.handle.error()
  table.nodes <- names(.Call("RHugin_table_get_nodes", table.ptr,
                              PACKAGE = "RHugin"))
  RHugin.handle.error()
  table.nodes
}


