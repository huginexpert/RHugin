set.table <- function(domain, node, data,
                      type = c("cpt", "experience", "fading"))
{
  RHugin.check.args(domain, node, character(0), "set.table")
  type <- match.arg(type)

  class <- class(data)
  if(!is.element(class, c("data.frame", "table", "numeric")))
    stop("the", sQuote("data"), "argument must be a data frame,",
         "table or numeric vector")

  node.ptr <- .Call("RHugin_domain_get_node_by_name", domain, node,
                     PACKAGE = "RHugin")
  RHugin.handle.error()

  category <- .Call("RHugin_node_get_category", node.ptr, PACKAGE = "RHugin")
  kind <- .Call("RHugin_node_get_kind", node.ptr, PACKAGE = "RHugin")

  table.ptr <- switch(type,
    cpt = .Call("RHugin_node_get_table", node.ptr, PACKAGE = "RHugin"),
    experience = .Call("RHugin_node_get_experience_table", node.ptr,
                        PACKAGE = "RHugin"),
    fading = .Call("RHugin_node_get_fading_table", node.ptr,
                    PACKAGE = "RHugin"))
  RHugin.handle.error()

  if(class == "numeric") {
    if(kind == "discrete" || (type %in% c("experience", "fading"))) {
      status <- .Call("RHugin_table_set_data", table.ptr, as.double(table),
                       PACKAGE = "RHugin")
      RHugin.handle.error(status)
      status <- .Call("RHugin_node_touch_table", node.ptr, PACKAGE = "RHugin")
      RHugin.handle.error(status)
      return(invisible(NULL))
    }
    else
      stop("a numeric vector can only be interpreted as the conditional",
           "probability table (cpt) of a discrete node")
  }

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
      if(is.element(type, c("experience", "fading")))
         table <- data[["Counts"]]
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

    alpha <- .Call("RHugin_node_set_alpha", node.ptr,
                    as.double(table[components == "(Intercept)"]),
                    as.integer(i), PACKAGE = "RHugin")
    RHugin.handle.error()

    beta <- list()
    for(n in continuous.parents) {
      beta[[n]] <- .Call("RHugin_node_set_beta", node.ptr,
                          as.double(table[components == n]),
                          continuous.parent.ptrs[[n]], as.integer(i),
                          PACKAGE = "RHugin")
      RHugin.handle.error()
    }

    gamma <- .Call("RHugin_node_set_gamma", node.ptr,
                    as.double(table[components == "(Variance)"]),
                    as.integer(i), PACKAGE = "RHugin")
    RHugin.handle.error()
  }

  else {

    status <- .Call("RHugin_table_set_data", table.ptr, as.double(table),
                     PACKAGE = "RHugin")
    RHugin.handle.error(status)
    status <- .Call("RHugin_node_touch_table", node.ptr, PACKAGE = "RHugin")
    RHugin.handle.error(status)
  }

  invisible(NULL)
}


