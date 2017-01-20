get.entropy <- function(domain, node, other = NULL)
{
  if(is.null(other)) {
    node.ptrs <- nodePointersFromNames(domain, node)
    ans <- .Call(RHugin_node_get_entropy, node.ptrs)
    names(ans) <- node
  }

  else {
    if(length(node) != length(other))
      stop(sQuote("node"), " and ", sQuote("other"), " are not the same length")

    node.ptrs <- nodePointersFromNames(domain, node)
    other.ptrs <- nodePointersFromNames(domain, other)
    ans <- .Call(RHugin_node_get_mutual_information, node.ptrs, other.ptrs)

    names(ans) <- paste(node, other, sep = "~")
  }

  ans
}


