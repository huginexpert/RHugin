get.requisites <- function(domain, node, depth = c("parents", "ancestors"))
{
  node <- node[1]
  RHugin.check.args(domain, node, character(0), "get.requisites")
  depth <- match.arg(depth)

  node.ptr <- .Call(RHugin_domain_get_node_by_name, domain, node)

  if(.Call(RHugin_node_get_category, node.ptr)[node] != "decision")
    stop(dQuote(node), " is not a decision node")

  if(depth == "parents")
    names(.Call(RHugin_node_get_requisite_parents, node.ptr)[[node]])
  else
    names(.Call(RHugin_node_get_requisite_ancestors, node.ptr)[[node]])
}


