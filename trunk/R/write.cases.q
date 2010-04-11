write.cases <- function(domain, filename, nodes)
{
  if(missing(nodes))
    nodes <- get.nodes(domain)

  RHugin.check.args(domain, nodes, character(0), "write.cases")
  filename <- path.expand(filename)

  node.ptrs <- .Call("RHugin_domain_get_node_by_name", domain, nodes,
                      PACKAGE = "RHugin")

  .Call("RHugin_domain_save_cases", domain, as.character(filename), node.ptrs,
         NULL, TRUE, ",\t", "*", PACKAGE = "RHugin")

  invisible()
}


