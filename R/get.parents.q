get.parents <- function(domain, node, type = "parents")
{
  node <- node[1]
  RHugin.check.args(domain, node, character(0), "get.parents")
  type <- match.arg(type,
                    c("parents", "requisite.parents", "requisite.ancestors"))

  node.ptr <- .Call(RHugin_domain_get_node_by_name, domain, node)

  if(type == "parents")
    names(.Call(RHugin_node_get_parents, node.ptr)[[node]])

  else {
    if(.Call(RHugin_node_get_category, node.ptr)[node] != "decision")
      stop(dQuote(node), " is not a decision node")

    if(type == "requisite.parents")
      names(.Call(RHugin_node_get_requisite_parents, node.ptr)[[node]])
    else
      names(.Call(RHugin_node_get_requisite_ancestors, node.ptr)[[node]])
  }  
}


