plot.RHuginDomain <- function(x, y, ...)
{
  if(!is.element("package:Rgraphviz", search()))
    stop("plotting an RHugin domain requires the Rgraphviz ",
         "package - please load Rgraphviz and try again")

  gx <- as.graph.RHuginDomain(x)
  nodeRenderInfo(gx) <- list(fill = "lightyellow", shape = "ellipse", lwd = 3)
  edgeRenderInfo(gx) <- list(lwd = 2)
  x <- layoutGraph(gx, layoutFun = layoutRHugin, domain = x)

  renderGraph(x)
  invisible(x)
}


