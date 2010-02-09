write.cases <- function(domain, filename, nodes)
{
  if(missing(nodes))
    nodes <- get.nodes(domain)

  RHugin.check.args(domain, nodes, character(0), "write.cases")

  node.ptrs <- .Call("RHugin_domain_get_node_by_name", domain,
                      as.character(nodes), PACKAGE = "RHugin")

  status <- .Call("RHugin_domain_save_cases", domain, as.character(filename),
                   node.ptrs, NULL, TRUE, ",\t", "*", PACKAGE = "RHugin")

  RHugin.handle.error(status)
  invisible(NULL)
}


