set.finding <- function(domain, node, finding, case = NULL)
{
  if(!is.null(case))
    return(invisible(.Call(RHugin_domain_enter_case, domain, case - 1)))

  node.ptr <- nodePointersFromNames(domain, node[1])
  category <- .Call(RHugin_node_get_category, node.ptr)
  kind <- .Call(RHugin_node_get_kind, node.ptr)
  subtype <- .Call(RHugin_node_get_subtype, node.ptr)

  if(kind == "discrete") {
    if(!is.element(category, c("chance", "decision")))
      stop(node, " is not a chance or decision node")

    states <- get.states(domain, node)

    if(length(finding) == 1) {
      state.index <- switch(subtype,
        "boolean" = ifelse(as.logical(finding), 1, 0),
        "labeled" = .Call(RHugin_node_get_state_index_from_label, node.ptr,
                          finding),
        "numbered" = .Call(RHugin_node_get_state_index_from_value, node.ptr,
                           finding),
        "interval" = .Call(RHugin_node_get_state_index_from_value, node.ptr,
                           finding),
        -1)

      if(state.index < 0)
        stop("unable to select state ", dQuote(finding), " in ", node)

      else
        .Call(RHugin_node_select_state, node.ptr, state.index)
    }
    
    else {
      if(length(finding) == length(states))
        .Call(RHugin_node_enter_finding, node.ptr, 0:(length(states) - 1),
              finding)

      else
        stop("the length of ", sQuote("finding"), " is not equal to the ",
             "number of states in ", node)
    }
  }

  if(kind == "continuous")
    .Call(RHugin_node_enter_value, node.ptr, finding[1])

  invisible()
}


