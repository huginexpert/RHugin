get.dseparated.nodes <- function(domain, source, hard, soft)
{
  if(missing(hard)) hard <- character(0)
  if(missing(soft)) soft <- character(0)

  RHugin.check.args(domain, c(source, hard, soft), character(0),
                   "get.dseparated.nodes")

  source.ptrs <- .Call("RHugin_domain_get_node_by_name", domain,
                        as.character(source), PACKAGE = "RHugin")
  hard.ptrs <- .Call("RHugin_domain_get_node_by_name", domain,
                      as.character(hard), PACKAGE = "RHugin")
  soft.ptrs <- .Call("RHugin_domain_get_node_by_name", domain,
                      as.character(soft), PACKAGE = "RHugin")

  names(.Call("RHugin_domain_get_d_separated_nodes", domain, source.ptrs,
               hard.ptrs, soft.ptrs, PACKAGE = "RHugin"))
}


