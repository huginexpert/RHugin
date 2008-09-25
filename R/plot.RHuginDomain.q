plot.RHuginDomain <- function(x, y, layoutType = c("dot", "neato", "fdp"), ...)
{
  layoutType <- match.arg(layoutType)

  if(!is.element("package:Rgraphviz", search()))
    stop("plotting an RHugin domain requires the Rgraphviz ",
         "package - please load Rgraphviz and try again") 

  x <- agopen(graph = as.graph(x), name = deparse(substitute(x)),
              layoutType = layoutType)
  plot(x, ...)
  invisible(x)
}


