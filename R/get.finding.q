get.finding <- function(domain, node, type = c("entered", "propagated"))
{
  type <- match.arg(type)

  node <- node[1]
  RHugin.check.args(domain, node, character(0), "get.finding")

  node.ptr <- .Call(RHugin_domain_get_node_by_name, domain, node[1])
  kind <- .Call(RHugin_node_get_kind, node.ptr)
  category <- .Call(RHugin_node_get_category, node.ptr)

  switch(kind,
    discrete = {
      if(category != "chance" && category != "decision")
        stop(node, " is not a discrete chance or decision node")
      states <- get.states(domain, node)
      finding <- switch(type,
        entered = .Call(RHugin_node_get_entered_finding, node.ptr,
                        0:(length(states) - 1)),
        propagated = .Call(RHugin_node_get_propagated_finding, node.ptr,
                            0:(length(states) - 1))
      )

      names(finding) <- states
      finding
    },

    continuous = {
      switch(type,
        entered = .Call(RHugin_node_get_entered_value, node.ptr),
        propagated = .Call(RHugin_node_get_propagated_value, node.ptr)
      )
    }
  )
}


