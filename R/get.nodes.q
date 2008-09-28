get.nodes <- function(domain)
{
  if(class(domain) != "RHuginDomain")
    stop("in ", sQuote("get.nodes"), " the first argument to ",
          sQuote("get.nodes"), " is not an RHugin domain",
          call. = FALSE)

  nodes <- character(0)
  node.ptr <- .Call("RHugin_domain_get_first_node", domain$pointer,
                     PACKAGE = "RHugin")
  RHugin.handle.error()

  while(!is.null(node.ptr)) {
    nodes <- c(.Call("RHugin_node_get_name", node.ptr, PACKAGE = "RHugin"),
                nodes)
    RHugin.handle.error()
    node.ptr <- .Call("RHugin_node_get_next", node.ptr, PACKAGE = "RHugin")
    RHugin.handle.error()
  }

  nodes
}


