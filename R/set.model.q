set.model <- function(domain, node, model)
{
  node <- node[1]
  node.ptr <- .Call(RHugin_domain_get_node_by_name, domain, node)
  model.ptr <- .Call(RHugin_node_get_model, node.ptr)

  expressions <- model$Expression
  model.nodes <- rev(names(.Call(RHugin_model_get_nodes, model.ptr)))
  states <- lapply(model.nodes, function(u) get.states(domain, u))
  names(states) <- model.nodes

  size <- ifelse(length(states), prod(sapply(states, length)), 1)

  if(size != length(expressions))
    stop(sQuote("model"), " is not the correct size")

  if(size > 1) {
    indices <- as.list(model[model.nodes])
    for(i in names(states))
      indices[[i]] <- factor(indices[[i]], levels = states[[i]])

    expressions <- as.vector(tapply(expressions, indices, I), mode = "character")
  }

  .Call(RHugin_model_set_expression, model.ptr, expressions)

  invisible()
}


