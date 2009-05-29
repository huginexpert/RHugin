get.table <- function(domain, node,
                      class = c("data.frame", "table", "ftable", "numeric"))
{
  RHugin.check.args(domain, node, character(0), "get.table")
  class <- match.arg(class)

  table.nodes <- get.table.nodes(domain, node)
  node.summary <- summary(domain, nodes = table.nodes)$nodes
  table <- NULL

  node.ptr <- .Call("RHugin_domain_get_node_by_name", domain, node,
                     PACKAGE = "RHugin")
  RHugin.handle.error()

  if(node.summary[[node]]$kind == "discrete") {
    states <- lapply(table.nodes, function(u) get.states(domain, u))
    names(states) <- table.nodes
    states <- rev(states)
    d <- sapply(states, length)

    table.ptr <- .Call("RHugin_node_get_table", node.ptr, PACKAGE = "RHugin")
    RHugin.handle.error()
    Freq <- .Call("RHugin_table_get_data", table.ptr, PACKAGE = "RHugin")
    RHugin.handle.error()

    table <- switch(class,
      "data.frame" = cbind(expand.grid(states), Freq = Freq),

      "table" = {
        attributes(Freq) <- list(dim = d, dimnames = states, class = "table")
        Freq
      },

      "ftable" = {
        attributes(Freq) <- list(dim = d, dimnames = states, class = "table")
        n <- length(table.nodes)
        ftable(Freq, row.vars = table.nodes[n], col.vars = table.nodes[-n])
      },

      "numeric" = Freq
    )
  }

  if(node.summary[[node]]$kind == "continuous") {
    parent.nodes <- table.nodes[table.nodes != node]
    parent.kinds <- sapply(node.summary[parent.nodes], function(u) u$kind)
    discrete.parents <- parent.nodes[parent.kinds == "discrete"]
    continuous.parents <- parent.nodes[parent.kinds == "continuous"]
    continuous.parent.ptrs <- list()

    for(n in continuous.parents) {
      continuous.parent.ptrs[[n]] <- .Call("RHugin_domain_get_node_by_name",
                                            domain, n, PACKAGE = "RHugin")
      RHugin.handle.error()
    }

    components <- c("(Intercept)", continuous.parents, "(Variance)")
    states <- character(0)
    n.state.space <- 1
    i <- 0

    if(length(discrete.parents)) {
      states <- lapply(discrete.parents, function(u) get.states(domain, u))
      names(states) <- discrete.parents
      states <- rev(states)
      n.state.space <- prod(sapply(states, length))
      i <- 0:(n.state.space - 1)
    }

    alpha <- .Call("RHugin_node_get_alpha", node.ptr, as.integer(i),
                    PACKAGE = "RHugin")
    RHugin.handle.error()

    beta <- list()
    for(n in continuous.parents) {
      beta[[n]] <- .Call("RHugin_node_get_beta", node.ptr,
                          continuous.parent.ptrs[[n]], as.integer(i),
                          PACKAGE = "RHugin")
      RHugin.handle.error()
    }

    gamma <- .Call("RHugin_node_get_gamma", node.ptr, as.integer(i),
                    PACKAGE = "RHugin")
    RHugin.handle.error()

    if(length(beta))
      table <- as.vector(t(cbind(alpha, as.data.frame(beta), gamma)))
    else
      table <- as.vector(t(cbind(alpha, gamma)))

    table <- switch(class,
      "data.frame" = {
        if(length(states)) {
          states <- expand.grid(states)
          states <- states[rep(1:n.state.space, each = length(components)), , drop = FALSE]
          states[[node]] <- rep(components, n.state.space)
          table <- cbind(states, Value = table)
          row.names(table) <- NULL
        }
        else {
          table <- data.frame(components, table)
          names(table) <- c(node, "Value")
        }

        table
      },

      "table" = {
        dn <- list()
        dn[[node]] <- components
        dn <- c(dn, states)
        attributes(table) <- list(dim = sapply(dn, length), dimnames = dn,
                                  class = "table")
        table
      },

      "ftable" = {
        dn <- list()
        dn[[node]] <- components
        dn <- c(dn, states)
        attributes(table) <- list(dim = sapply(dn, length), dimnames = dn,
                                  class = "table")
        ftable(table, row.vars = node, col.vars = discrete.parents)
      },

      "numeric" = table
    )
  }

  table
}


