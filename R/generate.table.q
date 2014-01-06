generate.table <- function(domain, nodes)
{
  if(missing(nodes))
    return(invisible(.Call(RHugin_domain_generate_tables, domain)))

  node.ptrs <- nodePointersFromNames(domain, nodes)
  model.ptrs <- .Call(RHugin_node_get_model, node.ptrs)

  for(node in nodes) {
    if(is.null(model.ptrs[[node]]))
      warning(dQuote(node), " does not have a model")
    else
      .Call(RHugin_node_generate_table, node.ptrs[node])
  }

  invisible()
}


