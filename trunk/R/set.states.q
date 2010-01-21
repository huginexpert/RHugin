set.states <- function(domain, node, states, subtype = c("auto", "labeled",
                      "boolean", "numbered", "interval"))
{
  RHugin.check.args(domain, node, character(0), "set.states")
  subtype <- match.arg(subtype)

  node.ptr <- .Call("RHugin_domain_get_node_by_name", domain,
                     as.character(node[1]), PACKAGE = "RHugin")

  category <- .Call("RHugin_node_get_category", node.ptr, PACKAGE = "RHugin")

  if(category != "chance" && category != "decision") {
    warning("this function has no effect on ", category, " nodes")
    return(invisible(NULL))
  }

  kind <- .Call("RHugin_node_get_kind", node.ptr, PACKAGE = "RHugin")

  if(kind == "continuous") {
    warning("this function has no effect on continuous nodes")
    return(invisible(NULL))
  }

  if(subtype == "auto")
    subtype <- switch(class(states),
      "integer" = "numbered",
      "numeric" = "numbered",
      "logical" = "boolean",
      "character" = "labeled",
      stop("unable to automatically set node subtype")
    )

  status <- switch(subtype,
    "boolean" = {
      status <- .Call("RHugin_node_set_number_of_states", node.ptr,
                       as.integer(2), PACKAGE = "RHugin")
      RHugin.handle.error(status)

      status <- .Call("RHugin_node_set_subtype", node.ptr,
                       as.character(subtype), PACKAGE = "RHugin")
      RHugin.handle.error(status)
    },

    "labeled" = {
      status <- .Call("RHugin_node_set_subtype", node.ptr,
                       as.character(subtype), PACKAGE = "RHugin")
      RHugin.handle.error(status)

      status <- .Call("RHugin_node_set_number_of_states", node.ptr,
                       as.integer(length(states)), PACKAGE = "RHugin")
      RHugin.handle.error(status)

      .Call("RHugin_node_set_state_label", node.ptr,
             as.integer(0:(length(states) - 1)), as.character(states),
             PACKAGE = "RHugin")
    },

    "numbered" = {
      status <- .Call("RHugin_node_set_subtype", node.ptr,
                       as.character(subtype), PACKAGE = "RHugin")
      RHugin.handle.error(status)

      states <- as.double(states)
      if(any(is.na(states)))
        stop("non numeric states supplied for numbered node")

      status <- .Call("RHugin_node_set_number_of_states", node.ptr,
                       as.integer(length(states)), PACKAGE = "RHugin")
      RHugin.handle.error(status)

      .Call("RHugin_node_set_state_value", node.ptr,
             as.integer(0:(length(states) - 1)), as.double(states),
             PACKAGE = "RHugin")
    },

    "interval" = {
      status <- .Call("RHugin_node_set_subtype", node.ptr,
                       as.character(subtype), PACKAGE = "RHugin")
      RHugin.handle.error(status)

      states <- as.double(states)
      if(any(is.na(states)))
        stop("non numeric states supplied for interval node")
      if(!identical(states, sort(states)))
        stop("states are not disjoint intervals")

      status <- .Call("RHugin_node_set_number_of_states", node.ptr,
                       as.integer(length(states) - 1), PACKAGE = "RHugin")
      RHugin.handle.error(status)

      .Call("RHugin_node_set_state_value", node.ptr,
             as.integer(0:(length(states) - 1)), as.double(states),
             PACKAGE = "RHugin")
    }
  )
  RHugin.handle.error(status)

  invisible(NULL)
}


