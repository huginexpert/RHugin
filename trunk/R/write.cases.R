write.cases <- function(domain, filename, nodes)
{
  if(missing(nodes))
    nodes <- get.nodes(domain)

  filename <- path.expand(filename)

  node.ptrs <- nodePointersFromNames(domain, nodes)

  .Call(RHugin_domain_save_cases, domain, filename, node.ptrs, NULL, TRUE,
        ",\t", "*")

  invisible()
}


