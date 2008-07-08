get.states <- function(domain, node)
{
  RHugin.check.args(domain, node, character(0), "get.states")

  node.ptr <- .Call("RHugin_domain_get_node_by_name", domain$pointer, node,
                     PACKAGE = "RHugin")
  RHugin.handle.error()

  if(!is.null(node.ptr)) {
    n.states <- .Call("RHugin_node_get_number_of_states", node.ptr,
                       PACKAGE = "RHugin")
    RHugin.handle.error()

    subtype <- summary(domain, node)[[node]]$subtype
    states <- switch(subtype,
      "labeled" = .Call("RHugin_node_get_state_label", node.ptr,
                         as.integer(0:(n.states - 1)), PACKAGE = "RHugin"),

      "boolean" = c(FALSE, TRUE),

      "numbered" = .Call("RHugin_node_get_state_value", node.ptr,
                          as.integer(0:(n.states - 1)), PACKAGE = "RHugin"),

      "interval" = .Call("RHugin_node_get_state_value", node.ptr,
                          as.integer(0:(n.states - 1)), PACKAGE = "RHugin")
    )
    RHugin.handle.error()
  }

  else
    states <- NULL

  states
}


