set.states <- function(domain, node, states, subtype = "auto")
{
  subtype <- match.arg(subtype, choices = c("auto", RHUGIN.SUBTYPES))

  node.ptr <- nodePointersFromNames(domain, node[1])
  category <- .Call(RHugin_node_get_category, node.ptr)
  kind <- .Call(RHugin_node_get_kind, node.ptr)

  if(!is.element(category, c("chance", "decision")) || kind == "continuous")
    stop(dQuote(node[1]), " is not a discrete chance or decision node")

  if(subtype == "auto")
    subtype <- switch(class(states),
      "integer" = "numbered",
      "numeric" = "numbered",
      "logical" = "boolean",
      "character" = "labeled",
      stop("unable to automatically set node subtype")
    )

  switch(subtype,
    "boolean" = {
      .Call(RHugin_node_set_number_of_states, node.ptr, 2)
      .Call(RHugin_node_set_subtype, node.ptr, subtype)
    },

    "labeled" = {
      .Call(RHugin_node_set_subtype, node.ptr,subtype)
      .Call(RHugin_node_set_number_of_states, node.ptr, length(states))
      .Call(RHugin_node_set_state_label, node.ptr, 0:(length(states) - 1),
            states)
    },

    "numbered" = {
      .Call(RHugin_node_set_subtype, node.ptr, subtype)
      states <- as.double(states)

      if(any(is.na(states)))
        stop("non numeric states supplied for numbered node")

      .Call(RHugin_node_set_number_of_states, node.ptr, length(states))
      .Call(RHugin_node_set_state_value, node.ptr, 0:(length(states) - 1),
            states)
    },

    "interval" = {
      .Call(RHugin_node_set_subtype, node.ptr, subtype)

      states <- as.double(states)
      if(any(is.na(states)))
        stop("non numeric states supplied for interval node")

      if(!identical(states, sort(states)))
        stop("states are not disjoint intervals")

      .Call(RHugin_node_set_number_of_states, node.ptr, length(states) - 1)
      .Call(RHugin_node_set_state_value, node.ptr, 0:(length(states) - 1),
            states)
    }
  )

  invisible()
}


