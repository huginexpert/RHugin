get.edges <- function(domain)
{
  RHugin.check.args(domain, character(0), character(0), "get.nodes")

  edges <- character(0)
  node.ptr <- .Call("RHugin_domain_get_first_node", domain$pointer,
                     PACKAGE = "RHugin")
  RHugin.handle.error()

  while(!is.null(node.ptr)) {
    node <- .Call("RHugin_node_get_name", node.ptr, PACKAGE = "RHugin")
    RHugin.handle.error()
    children <- names(.Call("RHugin_node_get_children", node.ptr,
                             PACKAGE = "RHugin"))
    RHugin.handle.error()
    if(length(children))
      edges <- c(edges, paste(node, children, sep = " -> "))
    node.ptr <- .Call("RHugin_node_get_next", node.ptr, PACKAGE = "RHugin")
    RHugin.handle.error()
  }

  edges
}


