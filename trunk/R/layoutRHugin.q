layoutRHugin <- function(x, domain, ...)
{
  nodes <- get.nodes(domain)
  n.nodes <- length(nodes)
  size <- .Call("RHugin_domain_get_node_size", domain, PACKAGE = "RHugin")
  RHugin.handle.error()

  if(all(size == 0)) {
    x <- layoutGraph(x)
    nodeX <- x@renderInfo@nodes$nodeX
    nodeY <- x@renderInfo@nodes$nodeY

    for(node in nodes) {
      node.ptr <- .Call("RHugin_domain_get_node_by_name", domain, node,
                         PACKAGE = "RHugin")
      RHugin.handle.error()
      .Call("RHugin_node_set_position", node.ptr,
             as.integer(c(nodeX[node], nodeY[node])),
             PACKAGE = "RHugin")
      RHugin.handle.error()
    }

    return(x)
  }

  nodeX <- nodeY <- rep(0, n.nodes)

  for(i in 1:n.nodes) {
    node.ptr <- .Call("RHugin_domain_get_node_by_name", domain, nodes[i],
                       PACKAGE = "RHugin")
    RHugin.handle.error()
    position <- .Call("RHugin_node_get_position", node.ptr, PACKAGE = "RHugin")
    RHugin.handle.error()
    nodeX[i] <- position[1]
    nodeY[i] <- position[2]
  }

  width <- rep(as.integer(ceiling(size[1] / 2)), n.nodes)
  height <- rep(as.integer(size[2]), n.nodes)
  nodeX <- as.integer(nodeX + width[1] + 5)
  nodeY <- as.integer(nodeY + ceiling(height[1] / 2) + 5)
  #shape <- rep("ellipse", n.nodes)
  #names(width) <- names(height) <- names(shape) <- nodes
  names(width) <- names(height) <- nodes
  names(nodeX) <- names(nodeY) <- nodes

  #nodeRenderInfo <- list(rWidth = width, lWidth = width, height = height,
  #                       nodeX = nodeX, nodeY = nodeY, labelX = nodeX,
  #                       labelY = nodeY, shape = shape, label = nodes)

  nodeRenderInfo <- list(rWidth = width, lWidth = width, height = height,
                         nodeX = nodeX, nodeY = nodeY, labelX = nodeX,
                         labelY = nodeY, label = nodes)

  edge.list <- get.edges(domain)
  edges <- character(0)
  splines <- list()

  for(parent in nodes) {
    if(length(children <- edge.list[[parent]]$edges)) {
      for(child in children) {
        this.edge <- paste(parent, child, sep = "~")
        edges <- c(edges, this.edge)

        h1 <- nodeX[parent]
        k1 <- nodeY[parent]
        h2 <- nodeX[child]
        k2 <- nodeY[child]
        a <- width[1]
        b <- as.integer(ceiling(height[1] / 2))

        if(h2 == h1) {
          if(k2 > k1) {
            x1 <- x2 <- h1
            y2 <- k2 - b
            y1 <- k1 + b
          }
          else {
            x1 <- x2 <- h1
            y2 <- k2 + b
            y1 <- k1 - b
          }
        }
        else {
          m <- (k2 - k1) / (h2 - h1)
          x1 <- h1 + sign(h2 - h1) * sqrt(1.0 / (1 / a^2 + m^2 / b^2))
          y1 <- k1 + m * (x1 - h1)
          x2 <- h2 + sign(h1 - h2) * sqrt(1.0 / (1 / a^2 + m^2 / b^2))
          y2 <- k2 + m * (x2 - h2)
        }

        h <- new("xyPoint", x = as.integer(x1), y = as.integer(y1))
        k <- new("xyPoint", x = as.integer(x2), y = as.integer(y2))
        splines[[this.edge]] <- list(new("BezierCurve", cPoints = list(h, k)))
      }
    }
  }

  n.edges <- length(edges)
  names(splines) <- edges
  NAvec <- rep(NA, n.edges)
  names(NAvec) <- edges
  arrowhead <- rep("open", n.edges)
  arrowtail <- rep("none", n.edges)
  direction <- rep("forward", n.edges)
  names(arrowhead) <- names(arrowtail) <- names(direction) <- edges

  edgeRenderInfo <- list(splines = splines, labelX = NAvec, labelY = NAvec,
                         label = NAvec, arrowhead = arrowhead,
                         arrowtail = arrowtail, direction = direction)

  boundingBox <- matrix(c(0, max(nodeX) + width[1] + 5, 0,
                          max(nodeY) + ceiling(height[1] / 2) + 5),
                        2, 2)

  graph <- list(bbox = boundingBox, laidout = TRUE, recipEdges = "combined")

  x@renderInfo <- new("renderInfo", nodes = nodeRenderInfo,
                       edges = edgeRenderInfo, graph = graph)

  invisible(x)
}


