plot.RHuginDomain <- function(x, y, ...)
{
  if(!is.element("package:Rgraphviz", search()))
    stop("plotting an RHugin domain requires the Rgraphviz ",
         "package - please load Rgraphviz and try again")

  x <- layoutGraph(as.graph(x), layoutFun = layoutRHugin, domain = x)

  renderGraph(x)
  invisible(x)
}


layoutRHugin <- function(x, domain, ...)
{
  nodes <- get.nodes(domain)
  n.nodes <- length(nodes)
  size <- .Call("RHugin_domain_get_node_size", domain, PACKAGE = "RHugin")
  RHugin.handle.error()

  if(all(size == 0))
    return(layoutGraph(x, ...))

  nodeX <- nodeY <- rep(0, n.nodes)
  names(nodeX) <- names(nodeY) <- nodes

  for(i in 1:n.nodes) {
    node.ptr <- .Call("RHugin_domain_get_node_by_name", domain, nodes[i],
                       PACKAGE = "RHugin")
    RHugin.handle.error()
    position <- .Call("RHugin_node_get_position", node.ptr)
    RHugin.handle.error()
    nodeX[i] <- position[1]
    nodeY[i] <- position[2]
  }

  width <- as.integer(ceiling(size[1] / 2))
  height <- as.integer(size[2])
  nodeX <- as.integer(nodeX + width + 5)
  nodeY <- as.integer(nodeY + ceiling(height / 2) + 5)
  width <- rep(width, n.nodes)
  height <- rep(height, n.nodes)
  shape <- rep("ellipse", n.nodes)
  names(width) <- names(height) <- names(shape) <- nodes
  names(nodeX) <- names(nodeY) <- nodes

  nodeRenderInfo <- list(rWidth = width, lWidth = width, height = height,
                         nodeX = nodeX, nodeY = nodeY, labelX = nodeX,
                         labelY = nodeY, shape = shape, label = nodes)

  edge.list <- get.edges(domain)
  edges <- character(0)
  enamesFrom <- character(0)
  enamesTo <- character(0)
  splines <- list()

  for(node in nodes) {
    if(length(tmp <- edge.list[[node]]$edges)) {
      for(e in tmp) {
        enamesFrom <- c(enamesFrom, node)
        enamesTo <- c(enamesFrom, e)
        this.edge <- paste(node, e, sep = "~")
        edges <- c(edges, this.edge)
        Pzero <- new("xyPoint", x = nodeX[node], y = nodeY[node])
        Pone <- new("xyPoint", x = nodeX[e], y = nodeY[e])
        temp <- list(computeEndPoints(nodeX[node], nodeY[node], nodeX[e], nodeY[e], width[1], as.integer(ceiling(height[1] / 2))))
        splines <- c(splines, list(temp))
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

  edgeRenderInfo <- list(enamesFrom = enamesFrom, enamesTo = enamesTo,
                         splines = splines, labelX = NAvec, labelY = NAvec,
                         label = NAvec, arrowhead = arrowhead,
                         arrowtail = arrowtail, direction = direction)

  boundingBox <- matrix(c(0, max(nodeX) + width[1] + 5, 0,
                          max(nodeY) + ceiling(height[1] / 2) + 5),
                        2, 2)

  graph <- list(bbox = boundingBox, laidout = TRUE, recipEdges = "combined")

  x@renderInfo <- new("renderInfo", nodes = nodeRenderInfo,
                       edges = edgeRenderInfo, graph = graph)

  x
}


computeEndPoints <- function(h1, k1, h2, k2, a, b)
{
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
  new("BezierCurve", cPoints = list(h, k))
}




