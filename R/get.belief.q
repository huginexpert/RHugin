get.belief <- function(domain, node)
{
  node.ptr <- nodePointersFromNames(domain, node[1])
  kind <- .Call(RHugin_node_get_kind, node.ptr)

  belief <- NULL

  if(kind == "discrete") {
    states <- get.states(domain, node)
    states.idx <- 0:(length(states) - 1)
    belief <- .Call(RHugin_node_get_belief, node.ptr, states.idx)
    names(belief) <- states
  }

  if(kind == "continuous") {
    mean <- .Call(RHugin_node_get_mean, node.ptr)
    variance <- .Call(RHugin_node_get_variance, node.ptr)
    belief <- c("(Mean)" = mean, "(Variance)" = variance)
  }

  belief
}


