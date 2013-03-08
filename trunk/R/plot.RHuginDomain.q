plot.RHuginDomain <- function(x, y, what = c("network", "jt"), ...)
{
  what <- match.arg(what)
  RHugin.check.domain(x, "plot.RHuginDomain")

  if(!require(Rgraphviz))
    stop("plotting an RHugin domain requires the Rgraphviz package")

  if(what == "network") {
    nodes <- get.nodes(x)
    node.ptrs <- .Call(RHugin_domain_get_node_by_name, x, nodes)
    categories <- .Call(RHugin_node_get_category, node.ptrs)
    kinds <- .Call(RHugin_node_get_kind, node.ptrs)

    fill <- character(length(nodes))
    shape <- character(length(nodes))
    names(fill) <- names(shape) <- nodes

    for(node in nodes) {
      if(categories[node] == "decision") {
        fill[node] <- "#FFB1B2"
        shape[node] <- "rectangle"
      }
      else if(categories[node] == "utility") {
        fill[node] <- "#B4FF6E"
        shape[node] <- "diamond"
      }
      else {
        if(kinds[node] == "discrete")
        {
          fill[node] <- "#FFFFB2"
          shape[node] <- "ellipse"
        }
        else {
          fill[node] <- "#FFFF00"
          shape[node] <- "ellipse"
        }
      }
    }

    gx <- as.graph.RHuginDomain(x)
    gx <- layoutGraph(gx, layoutFun = layoutRHugin, domain = x)
    nodeRenderInfo(gx) <- list(fill = fill, shape = shape, lwd = 2)
    edgeRenderInfo(gx) <- list(lwd = 2)
    graphRenderInfo(gx) <- list(ratio = 1.0)
    renderGraph(gx)
  }

  if(what == "jt") {
    if(!.Call(RHugin_domain_is_triangulated, x))
      stop("the domain is not triangulated")

    jts <- list(.Call(RHugin_domain_get_first_junction_tree, x))

    while(!is.null(njt <- .Call(RHugin_jt_get_next, jts[[length(jts)]])))
      jts <- c(jts, njt)

    g <- new("graphNEL")
    nAttrs <- list()
    nAttrs$height <- character(0)
    nAttrs$label <- character(0)
    nAttrs$color <- character(0)
    nAttrs$fillcolor <- character(0)

    label.width <- 1.5 * max(max(strwidth(get.nodes(x), units = "inches")), 1.0)
    line.height <- 2 * max(strheight(get.nodes(x), units = "inches"))

    for(jt in jts) {
      cliques <- .Call(RHugin_jt_get_cliques, jt)
      n.cliques <- length(cliques)
      clique.members <- lapply(cliques, function(u)
        names(.Call(RHugin_clique_get_members, u)))
      clique.sizes <- sapply(clique.members, length)
      clique.names <- sapply(clique.members, paste, collapse = ":")

      g <- addNode(clique.names, g)

      for(clique in cliques) {
        clique.name <- paste(names(.Call(RHugin_clique_get_members, clique)),
                             collapse = ":")

      neighbors <- .Call(RHugin_clique_get_neighbors, clique)
      neighbor.names <- sapply(neighbors, function(u)
        paste(names(.Call(RHugin_clique_get_members, u)), collapse = ":"))

      for(neighbor in neighbor.names)
        if(!is.element(clique.name, edges(g)[[neighbor]]))
          g <- addEdge(neighbor, clique.name, g)
      }

      node.heights <- clique.sizes * line.height
      names(node.heights) <- clique.names
      nAttrs$height <- c(nAttrs$height, node.heights)

      node.labels <- rep("", n.cliques)
      names(node.labels) <- clique.names
      nAttrs$label <- c(nAttrs$label, node.labels)

      ## a bit of a hack here: the colors corresponding to evidence are passed
      ## thru nAttrs$color and the colors corresponding to category/kind are
      ## passed thru nAttrs$fillcolor

      node.colors <- character(0)
      for(i in 1:n.cliques) {
        colors <- rep("#00FF13", clique.sizes[[i]])
        node.ptrs <- .Call(RHugin_domain_get_node_by_name, x,
                           clique.members[[i]])
        for(j in 1:clique.sizes[[i]])
          if(.Call(RHugin_node_evidence_is_entered, node.ptrs[j]))
            colors[j] <- "#FF0000"
        node.colors <- c(node.colors, paste(colors, collapse = ":"))
      }
      names(node.colors) <- clique.names
      nAttrs$color <- c(nAttrs$color, node.colors)

      node.fillcolors <- character(0)
      for(i in 1:n.cliques) {
        colors <- rep("#FFFFC0", clique.sizes[[i]])
        node.ptrs <- .Call(RHugin_domain_get_node_by_name, x,
                           clique.members[[i]])
        for(j in 1:clique.sizes[[i]]) {
          if(.Call(RHugin_node_get_kind, node.ptrs[j]) == "continuous")
            colors[j] <- "#FFFF02"
          else if(.Call(RHugin_node_get_category, node.ptrs[j]) == "decision")
            colors[j] <- "#FFB1B2"
        }
        node.fillcolors <- c(node.fillcolors, paste(colors, collapse = ":"))
      }
      names(node.fillcolors) <- clique.names
      nAttrs$fillcolor <- c(nAttrs$fillcolor, node.fillcolors)
    }

    attrs <- list(node = list(shape = "rectangle", fixedsize = TRUE,
                              width = label.width),
                  graph = list(ratio = 1.0))

    nodeRenderFun <- function(node, ur, attrs, radConv) {
      nc <- getNodeCenter(node)
      l <- getX(nc) - getNodeLW(node)
      r <- getX(nc) + getNodeRW(node)
      b <- getY(nc) - getNodeHeight(node)/2
      t <- getY(nc) + getNodeHeight(node)/2
      jitter <- 30*par()$cin[1]
      rect(l, b, r, t)

      node.names <- strsplit(name(node), split = ":")[[1]]
      n.nodes <- length(node.names)
      node.colors <- strsplit(color(node), split = ":")[[1]]

      node.fillcolors <- strsplit(fillcolor(node), split = ":")[[1]]

      text.size <- 3.5*n.nodes / getNodeHeight(node)
      y <- b + (getNodeHeight(node) / (n.nodes + 1)) * (1:n.nodes)
      text(l+4*jitter, y, node.names, adj = c(0, 0.5), cex = text.size)
      points(rep(l + jitter, length(y)), y, pch = 16, cex = 1.5*text.size,
             col = node.colors)
      points(rep(l + jitter, length(y)), y, pch = 1, cex = 1.5*text.size)
      points(rep(l + 3*jitter, length(y)), y, pch = 15, cex = 1.5*text.size,
             col = node.fillcolors)
      points(rep(l + 3*jitter, length(y)), y, pch = 22, cex = 1.5*text.size)
    }

    g.layout <- agopen(g, name = "jt", nodeAttrs = nAttrs, attrs = attrs)
    plot(g.layout, drawNode = nodeRenderFun)
  }

  invisible(x)
}


