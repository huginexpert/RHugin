clone.node <- function(domain, node, name)
{
  if(name[1] %in% RHUGIN.RESERVED)
    stop("invalid name: ", dQuote(name[1]), " is a reserved word in RHugin")

  name.ptr <- .Call(RHugin_domain_get_node_by_name, domain, name[1])
  if(!is.null(name.ptr[[1]]))
    stop("Node ", dQuote(name), " already exists")

  node.ptr <- nodePointersFromNames(domain, node[1])
  clone.ptr <- .Call(RHugin_node_clone, node.ptr)
  .Call(RHugin_node_set_name, clone.ptr, name[1])

  invisible()
}
