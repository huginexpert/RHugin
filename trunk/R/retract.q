retract <- function(domain, nodes)
{
  if(missing(nodes))
    .Call(RHugin_domain_retract_findings, domain)

  else {
    node.ptrs <- nodePointersFromNames(domain, nodes)
    .Call(RHugin_node_retract_findings, node.ptrs)
  }

  invisible()
}


