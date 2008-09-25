get.table <- function(domain, node, class = c("data.frame", "table", "ftable"))
{
  RHugin.check.args(domain, node, character(0), "get.table")
  class <- match.arg(class)

  table.nodes <- get.table.nodes(domain, node)
  states <- lapply(table.nodes, function(u) get.states(domain, u))
  names(states) <- table.nodes
  states <- rev(states)
  d <- sapply(states, length)

  node.ptr <- .Call("RHugin_domain_get_node_by_name", domain$pointer, node,
                     PACKAGE = "RHugin")
  RHugin.handle.error()
  table.ptr <- .Call("RHugin_node_get_table", node.ptr, PACKAGE = "RHugin")
  RHugin.handle.error()
  Freq <- .Call("RHugin_table_get_data", table.ptr, PACKAGE = "RHugin")
  RHugin.handle.error()

  switch(class,
    "data.frame" = cbind(expand.grid(states), Freq = Freq),

    "table" = {
      attributes(Freq) <- list(dim = d, dimnames = states, class = "table")
      Freq
    },

    "ftable" = {
      attributes(Freq) <- list(dim = d, dimnames = states, class = "table")
      ftable(Freq, row.vars = 1:length(d))
    }
  )
}


