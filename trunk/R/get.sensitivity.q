get.sensitivity <- function(domain, output, state, ..., set = FALSE)
{
  RHugin.check.args(domain, output, character(0), "get.sensitvity")

  output.states <- get.states(domain, output)
  state <- match(state, output.states, nomatch = NA)[1]

  if(is.na(state))
    stop(dQuote(state), " is not a state of node ", dQuote(output))
  else
    state <- state - 1

  node.ptr <- .Call("RHugin_domain_get_node_by_name",
                     domain, as.character(output), PACKAGE = "RHugin")
  RHugin.handle.error()

  status <- .Call("RHugin_node_compute_sensitivity_data", node.ptr,
                   as.integer(state), PACKAGE = "RHugin")
  RHugin.handle.error(status)

  if(set) {
    set <- .Call("RHugin_domain_get_sensitivity_set", domain,
                  PACKAGE = "RHugin")
    return(names(set))
  }

  dots <- list(...)

  if(!length(dots))
    return(invisible(NULL))

  if(is.list(dots[[1]])) 
    dots <- dots[[1]]

  constants <- matrix(as.double(NA), length(dots), 4)
  dimnames(constants) <- list(paste(names(dots), unlist(dots), sep = ":"),
                              c("alpha", "beta", "gamma", "delta"))

  for(i in 1:length(dots)) {

    node.ptr <- .Call("RHugin_domain_get_node_by_name", domain,
                       as.character(names(dots[i])), PACKAGE = "RHugin")
    RHugin.handle.error()

    node.states <- get.states(domain, names(dots[i]))
    input <- match(dots[[i]], node.states, nomatch = NA)[1]

    if(is.na(input))
      stop(dQuote(dots[[i]]), " is not a state of node ",
           dQuote(names(dots[i])))
    else
      input <- input - 1

    temp <- .Call("RHugin_node_get_sensitivity_constants", node.ptr,
                   as.integer(input), PACKAGE = "RHugin")

    if(error.code() == 0)
      constants[i, ] <- temp
  }

  constants
}


