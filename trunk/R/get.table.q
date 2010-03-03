get.table <- function(domain, node, type = c("cpt", "experience", "fading"),
                      class = c("data.frame", "table", "ftable", "numeric"))
{
  RHugin.check.args(domain, node, character(0), "get.table")
  type <- match.arg(type)
  class <- match.arg(class)

  node.ptr <- .Call("RHugin_domain_get_node_by_name", domain, node[1],
                     PACKAGE = "RHugin")
  category <- .Call("RHugin_node_get_category", node.ptr, PACKAGE = "RHugin")
  kind <- .Call("RHugin_node_get_kind", node.ptr, PACKAGE = "RHugin")

  table.ptr <- switch(type,
    cpt = .Call("RHugin_node_get_table", node.ptr, PACKAGE = "RHugin"),
    experience = .Call("RHugin_node_get_experience_table", node.ptr,
                        PACKAGE = "RHugin"),
    fading = .Call("RHugin_node_get_fading_table", node.ptr,
                    PACKAGE = "RHugin"))

  table.nodes <- names(.Call("RHugin_table_get_nodes", table.ptr,
                              PACKAGE = "RHugin"))

  if(kind == "continuous" && type == "cpt") {
    parent.nodes <- table.nodes[table.nodes != node]
    parent.kinds <- character(0)

    parent.ptrs <- .Call("RHugin_domain_get_node_by_name", domain, parent.nodes,
                          PACKAGE = "RHugin")
    parent.kinds <- .Call("RHugin_node_get_kind", parent.ptrs,
                           PACKAGE = "RHugin")

    discrete.parents <- parent.nodes[parent.kinds == "discrete"]
    continuous.parents <- parent.nodes[parent.kinds == "continuous"]
    continuous.parent.ptrs <- list()

    continuous.parent.ptrs <- .Call("RHugin_domain_get_node_by_name", domain,
                                     continuous.parents, PACKAGE = "RHugin")

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

    alpha <- .Call("RHugin_node_get_alpha", node.ptr, i, PACKAGE = "RHugin")

    beta <- list()
    for(n in continuous.parents)
      beta[[n]] <- .Call("RHugin_node_get_beta", node.ptr,
                          continuous.parent.ptrs[n], i, PACKAGE = "RHugin")

    gamma <- .Call("RHugin_node_get_gamma", node.ptr, i, PACKAGE = "RHugin")

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
  }

  table <- switch(class,
    "data.frame" = {
      if(length(states))
        table <- cbind(expand.grid(states), table)
      else
        table <- data.frame(Counts = table)
      if(type == "experience")
        names(table)[length(table)] <- "Counts"
      else if(type == "fading")
        names(table)[length(table)] <- "Lambda"
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
      if(!length(states))
        stop("can not coerce zero dimensional structure to class table")

      attributes(table) <- list(dim = sapply(states, length), dimnames = states,
                                class = "table")
      table
    },

    "ftable" = {
      if(!length(states))
        stop("can not coerce zero dimensional structure to class ftable")

      attributes(table) <- list(dim = sapply(states, length), dimnames = states,
                                class = "table")
      ftable(table, row.vars = node)
    },

    "numeric" = table
  )

  table
}


