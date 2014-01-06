delete.model <- function(domain, nodes)
{
  node.ptrs <- nodePointersFromNames(domain, nodes)
  model.ptrs <- .Call(RHugin_node_get_model, node.ptrs)

  for(node in nodes) {
    if(is.null(model.ptrs[[node]]))
      warning(dQuote(node), " does not have a model")
    else
      .Call(RHugin_model_delete, model.ptrs[node])
  }

  invisible()
}


