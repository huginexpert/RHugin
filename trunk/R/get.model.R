get.model <- function(domain, node, model.nodes)
{
  node.ptr <- nodePointersFromNames(domain, node[1])
  model.ptr <- .Call(RHugin_node_get_model, node.ptr)

  if(missing(model.nodes)) {
    if(is.null(model.ptr[[node]]))
      stop(dQuote(node), " does not have a model")

    model.nodes <- names(.Call(RHugin_model_get_nodes, model.ptr))
    expressions <- .Call(RHugin_model_get_expression, model.ptr)
  }

  else {
    model.nodes <- as.character(model.nodes)
    expressions <- character(1)
  }

  if(length(model.nodes)) {
    states <- lapply(model.nodes, function(u) get.states(domain, u))
    names(states) <- model.nodes

    model <- cbind(expand.grid(rev(states)), Expression = expressions,
                   stringsAsFactors = FALSE)
  }

  else
    model <- data.frame(Expression = expressions, stringsAsFactors = FALSE)

  oldClass(model) <- c("RHugin.model", "data.frame")
  attr(model, "header") <- paste("Model for node ", node, ":\n", sep = "")

  model
}


