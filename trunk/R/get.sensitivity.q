get.sensitivity <- function(domain, query, qstate)
{
  RHugin.check.args(domain, query, character(0), "get.sensitvity")

  query.states <- get.states(domain, query)
  qstate <- match(qstate, query.states, nomatch = NA)[1]
  if(is.na(qstate))
    stop("invalid qstate")
  else
    qstate <- qstate - 1

  node.ptr <- .Call("RHugin_domain_get_node_by_name", domain, query,
                     PACKAGE = "RHugin")
  RHugin.handle.error()

  status <- .Call("RHugin_node_compute_sensitvity_data", node.ptr,
                   as.integer(state), PACKAGE = "RHugin")
  RHugin.handle.error(status)
}


