delete.model <- function(domain, nodes)
{
  RHugin.check.args(domain, nodes, character(0), "delete.model")
  node.ptrs <- .Call(RHugin_domain_get_node_by_name, domain, nodes)
  model.ptrs <- .Call(RHugin_node_get_model, node.ptrs)

  for(node in nodes) {
    if(is.null(model.ptrs[[node]]))
      warning(dQuote(node), " does not have a model")
    else
      .Call(RHugin_model_delete, model.ptrs[node])
  }

  invisible()
}


