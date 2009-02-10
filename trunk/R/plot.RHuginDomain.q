plot.RHuginDomain <- function(x, y, ...)
{
  if(!is.element("package:Rgraphviz", search()))
    stop("plotting an RHugin domain requires the Rgraphviz ",
         "package - please load Rgraphviz and try again")

  x <- layoutGraph(as.graph(x))

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

  width <- ifelse(size[1] %% 2, (size[1] + 1) / 2, size[1] / 2)
  width <- rep(width, n.nodes)
  height <- rep(size[2], n.nodes)
  names(width) <- names(height) <- nodes

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

  nodeRenderInfo <- list(rWidth = width, lWidth = width, height = height,
                         nodeX = nodeX, nodeY = nodeY, labelX = nodeX,
                         labelY = nodeY, label = nodes)

  edge.list <- get.edges(domain)
  edges <- character(0)
  splines <- list()

  for(node in nodes) {
    if(length(tmp <- edge.list[[node]]$edges)) {
      for(e in tmp) {
        this.edge <- paste(node, e, sep = "~")
        edges <- c(edges, this.edge)
        Pzero <- new("xyPoint", x = nodeX[node], y = nodeY[node])
        Pone <- new("xyPoint", x = nodeX[e], y = nodeY[e])
        temp <- list(new("BezierCurve", cPoints = list(Pzero, Pone)))
        splines <- c(splines, list(temp))
      }
      
    }
  }

  names(splines) <- edges


  browser()

  FALSE
}


