generate.table <- function(domain, nodes)
{
  node <- nodes[1]
  node.ptr <- .Call(RHugin_domain_get_node_by_name, domain, node)
  model.ptr <- .Call(RHugin_node_get_model, node.ptr)

  if(is.null(model.ptr[[node]]))
    warning(dQuote(node), " does not have a model")
  else
    .Call(RHugin_node_generate_table, node.ptr)

  invisible()
}


