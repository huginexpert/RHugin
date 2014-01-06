get.dconnected.nodes <- function(domain, source, hard, soft)
{
  if(missing(hard)) hard <- character(0)
  if(missing(soft)) soft <- character(0)

  source.ptrs <- nodePointersFromNames(domain, source)
  hard.ptrs <- nodePointersFromNames(domain, hard)
  soft.ptrs <- nodePointersFromNames(domain, soft)

  dc.ptrs <- .Call(RHugin_domain_get_d_connected_nodes, domain, source.ptrs,
                   hard.ptrs, soft.ptrs)

  names(dc.ptrs)
}


