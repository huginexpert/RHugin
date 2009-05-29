set.table <- function(domain, node, data)
{
  RHugin.check.args(domain, node, character(0), "set.table")

  table.nodes <- get.table.nodes(domain, node)
  node.summary <- summary(domain, nodes = table.nodes)$nodes

  node.ptr <- .Call("RHugin_domain_get_node_by_name", domain, node,
                     PACKAGE = "RHugin")
  RHugin.handle.error()

  if(node.summary[[node]]$kind == "discrete") {
    table.nodes <- rev(table.nodes)

    Freq <- switch(class(data),
      "data.frame" = {
        Freq <- data[["Freq"]]

        if(is.null(Freq))
          Freq <- rep(1, dim(data)[1])

        states <- lapply(table.nodes, function(u) get.states(domain, u))
        names(states) <- table.nodes

        indices <- as.list(data[table.nodes])
        for(i in table.nodes)
          indices[[i]] <- factor(indices[[i]], levels = states[[i]])

        Freq <- as.vector(tapply(Freq, indices, sum), mode = "numeric")
        Freq[is.na(Freq)] <- 0.0
        Freq
      },

      "table" = {
        table.nodes <- get.table.nodes(domain, node)
        states <- lapply(table.nodes, function(u) get.states(domain, u))
        names(states) <- table.nodes
        states <- rev(states)

        if(!isTRUE(all.equal(dimnames(data), states)))
          stop("table dimnames do not match node states")

        as.vector(data)
      },

      "numeric" = data,

      NULL
    )

    if(is.null(Freq))
      stop("could not interpret ", deparse(substitute(data)), " as table")

    table.ptr <- .Call("RHugin_node_get_table", node.ptr, PACKAGE = "RHugin")
    RHugin.handle.error()

    status <- .Call("RHugin_table_set_data", table.ptr, as.double(Freq),
                     PACKAGE = "RHugin")
    RHugin.handle.error(status)
    status <- .Call("RHugin_node_touch_table", node.ptr, PACKAGE = "RHugin")
    RHugin.handle.error(status)
  }

  if(node.summary[[node]]$kind == "continuous") {
    if(class(data) != "data.frame")
      stop("the data argument must be a data frame for continuous nodes")

    Value <- data[["Value"]]

    if(is.null(Value))
      stop("no data given")

    parent.nodes <- table.nodes[table.nodes != node]
    parent.kinds <- sapply(node.summary[parent.nodes], function(u) u$kind)
    discrete.parents <- rev(parent.nodes[parent.kinds == "discrete"])
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
    n.states <- sapply(states, length)
    n.state.space <- ifelse(length(n.states), prod(n.states), 1)

    indices <- as.list(data[c(node, discrete.parents)])
    for(i in discrete.parents)
      indices[[i]] <- factor(indices[[i]], levels = states[[i]])
    indices[[node]] <- factor(indices[[node]], levels = components)

    Value <- as.vector(tapply(Value, indices, function(u) u), mode = "numeric")
    if(any(is.na(Value))) stop("mising values in table")

    components <- rep(components, n.state.space)
    i <- 0:(n.state.space - 1)

    alpha <- .Call("RHugin_node_set_alpha", node.ptr,
                    as.double(Value[components == "(Intercept)"]),
                    as.integer(i), PACKAGE = "RHugin")
    RHugin.handle.error()

    beta <- list()
    for(n in continuous.parents) {
      beta[[n]] <- .Call("RHugin_node_set_beta", node.ptr,
                          as.double(Value[components == n]),
                          continuous.parent.ptrs[[n]], as.integer(i),
                          PACKAGE = "RHugin")
      RHugin.handle.error()
    }

    gamma <- .Call("RHugin_node_set_gamma", node.ptr,
                    as.double(Value[components == "(Variance)"]),
                    as.integer(i), PACKAGE = "RHugin")
    RHugin.handle.error()
  }

  invisible(NULL)
}


