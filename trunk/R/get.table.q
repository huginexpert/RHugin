get.table <- function(domain, node)
{
  RHugin.check.args(domain, node, character(0), "get.table")
  table.nodes <- get.table.nodes(domain, node)
  states.list <- sapply(table.nodes, function(u) get.states(domain, u),
                        simplify = FALSE)
  states.list <- states.list[length(states.list):1]
  X <- expand.grid(states.list)
  X <- X[length(X):1]
  node.ptr <- .Call("RHugin_domain_get_node_by_name", domain$pointer, node,
                     PACKAGE = "RHugin")
  RHugin.handle.error()
  table.ptr <- .Call("RHugin_node_get_table", node.ptr, PACKAGE = "RHugin")
  RHugin.handle.error()
  X$prob <- .Call("RHugin_table_get_data", table.ptr, PACKAGE = "RHugin")
  RHugin.handle.error()
  X
}


