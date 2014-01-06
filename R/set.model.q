set.model <- function(domain, node, model)
{
  node <- node[1]
  expressions <- as.character(model$Expression)
  model.nodes <- names(model)[-length(model)]

  if(length(model.nodes)) {
    if(!all(model.nodes %in% get.parents(domain, node)))
      stop("invalid model node")

    states <- lapply(model.nodes, function(u) get.states(domain, u))
    names(states) <- model.nodes
    size <- prod(sapply(states, length))

    if(size != length(expressions))
      stop(sQuote("model"), " is not the correct size")

    indices <- as.list(model[model.nodes])
    for(i in names(states))
      indices[[i]] <- factor(indices[[i]], levels = states[[i]])

    expressions <- tapply(expressions, indices, I)
  }
  
  else {
    if(length(expressions) != 1)
      stop(sQuote("model"), " is not the correct size")
  }

  node.ptr <- nodePointersFromNames(domain, node)
  model.node.ptrs <- nodePointersFromNames(domain, rev(model.nodes))

  model.ptr <- .Call(RHugin_node_new_model, node.ptr, model.node.ptrs)
  .Call(RHugin_model_set_expression, model.ptr, expressions)

  invisible()
}


