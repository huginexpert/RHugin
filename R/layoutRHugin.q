layoutRHugin <- function(x, domain, ...)
{
  nodes <- get.nodes(domain)
  n.nodes <- length(nodes)
  size <- .Call("RHugin_domain_get_node_size", domain, PACKAGE = "RHugin")
  RHugin.handle.error()

  if(abs(prod(size)) < 1e-3) {
    x <- layoutGraph(x)
    nodeX <- nodeRenderInfo(x)$nodeX
    nodeY <- nodeRenderInfo(x)$nodeY

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
  names(width) <- names(height) <- nodes
  names(nodeX) <- names(nodeY) <- nodes

  NRIx <- nodeRenderInfo(x)
  NRIx[["rWidth"]] <- NRIx[["lWidth"]] <- width
  NRIx[["height"]] <- height
  NRIx[["nodeX"]] <- NRIx[["labelX"]] <- nodeX
  NRIx[["nodeY"]] <- NRIx[["labelY"]] <- nodeY
  nodeRenderInfo(x) <- NRIx

  edge.list <- get.edges(domain)
  edges <- character(0)
  splines <- list()

  for(parent in nodes) {
    if(length(children <- edge.list[[parent]]$edges)) {
      for(child in children) {
        this.edge <- paste(parent, child, sep = "~")
        edges <- c(edges, this.edge)

        px <- nodeX[parent]
        py <- nodeY[parent]
        parent.shape <- NRIx$shape[parent]
        if(is.na(parent.shape))
          parent.shape <- "ellipse"

        cx <- nodeX[child]
        cy <- nodeY[child]
        child.shape <- NRIx$shape[child]
        if(is.na(child.shape))
          child.shape <- "ellipse"

        a <- width[1]
        b <- as.integer(ceiling(height[1] / 2))
        ac <- round(1.25 * a)
        bc <- round(1.25 * b)

        if(cx == px) {
          x1 <- x2 <- px
          y2 <- cy - ifelse(cy > py, bc, -bc)
          y1 <- py + ifelse(cy > py, b, -b)
        }

        else {
          m <- (cy - py) / (cx - px)

          if(parent.shape == "rectangle") {
            if(abs(m) < b/a) {
              x1 <- px + sign(cx - px) * a
              y1 <- py + m * sign(cx - px) * a
            }

            else {
              x1 <- (sign(cy - py) * b) / m + px
              y1 <- py + sign(cy - py) * b
            }
          }

          else {
            x1 <- px + sign(cx - px) * sqrt(1.0 / (1 / a^2 + m^2 / b^2))
            y1 <- py + m * (x1 - px)
          }

          if(child.shape == "rectangle") {
            if(abs(m) < b/a) {
              x2 <- cx + sign(px - cx) * ac
              y2 <- cy + m * sign(px - cx) * ac
            }

            else {
              x2 <- (sign(py - cy) * bc) / m + cx
              y2 <- cy + sign(py - cy) * bc
            }
          }

          else {
            x2 <- cx + sign(px - cx) * sqrt(1.0 / (1 / ac^2 + m^2 / bc^2))
            y2 <- cy + m * (x2 - cx)
          }
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

  ERIx <- edgeRenderInfo(x)
  ERIx[["splines"]] <- splines
  ERIx[["labelX"]] <- ERIx[["labelY"]] <- ERIx[["label"]] <- NAvec
  ERIx[["arrowhead"]] <- arrowhead
  ERIx[["arrowtail"]] <- arrowtail
  ERIx[["direction"]] <- direction
  edgeRenderInfo(x) <- ERIx

  boundingBox <- matrix(c(0, max(nodeX) + width[1] + 5, 0,
                          max(nodeY) + ceiling(height[1] / 2) + 5),
                        2, 2)

  gRIx <- graphRenderInfo(x)
  gRIx[["bbox"]] <- boundingBox
  gRIx[["laidout"]] <- TRUE
  gRIx[["recipEdges"]] <- "combined"
  graphRenderInfo(x) <- gRIx

  invisible(x)
}


