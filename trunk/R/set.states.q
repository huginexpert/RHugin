set.states <- function(domain, node, states, subtype = "auto")
{
  RHugin.check.args(domain, node, character(0), "set.states")
  subtypes <- c("auto", "labeled", "boolean", "numbered", "interval")
  subtype <- match.arg(subtype, choices = subtypes)

  node.ptr <- .Call("RHugin_domain_get_node_by_name", domain, node[1],
                     PACKAGE = "RHugin")

  category <- .Call("RHugin_node_get_category", node.ptr, PACKAGE = "RHugin")
  kind <- .Call("RHugin_node_get_kind", node.ptr, PACKAGE = "RHugin")

  if(!is.element(category, c("chance", "decision")) || kind == "continuous")
    stop(node, " is not a discrete chance or decision node")

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
      .Call("RHugin_node_set_number_of_states", node.ptr, 2, PACKAGE = "RHugin")
      .Call("RHugin_node_set_subtype", node.ptr, subtype, PACKAGE = "RHugin")
    },

    "labeled" = {
      .Call("RHugin_node_set_subtype", node.ptr,subtype, PACKAGE = "RHugin")
      .Call("RHugin_node_set_number_of_states", node.ptr, length(states),
             PACKAGE = "RHugin")
      .Call("RHugin_node_set_state_label", node.ptr, 0:(length(states) - 1),
             states, PACKAGE = "RHugin")
    },

    "numbered" = {
      .Call("RHugin_node_set_subtype", node.ptr, subtype, PACKAGE = "RHugin")
      states <- as.double(states)

      if(any(is.na(states)))
        stop("non numeric states supplied for numbered node")

      .Call("RHugin_node_set_number_of_states", node.ptr, length(states),
             PACKAGE = "RHugin")
      .Call("RHugin_node_set_state_value", node.ptr, 0:(length(states) - 1),
             states, PACKAGE = "RHugin")
    },

    "interval" = {
      .Call("RHugin_node_set_subtype", node.ptr, subtype, PACKAGE = "RHugin")

      states <- as.double(states)
      if(any(is.na(states)))
        stop("non numeric states supplied for interval node")

      if(!identical(states, sort(states)))
        stop("states are not disjoint intervals")

      .Call("RHugin_node_set_number_of_states", node.ptr, length(states) - 1,
             PACKAGE = "RHugin")
      .Call("RHugin_node_set_state_value", node.ptr, 0:(length(states) - 1),
             states, PACKAGE = "RHugin")
    }
  )

  invisible()
}


