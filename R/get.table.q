get.table <- function(domain, node, type = c("cpt", "experience", "fading"),
                      class = c("data.frame", "table", "ftable", "numeric"))
{
  RHugin.check.args(domain, node, character(0), "get.table")
  type <- match.arg(type)
  class <- match.arg(class)

  node.ptr <- .Call("RHugin_domain_get_node_by_name", domain,
                     as.character(node[1]), PACKAGE = "RHugin")
  category <- .Call("RHugin_node_get_category", node.ptr, PACKAGE = "RHugin")
  kind <- .Call("RHugin_node_get_kind", node.ptr, PACKAGE = "RHugin")

  table.ptr <- switch(type,
    cpt = .Call("RHugin_node_get_table", node.ptr, PACKAGE = "RHugin"),
    experience = .Call("RHugin_node_get_experience_table", node.ptr,
                        PACKAGE = "RHugin"),
    fading = .Call("RHugin_node_get_fading_table", node.ptr,
                    PACKAGE = "RHugin"))
  RHugin.handle.error()

  table.nodes <- names(.Call("RHugin_table_get_nodes", table.ptr,
                              PACKAGE = "RHugin"))
  RHugin.handle.error()

  if(kind == "continuous" && type == "cpt") {
    parent.nodes <- table.nodes[table.nodes != node]
    parent.kinds <- character(0)

    for(n in parent.nodes) {
      parent.ptr <- .Call("RHugin_domain_get_node_by_name", domain, n,
                           PACKAGE = "RHugin")
      RHugin.handle.error()
      parent.kinds[n] <- .Call("RHugin_node_get_kind", parent.ptr,
                                PACKAGE = "RHugin")
    }

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

    states <- c(list(components), states)
    names(states)[1] <- node
  }

  else {
    states <- lapply(table.nodes, function(u) get.states(domain, u))
    names(states) <- table.nodes
    states <- rev(states)

    table <- .Call("RHugin_table_get_data", table.ptr, PACKAGE = "RHugin")
    RHugin.handle.error()
  }

  table <- switch(class,
    "data.frame" = {
      table <- cbind(expand.grid(states), table)
      if(is.element(type, c("experience", "fading")))
        names(table)[length(table)] <- "Counts"
      else if(category == "utility")
        names(table)[length(table)] <- "Utility"
      else if(category == "decision")
        names(table)[length(table)] <- "Cost"
      else {
        if(kind == "continuous")
          names(table)[length(table)] <- "Value"
        else
          names(table)[length(table)] <- "Freq"
      }
      table
    },

    "table" = {
      attributes(table) <- list(dim = sapply(states, length), dimnames = states,
                                class = "table")
      table
    },

    "ftable" = {
      attributes(table) <- list(dim = sapply(states, length), dimnames = states,
                                class = "table")
      ftable(table, row.vars = node)
    },

    "numeric" = table
  )

  table
}


