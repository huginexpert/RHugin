add.node <- function(domain, name,
                     category = c("chance", "decision", "utility", "function"),
                     kind = c("discrete", "continuous", "other"),
                     subtype, states)
{
  if(name[1] %in% RHUGIN.RESERVED)
    stop("invalid name: ", dQuote(name[1]), " is a reserved word in RHugin")

  name.ptr <- .Call(RHugin_domain_get_node_by_name, domain, name[1])
  if(!is.null(name.ptr[[1]]))
    stop("Node ", dQuote(name[1]), " already exists")

  category <- match.arg(category)
  kind <- match.arg(kind)

  if(!missing(subtype))
    subtype <- match.arg(subtype, RHUGIN.SUBTYPES)
  else
    subtype <- NULL

  node.ptr <- .Call(RHugin_domain_new_node, domain, category, kind)
  .Call(RHugin_node_set_name, node.ptr, name[1])

  if((category == "chance" && kind == "discrete") || category == "decision") {
    if(!is.null(subtype) && !missing(states))
      set.states(domain, node = name, states = states, subtype = subtype)
    else if(!is.null(subtype))
      set.states(domain, node = name, subtype = subtype)
    else if(!missing(states))
      set.states(domain, node = name, states = states)
  }

  invisible()
}


