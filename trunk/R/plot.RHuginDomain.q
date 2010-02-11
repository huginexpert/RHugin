plot.RHuginDomain <- function(x, y, ...)
{
  if(!require(Rgraphviz))
    stop("plotting an RHugin domain requires the Rgraphviz package")

  nodes <- get.nodes(x)
  node.ptrs <- .Call("RHugin_domain_get_node_by_name", x, as.character(nodes),
                      PACKAGE = "RHugin")
  categories <- .Call("RHugin_node_get_category", node.ptrs, PACKAGE = "RHugin")
  kinds <- .Call("RHugin_node_get_kind", node.ptrs, PACKAGE = "RHugin")

  fill <- character(length(nodes))
  shape <- character(length(nodes))
  names(fill) <- names(shape) <- nodes

  for(node in nodes) {
    if(categories[node] == "decision") {
      fill[node] <- "red"
      shape[node] <- "rectangle"
    }
    else if(categories[node] == "utility") {
      fill[node] <- "green"
      ## diamond not yet supported by Rgraphviz ##
      #shape[node] <- "diamond"
      shape[node] <- "rectangle"
    }
    else {
      if(kinds[node] == "discrete")
      {
        fill[node] <- "yellow"
        shape[node] <- "ellipse"
      }
      else {
        fill[node] <- "orange"
        shape[node] <- "ellipse"
      }
    }
  }

  gx <- as.graph.RHuginDomain(x)
  nodeRenderInfo(gx) <- list(fill = fill, shape = shape, lwd = 3)
  edgeRenderInfo(gx) <- list(lwd = 2)
  gx <- layoutGraph(gx, layoutFun = layoutRHugin, domain = x)
  renderGraph(gx)

  invisible(gx)
}


