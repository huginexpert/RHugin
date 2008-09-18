position.nodes <- function(domain, nodes = NULL, layoutType = c("dot", "neato",
                           "fdp", "manual", "none"), x, y)
{
  if(!is.element("package:Rgraphviz", search()))
    stop("the ", sQuote("position.nodes"), " function requires the Rgraphviz ",
         "package - please load Rgraphviz and try again") 

  RHugin.check.args(domain, nodes, character(0), "position.nodes")
  layoutType <- match.arg(layoutType)

  if(is.null(nodes))
    nodes <- get.nodes(domain)

  n <- length(nodes)

  if(layoutType != "none") {
    if(layoutType != "manual") {
      rgv.layout <- agopen(graph = as.graph(domain),
                           name = deparse(substitute(domain)),
                           layoutType = layoutType)
      X <- getNodeXY(rgv.layout)
      X <- cbind(X$x, X$y)
    }
    else {
      if(length(x) != n || length(y) != n)
        stop("the lengths of ", sQuote("x"), " and ", sQuote("y"),
             " are not the same as the length of ", sQuote("nodes"))
      X <- cbind(x, y)
    }

    for(i in 1:n) {
      node.ptr <- .Call("RHugin_domain_get_node_by_name", domain$pointer,
                         nodes[i], PACKAGE = "RHugin")
      RHugin.handle.error()
      .Call("RHugin_node_set_position", node.ptr, as.integer(X[i, ]),
             PACKAGE = "RHugin")
      RHugin.handle.error()
    }
  }

  nodes <- get.nodes(domain)
  n <- length(nodes)
  position <- matrix(0, length(nodes), 2)
  dimnames(position) <- list(nodes, c("x", "y"))

  for(i in 1:n) {
    node.ptr <- .Call("RHugin_domain_get_node_by_name", domain$pointer,
                       nodes[i], PACKAGE = "RHugin")
    RHugin.handle.error()
    position[i, ] <- .Call("RHugin_node_get_position", node.ptr,
                            PACKAGE = "RHugin")
  }

  position
}


