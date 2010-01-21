set.finding <- function(domain, node, finding, case = NULL)
{
  if(!is.null(case)) {
    RHugin.check.args(domain, character(0), character(0), "set.finding")

    status <- .Call("RHugin_domain_enter_case", domain, as.integer(case - 1),
                     PACKAGE = "RHugin")
    RHugin.handle.error(status)
    return(invisible(NULL))
  }

  RHugin.check.args(domain, node, character(0), "set.finding")

  node.ptr <- .Call("RHugin_domain_get_node_by_name", domain,
                      as.character(node[1]), PACKAGE = "RHugin")
  category <- .Call("RHugin_node_get_category", node.ptr, PACKAGE = "RHugin")
  kind <- .Call("RHugin_node_get_kind", node.ptr, PACKAGE = "RHugin")
  subtype <- .Call("RHugin_node_get_subtype", node.ptr, PACKAGE = "RHugin")

  if(kind == "discrete") {
    if(category != "chance" && category != "decision")
      stop(dQuote(node), " is not a discrete chance or decision node")

    states <- get.states(domain, node)

    if(length(finding) == 1) {
      state.index <- switch(subtype,
        "boolean" = ifelse(as.logical(finding), 1, 0),
        "labeled" = .Call("RHugin_node_get_state_index_from_label", node.ptr,
                           as.character(finding), PACKAGE = "RHugin"),
        "numbered" = .Call("RHugin_node_get_state_index_from_value", node.ptr,
                            as.double(finding), PACKAGE = "RHugin"),
        "interval" = .Call("RHugin_node_get_state_index_from_value", node.ptr,
                            as.double(finding), PACKAGE = "RHugin"),
        -1)

      if(state.index < 0)
        stop("unable to select state ", dQuote(finding), " in node ",
              dQuote(node))

      else
        status <- .Call("RHugin_node_select_state", node.ptr,
                         as.integer(state.index), PACKAGE = "RHugin")
    }
    
    else {
      if(length(finding) == length(states))
        status <- .Call("RHugin_node_enter_finding", node.ptr,
                         as.integer(0:(length(states) - 1)), as.double(finding),
                         PACKAGE = "RHugin")

      else
        stop("the length of ", sQuote("finding"), " is not equal to the number ",
             "of states in node ", dQuote(node))
    }

    RHugin.handle.error(status)
  }

  if(kind == "continuous") {
    status <- .Call("RHugin_node_enter_value", node.ptr, as.double(finding[1]),
                     PACKAGE = "RHugin")
    RHugin.handle.error(status)
  }

  invisible(NULL)
}


