get.finding <- function(domain, node)
{
  RHugin.check.args(domain, node, character(0), "get.finding")

  node.ptr <- .Call("RHugin_domain_get_node_by_name", domain,
                     as.character(node[1]), PACKAGE = "RHugin")
  kind <- .Call("RHugin_node_get_kind", node.ptr, PACKAGE = "RHugin")
  category <- .Call("RHugin_node_get_category", node.ptr, PACKAGE = "RHugin")

  if(kind == "discrete") {
    if(category != "chance" && category != "decision")
      stop(node, " is not a discrete chance or decision node")
    states <- get.states(domain, node)
    finding <- .Call("RHugin_node_get_entered_finding", node.ptr,
                      as.integer(0:(length(states) - 1)), PACKAGE = "RHugin")
    RHugin.handle.error()
    names(finding) <- states
  }

  if(kind == "continuous") {
    finding <- .Call("RHugin_node_get_entered_value", node.ptr,
                      PACKAGE = "RHugin")
    RHugin.handle.error()
  }

  finding
}


