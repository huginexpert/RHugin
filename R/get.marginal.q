get.marginal <- function(domain, nodes,
                         class = c("data.frame", "table", "ftable", "numeric"))
{
  RHugin.check.args(domain, nodes, character(0), "get.marginal")
  class <- match.arg(class)

  node.ptrs <- list()
  categories <- character()
  kinds <- character()

  for(node in nodes) {
    node.ptrs[[node]] <- .Call("RHugin_domain_get_node_by_name", domain, node,
                                PACKAGE = "RHugin")
    RHugin.handle.error()

    categories[node] <- .Call("RHugin_node_get_category", node.ptrs[[node]],
                               PACKAGE = "RHugin")
    RHugin.handle.error()

    kinds[node] <- .Call("RHugin_node_get_kind", node.ptrs[[node]],
                          PACKAGE = "RHugin")
    RHugin.handle.error()
  }

  if(any(categories != "chance"))
    stop("the ", sQuote("nodes"), " argument is not a set of distinct ",
         "chance nodes")

  discrete <- nodes[kinds == "discrete"]
  continuous <- nodes[kinds == "continuous"]

  if(length(continuous))
    stop("no support for continuous nodes yet")

  nodes <- c(discrete, continuous)
  node.ptrs <- node.ptrs[nodes]

  table.ptr <- .Call("RHugin_domain_get_marginal", domain, node.ptrs,
                      PACKAGE = "RHugin")
  RHugin.handle.error()
  on.exit(.Call("RHugin_table_delete", table.ptr, PACKAGE = "RHugin"))

  table.nodes <- names(.Call("RHugin_table_get_nodes", table.ptr,
                              PACKAGE = "RHugin"))
  RHugin.handle.error()

  states <- lapply(nodes, function(u) get.states(domain, u))
  names(states) <- nodes
  states <- rev(states)
  d <- sapply(states, length)

  table <- .Call("RHugin_table_get_data", table.ptr, PACKAGE = "RHugin")
  RHugin.handle.error()

  table <- switch(class,
    "data.frame" = {
      table <- cbind(expand.grid(states), table)
      names(table)[length(table)] <- "Freq"
      table
    },

    "table" = {
      attributes(table) <- list(dim = d, dimnames = states, class = "table")
      table
    },

    "ftable" = {
      attributes(table) <- list(dim = d, dimnames = states, class = "table")
      n <- length(table.nodes)
      ftable(table, row.vars = table.nodes[n], col.vars = table.nodes[-n])
    },

    "numeric" = table
  )

  table
}


