plot.RHuginDomain <- function(x, y, ...)
{
  if(!is.element("package:Rgraphviz", search()))
    stop("plotting an RHugin domain requires the Rgraphviz ",
         "package - please load Rgraphviz and try again")

  x <- layoutGraph(as.graph.RHuginDomain(x), layoutFun = layoutRHugin,
                   domain = x)

  graph.par(list(nodes = list(fill = "lightyellow", shape = "ellipse", lwd = 3),
                 edges = list(lwd = 2)))
  renderGraph(x)
  invisible(x)
}


