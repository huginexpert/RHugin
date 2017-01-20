nodePointersFromNames <- function(domain, nodes)
{
  node.ptrs <- .Call(RHugin_domain_get_node_by_name, domain, nodes)
  null.nodes <- sapply(node.ptrs, is.null)

  if(any(null.nodes)) {
    null.nodes <- which(null.nodes)
    m <- paste("node", dQuote(nodes[null.nodes[1]]), "not found", collapse = "")
    se <- simpleError(m, call = sys.call(1))
    stop(se)
  }

  node.ptrs
}


