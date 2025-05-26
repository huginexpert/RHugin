nodePointersFromNames <- function(domain, nodes)
{
  domainOrClass <- .Call(isDomainOrClass, domain)
  if(domainOrClass == 0) # Domain
    node.ptrs <- .Call(RHugin_domain_get_node_by_name, domain, nodes)
  else if (domainOrClass == 1) # Class
  {
    node.ptrs <- .Call(RHugin_class_get_node_by_name, domain, nodes)
  }
  else
    stop("cannot get nodes from something that is neither a domain nor class")
  
  null.nodes <- sapply(node.ptrs, is.null)

  if(any(null.nodes)) {
    null.nodes <- which(null.nodes)
    m <- paste("node", dQuote(nodes[null.nodes[1]]), "not found", collapse = "")
    se <- simpleError(m, call = sys.call(1))
    stop(se)
  }

  node.ptrs
}


