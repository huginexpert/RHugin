get.table <- function(domain, node, type = c("cpt", "experience", "fading"),
                      class = c("data.frame", "table", "ftable", "numeric"))
{
  type <- match.arg(type)
  class <- match.arg(class)

  node.ptr <- nodePointersFromNames(domain, node[1])
  category <- .Call(RHugin_node_get_category, node.ptr)
  kind <- .Call(RHugin_node_get_kind, node.ptr)
  kind <- ifelse(is.na(kind), "none", kind)

  table.ptr <- switch(type,
    cpt = .Call(RHugin_node_get_table, node.ptr),
    experience = .Call(RHugin_node_get_experience_table, node.ptr),
    fading = .Call(RHugin_node_get_fading_table, node.ptr)
  )

  table.node.ptrs <- .Call(RHugin_table_get_nodes, table.ptr)
  table.nodes <- names(table.node.ptrs)

  if(kind == "continuous" && type == "cpt") {
    parent.nodes <- table.nodes[table.nodes != node]

    parent.ptrs <- table.node.ptrs[parent.nodes]
    parent.kinds <- .Call(RHugin_node_get_kind, parent.ptrs)

    discrete.parents <- parent.nodes[parent.kinds == "discrete"]
    continuous.parents <- parent.nodes[parent.kinds == "continuous"]
    continuous.parent.ptrs <-  table.node.ptrs[continuous.parents]

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

    alpha <- .Call(RHugin_node_get_alpha, node.ptr, i)

    beta <- list()
    for(n in continuous.parents)
      beta[[n]] <- .Call(RHugin_node_get_beta, node.ptr,
                         continuous.parent.ptrs[n], i)

    gamma <- .Call(RHugin_node_get_gamma, node.ptr, i)

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

    table <- .Call(RHugin_table_get_data, table.ptr)
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


