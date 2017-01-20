get.parents <- function(domain, node, type = "parents")
{
  type <- match.arg(type, c("parents",
                            "requisite.parents",
                            "requisite.ancestors"))

  node <- node[1]
  node.ptr <- nodePointersFromNames(domain, node)

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


