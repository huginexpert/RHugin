set.table <- function(domain, node, data)
{
  RHugin.check.args(domain, node, character(0), "set.table")

  x <- switch(class(data),
    "data.frame" = {
      data <- condense.data.frame(data, get.table.nodes(domain, node))
      data[[length(data)]]
    },
    stop("RHugin doesn't wanna"))

  node.ptr <- .Call("RHugin_domain_get_node_by_name", domain$pointer, node,
                     PACKAGE = "RHugin")
  RHugin.handle.error()
  table.ptr <- .Call("RHugin_node_get_table", node.ptr, PACKAGE = "RHugin")
  RHugin.handle.error()
  status <- .Call("RHugin_table_set_data", table.ptr, as.numeric(x),
                   PACKAGE = "RHugin")
  RHugin.handle.error(status)
  status <- .Call("RHugin_node_touch_table", node.ptr, PACKAGE = "RHugin")
  RHugin.handle.error(status)

  invisible(NULL)
}


