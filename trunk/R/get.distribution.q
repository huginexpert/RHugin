get.distribution <- function(domain, node, class = c("data.frame", "table",
                             "ftable", "numeric"))
{
  RHugin.check.args(domain, node, character(0), "get.distribution")
  class <- match.arg(class)

  node.ptr <- .Call("RHugin_domain_get_node_by_name", domain, node[1],
                     PACKAGE = "RHugin")

  kind <- .Call("RHugin_node_get_kind", node.ptr, PACKAGE = "RHugin")
  if(kind[node] != "continuous")
    stop(node, " is not a conditional Gaussian (CG) node")

  table.ptr <- .Call("RHugin_node_get_distribution", node.ptr,
                      PACKAGE = "RHugin")

  on.exit(.Call("RHugin_table_delete", table.ptr, PACKAGE = "RHugin"))

  node.ptrs <- .Call("RHugin_table_get_nodes", table.ptr, PACKAGE = "RHugin")
  nodes <- names(node.ptrs)

  kinds <- .Call("RHugin_node_get_kind", node.ptrs, PACKAGE = "RHugin")
  discrete <- nodes[kinds == "discrete"]

  states <- lapply(discrete, function(u) get.states(domain, u))
  names(states) <- discrete
  states <- rev(states)
  d <- sapply(states, length)

  table <- .Call("RHugin_table_get_data", table.ptr, PACKAGE = "RHugin")
  n.table <- length(table)

  mean <- matrix(0.0, nrow = n.table, ncol = 1)
  dimnames(mean) <- list(1:n.table, node)
  cov <- list()

  mean[ , 1] <- .Call("RHugin_table_get_mean", table.ptr, 0:(n.table - 1),
                       node.ptrs[node], PACKAGE = "RHugin")

  for(k in 1:n.table)
    cov[[k]] <- .Call("RHugin_table_get_variance", table.ptr, k - 1,
                       node.ptrs[node], PACKAGE = "RHugin")

  if(!length(states))
    class <- "numeric"

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
      attributes(table) <- list(dim = sapply(states, length), dimnames = states,
                                class = "table")
      ftable(table, row.vars = node)
    },

    "numeric" = table
  )

  list(table = table, mean = mean, cov = cov)
}


