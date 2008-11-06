get.entropy <- function(domain, node, other = NULL)
{
  RHugin.check.args(domain, c(node, other), character(0), "get.entropy")

  if(is.null(other)) {
    entropy <- double(length(node))

    for(i in 1:length(node)) {
      node.ptr <- .Call("RHugin_domain_get_node_by_name", domain,
                         as.character(node[i]), PACKAGE = "RHugin")
      entropy[i] <- .Call("RHugin_node_get_entropy", node.ptr,
                           PACKAGE = "RHugin")
    }

    names(entropy) <- node
  }

  else {
    if(length(node) != length(other))
      stop(sQuote("node"), " and ", sQuote("other"), " are not the same length")

    entropy <- double(length(node))

    for(i in 1:length(node)) {
      node.ptr <- .Call("RHugin_domain_get_node_by_name", domain,
                         as.character(node[i]), PACKAGE = "RHugin")
      other.ptr <- .Call("RHugin_domain_get_node_by_name", domain,
                         as.character(other[i]), PACKAGE = "RHugin")
      entropy[i] <- .Call("RHugin_node_get_mutual_information", node.ptr,
                           other.ptr, PACKAGE = "RHugin")
    }

    names(entropy) <- paste(node, other, sep = "~")
  }

  entropy
}


