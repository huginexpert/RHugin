retract <- function(domain, nodes)
{
  if(missing(nodes)) {
    RHugin.check.domain(domain, "retract")

    .Call(RHugin_domain_retract_findings, domain)
  }

  else {
    RHugin.check.args(domain, nodes, character(0), "retract")

    node.ptrs <- .Call(RHugin_domain_get_node_by_name, domain, nodes)
    .Call(RHugin_node_retract_findings, node.ptrs)
  }

  invisible()
}


