get.model <- function(domain, node, model.nodes)
{
  node <- node[1]
  if(missing(model.nodes))
    model.nodes <- character(0)

  node.ptr <- .Call(RHugin_domain_get_node_by_name, domain, node)
  model.ptr <- .Call(RHugin_node_get_model, node.ptr)

  if(is.null(model.ptr[[node]])) {
    mn.ptrs <- .Call(RHugin_domain_get_node_by_name, domain, model.nodes)
    model.ptr <- .Call(RHugin_node_new_model, node.ptr, mn.ptrs)
  }

  model.nodes <- names(.Call(RHugin_model_get_nodes, model.ptr))
  expressions <- .Call(RHugin_model_get_expression, model.ptr)

  if(length(model.nodes)) {
    states <- lapply(model.nodes, function(u) get.states(domain, u))
    names(states) <- model.nodes
    states <- rev(states)

    model <- cbind(expand.grid(states), Expression = expressions, stringsAsFactors = FALSE)
  }

  else
    model <- data.frame(Expression = expressions, stringsAsFactors = FALSE)

  oldClass(model) <- c("RHugin.model", "data.frame")
  attr(model, "header") <- paste("Model for node ", node, ":\n", sep = "")

  model
}


