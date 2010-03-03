get.marginal <- function(domain, nodes,
                         class = c("data.frame", "table", "ftable", "numeric"))
{
  RHugin.check.args(domain, nodes, character(0), "get.marginal")
  class <- match.arg(class)

  node.ptrs <- .Call("RHugin_domain_get_node_by_name", domain, nodes,
                      PACKAGE = "RHugin")
  categories <- .Call("RHugin_node_get_category", node.ptrs, PACKAGE = "RHugin")
  kinds <- .Call("RHugin_node_get_kind", node.ptrs, PACKAGE = "RHugin")

  if(any(categories != "chance"))
    stop("the ", sQuote("nodes"), " argument is not a set of distinct ",
         "chance nodes")

  discrete <- nodes[kinds == "discrete"]
  continuous <- nodes[kinds == "continuous"]

  nodes <- c(discrete, continuous)
  node.ptrs <- node.ptrs[nodes]

  table.ptr <- .Call("RHugin_domain_get_marginal", domain, node.ptrs,
                      PACKAGE = "RHugin")

  on.exit(.Call("RHugin_table_delete", table.ptr, PACKAGE = "RHugin"))

  states <- lapply(discrete, function(u) get.states(domain, u))
  names(states) <- discrete
  states <- rev(states)
  d <- sapply(states, length)

  table <- .Call("RHugin_table_get_data", table.ptr, PACKAGE = "RHugin")
  n.continuous <- length(continuous)
  n.table <- length(table)

  if(n.continuous) {
    mean <- matrix(0.0, nrow = n.table, ncol = n.continuous)
    dimnames(mean) <- list(1:n.table, continuous)
    cov <- list()

    for(j in 1:n.continuous)
      mean[ , j] <- .Call("RHugin_table_get_mean", table.ptr, 0:(n.table - 1),
                           node.ptrs[continuous[j]], PACKAGE = "RHugin")

    for(k in 1:n.table) {
      tmp <- matrix(0.0, n.continuous, n.continuous)
      dimnames(tmp) <- list(continuous, continuous)
      for(i in 1:n.continuous)
        tmp[i, i] <- .Call("RHugin_table_get_variance", table.ptr, k - 1,
                            node.ptrs[continuous[i]], PACKAGE = "RHugin")

      if(n.continuous > 1) {
        for(i in 2:n.continuous) {
          for(j in 1:(i - 1))
            tmp[i, j] <- tmp[j, i] <- .Call("RHugin_table_get_covariance",
                                             table.ptr, k - 1,
                                             node.ptrs[continuous[i]],
                                             node.ptrs[continuous[j]],
                                             PACKAGE = "RHugin")
        }
      }
    cov[[k]] <- tmp  
    }
  }

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
      ftable(table, row.vars = nodes[1])
    },

    "numeric" = table
  )

  if(n.continuous)
    list(table = table, mean = mean, cov = cov)
  else
    list(table = table)
}


