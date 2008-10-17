get.finding <- function(domain, node)
{
  RHugin.check.args(domain, node, character(0), "get.finding")

  node.summary <- summary(domain, node)[[node]]
  category <- node.summary$category
  kind <- node.summary$kind
  states <- get.states(domain, node)

  if(kind != "discrete" || (category != "chance" && category != "decision"))
    stop(dQuote(node), " is not a discrete chance or decision node")

  node.ptr <- .Call("RHugin_domain_get_node_by_name", domain,
                     as.character(node), PACKAGE = "RHugin")

  finding <- .Call("RHugin_node_get_entered_finding", node.ptr,
                    as.integer(0:(length(states) - 1)), PACKAGE = "RHugin")

  names(finding) <- states
  finding
}


