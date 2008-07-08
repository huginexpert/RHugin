retract <- function(domain, node)
{
  if(missing(node)) {
    RHugin.check.args(domain, character(0), character(0), "retract")
    status <- .Call("RHugin_domain_retract_findings", domain$pointer,
                     PACKAGE = "RHugin")
    RHugin.handle.error(status)
  }

  else {
    RHugin.check.args(domain, node, character(0), "retract")
    node.ptr <- .Call("RHugin_domain_get_node_by_name", domain$pointer, node,
                       PACKAGE = "RHugin")
    RHugin.handle.error()
    status <- .Call("RHugin_node_retract_findings", node.ptr,
                     PACKAGE = "RHugin")
    RHugin.handle.error(status)
  }

  invisible(NULL)
}

