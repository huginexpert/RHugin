retract <- function(domain, nodes)
{
  if(missing(nodes)) {
    RHugin.check.args(domain, character(0), character(0), "retract")

    .Call("RHugin_domain_retract_findings", domain, PACKAGE = "RHugin")
  }

  else {
    RHugin.check.args(domain, nodes, character(0), "retract")

    node.ptrs <- .Call("RHugin_domain_get_node_by_name", domain, nodes,
                        PACKAGE = "RHugin")
    .Call("RHugin_node_retract_findings", node.ptrs, PACKAGE = "RHugin")
  }

  invisible()
}


