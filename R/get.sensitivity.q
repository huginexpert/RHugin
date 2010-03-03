get.sensitivity <- function(domain, output, state, ..., set = FALSE)
{
  RHugin.check.args(domain, output, character(0), "get.sensitvity")

  output.states <- get.states(domain, output)
  state <- match(state, output.states, nomatch = NA)[1]

  if(is.na(state))
    stop(dQuote(state), " is not a state of node ", dQuote(output))
  else
    state <- state - 1

  node.ptr <- .Call("RHugin_domain_get_node_by_name", domain, output,
                     PACKAGE = "RHugin")

  .Call("RHugin_node_compute_sensitivity_data", node.ptr, state,
         PACKAGE = "RHugin")

  if(set) {
    set <- .Call("RHugin_domain_get_sensitivity_set", domain,
                  PACKAGE = "RHugin")
    return(names(set))
  }

  dots <- list(...)

  if(!length(dots))
    return(invisible())

  if(is.list(dots[[1]])) 
    dots <- dots[[1]]

  nodes <- names(dots)
  constants <- matrix(as.double(NA), length(dots), 4)
  dimnames(constants) <- list(paste(nodes, unlist(dots), sep = ":"),
                              c("alpha", "beta", "gamma", "delta"))

  node.ptrs <- .Call("RHugin_domain_get_node_by_name", domain, nodes,
                      PACKAGE = "RHugin")

  for(i in 1:length(dots)) {
    node.states <- get.states(domain, nodes[i])
    input <- match(dots[[i]], node.states, nomatch = NA)[1]

    if(is.na(input))
      stop(dots[[i]], " is not a state of node ", nodes[i])
    else
      input <- input - 1

    constants[i, ] <- .Call("RHugin_node_get_sensitivity_constants",
                             node.ptrs[nodes[i]], input, PACKAGE = "RHugin")
  }

  constants
}


