summary.RHuginDomain <- function(object, nodes, ...)
{
  if(missing(nodes))
    nodes <- get.nodes(object)
  else
    nodes <- intersect(nodes, get.nodes(object))

  ans <- list()

  for(node in nodes) {
    node.ptr <- .Call("RHugin_domain_get_node_by_name", object, node,
                       PACKAGE = "RHugin")
    RHugin.handle.error()
    node.category <- .Call("RHugin_node_get_category", node.ptr,
                            PACKAGE = "RHugin")
    RHugin.handle.error()
    node.kind <- .Call("RHugin_node_get_kind", node.ptr, PACKAGE = "RHugin")
    RHugin.handle.error()

    if(node.kind == "discrete") {
      node.subtype <- .Call("RHugin_node_get_subtype", node.ptr,
                             PACKAGE = "RHugin")
      RHugin.handle.error()
      states <- get.states(object, node)
    }

    else {
      node.subtype <- NULL
      states <- NULL
    }

    ans[[node]] <- list(category = node.category, kind = node.kind,
                        subtype = node.subtype, states = states)
  }

  oldClass(ans) <- "summary.RHuginDomain"
  ans
}


