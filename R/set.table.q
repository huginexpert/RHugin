set.table <- function(domain, node, data,
                      type = c("cpt", "experience", "fading"))
{
  RHugin.check.args(domain, node, character(0), "set.table")
  type <- match.arg(type)

  class <- class(data)
  if(!is.element(class, c("data.frame", "table", "numeric")))
    stop("the ", sQuote("data"), " argument must be a data frame, ",
         "a table or a numeric vector")

  node.ptr <- .Call(RHugin_domain_get_node_by_name, domain, node[1])

  category <- .Call(RHugin_node_get_category, node.ptr)
  kind <- .Call(RHugin_node_get_kind, node.ptr)
  kind <- ifelse(is.na(kind), "none", kind)

  table.ptr <- switch(type,
    cpt = .Call(RHugin_node_get_table, node.ptr),
    experience = .Call(RHugin_node_get_experience_table, node.ptr),
    fading = .Call(RHugin_node_get_fading_table, node.ptr)
  )

  if(class == "numeric") {
    if(kind == "discrete" || (type %in% c("experience", "fading"))) {
      .Call(RHugin_table_set_data, table.ptr, data)
      .Call(RHugin_node_touch_table, node.ptr)
      return(invisible())
    }
    else
      stop("a numeric vector can only be interpreted as the conditional",
           "probability table (cpt) of a discrete node")
  }

  table.node.ptrs <- .Call(RHugin_table_get_nodes, table.ptr)
  table.nodes <- names( table.node.ptrs)

  if(kind == "continuous" && type == "cpt") {
    parent.nodes <- table.nodes[table.nodes != node]

    parent.ptrs <- table.node.ptrs[parent.nodes]
    parent.kinds <- .Call(RHugin_node_get_kind, parent.ptrs)

    discrete.parents <- parent.nodes[parent.kinds == "discrete"]
    continuous.parents <- parent.nodes[parent.kinds == "continuous"]

    continuous.parent.ptrs <- parent.ptrs[continuous.parents]

    components <- c("(Intercept)", continuous.parents, "(Variance)")
    states <- lapply(discrete.parents, function(u) get.states(domain, u))
    names(states) <- discrete.parents
    states[[node]] <- components
    states <- rev(states)
  }

  else {
    table.nodes <- rev(table.nodes)
    states <- lapply(table.nodes, function(u) get.states(domain, u))
    names(states) <- table.nodes
  }

  table <- switch(class(data),
    "data.frame" = {
      table <- NULL
      if(type == "experience")
         table <- data[["Counts"]]
      else if(type == "fading")
         table <- data[["Lambda"]]
      else if(category == "utility")
        table <- data[["Utility"]]
      else if(category == "decision")
        table <- data[["Cost"]]
      else if(category == "chance") {
        if(kind == "continuous")
          table <- data[["Value"]]
        else {
          table <- data[["Freq"]]
          if(is.null(table)) table <- rep(1, dim(data)[1])
        }
      }

      if(is.null(table))
        stop("no data in table")

      if(length(missing.data <- setdiff(names(states), names(data))))
        stop("no data provided for the following node(s): ",
              paste(missing.data, collapse = ", "))

      indices <- as.list(data[names(states)])
      for(i in names(states))
        indices[[i]] <- factor(indices[[i]], levels = states[[i]])

      table <- as.vector(tapply(table, indices, sum), mode = "numeric")
      table[is.na(table)] <- 0.0
      table
    },

    "table" = {
      c.states <- lapply(states, as.character)

      if(!isTRUE(all.equal(dimnames(data), states)))
        stop("table dimnames do not match node states")

      as.vector(data)
    })

  if(kind == "continuous" && type == "cpt") {
    n.states <- sapply(states[-1], length)
    n.state.space <- ifelse(length(n.states), prod(n.states), 1)

    components <- rep(states[[node]], n.state.space)
    i <- 0:(n.state.space - 1)

    .Call(RHugin_node_set_alpha, node.ptr, table[components == "(Intercept)"], i)

    for(n in continuous.parents)
      .Call(RHugin_node_set_beta, node.ptr, table[components == n],
            continuous.parent.ptrs[n], i)

    .Call(RHugin_node_set_gamma, node.ptr, table[components == "(Variance)"], i)
  }

  else {
    .Call(RHugin_table_set_data, table.ptr, table)
    .Call(RHugin_node_touch_table, node.ptr)
  }

  invisible()
}


