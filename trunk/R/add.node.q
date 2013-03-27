add.node <- function(domain, name,
                     category = c("chance", "decision", "utility", "function"),
                     kind = c("discrete", "continuous", "other"),
                     subtype, states)
{
  RHugin.check.args(domain, character(0), name, "add.node")

  category <- match.arg(category)
  kind <- match.arg(kind)

  if(is.element(name, RHUGIN.RESERVED))
    stop("invalid name: ", dQuote(name), " is a reserved word in RHugin")

  if(!missing(subtype))
    subtype <- match.arg(subtype, RHUGIN.SUBTYPES)
  else
    subtype <- NULL

  node.ptr <- .Call(RHugin_domain_new_node, domain, category, kind)
  .Call(RHugin_node_set_name, node.ptr, name)

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


