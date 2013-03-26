generate.table <- function(domain, nodes)
{
  if(missing(nodes)) {
    RHugin.check.domain(domain, "generate.table")
    .Call(RHugin_domain_generate_tables, domain)
    return(invisible())
  }

  RHugin.check.args(domain, nodes, character(0), "generate.table")

  node.ptrs <- .Call(RHugin_domain_get_node_by_name, domain, nodes)
  model.ptrs <- .Call(RHugin_node_get_model, node.ptrs)

  for(node in nodes) {
    if(is.null(model.ptrs[[node]]))
      warning(dQuote(node), " does not have a model")
    else
      .Call(RHugin_node_generate_table, node.ptrs[node])
  }

  invisible()
}


