set.table <- function(domain, node, data)
{
  RHugin.check.args(domain, node, character(0), "set.table")

  Freq <- as.numeric(data[[length(data)]])

  table.nodes <- rev(get.table.nodes(domain, node))
  states <- lapply(table.nodes, function(u) get.states(domain, u))
  names(states) <- table.nodes

  indices <- as.list(data[table.nodes])
  for(i in table.nodes)
    indices[[i]] <- factor(indices[[i]], levels = states[[i]])

  Freq <- as.vector(tapply(Freq, indices, sum))
  Freq[is.na(Freq)] <- 0

  node.ptr <- .Call("RHugin_domain_get_node_by_name", domain, node,
                     PACKAGE = "RHugin")
  RHugin.handle.error()
  table.ptr <- .Call("RHugin_node_get_table", node.ptr, PACKAGE = "RHugin")
  RHugin.handle.error()

  status <- .Call("RHugin_table_set_data", table.ptr, as.numeric(Freq),
                   PACKAGE = "RHugin")
  RHugin.handle.error(status)
  status <- .Call("RHugin_node_touch_table", node.ptr, PACKAGE = "RHugin")
  RHugin.handle.error(status)

  invisible(NULL)
}


