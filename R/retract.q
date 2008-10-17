retract <- function(domain, nodes)
{
  if(missing(nodes)) {
    RHugin.check.args(domain, character(0), character(0), "retract")
    status <- .Call("RHugin_domain_retract_findings", domain,
                     PACKAGE = "RHugin")
    RHugin.handle.error(status)
  }

  else {
    RHugin.check.args(domain, nodes, character(0), "retract")

    for(node in nodes) {
      node.ptr <- .Call("RHugin_domain_get_node_by_name", domain, node,
                         PACKAGE = "RHugin")
      RHugin.handle.error()
      status <- .Call("RHugin_node_retract_findings", node.ptr,
                       PACKAGE = "RHugin")
      RHugin.handle.error(status)
    }
  }

  invisible(NULL)
}

