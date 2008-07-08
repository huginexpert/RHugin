set.table <- function(domain, node, data)
{
  RHugin.check.args(domain, node, character(0), "set.table")
  existing.data <- get.table(domain, node)

  if(is.character(all.equal(data[-length(data)], existing.data[-length(existing.data)]))) {
    if(nrow(data) == nrow(existing.data) && all(is.element(names(data), names(existing.data))))
      data <- condense.data.frame(data, names(existing.data)[-length(existing.data)])
    else
      stop(paste("the data frame", deparse(substitute(data)), "does not match the table for", node))
  }

  node.ptr <- .Call("RHugin_domain_get_node_by_name", domain$pointer, node,
                     PACKAGE = "RHugin")
  RHugin.handle.error()
  table.ptr <- .Call("RHugin_node_get_table", node.ptr, PACKAGE = "RHugin")
  RHugin.handle.error()
  status <- .Call("RHugin_table_set_data", table.ptr,
                   as.numeric(data[[length(data)]]), PACKAGE = "RHugin")
  RHugin.handle.error(status)
  status <- .Call("RHugin_node_touch_table", node.ptr, PACKAGE = "RHugin")
  RHugin.handle.error(status)

  invisible(NULL)
}


