add.node <- function(domain, name,
                     category = c("chance", "decision", "utility"),
                     kind = c("discrete", "continuous"),
                     subtype, states)
{
  RHugin.check.args(domain, character(0), name, "add.node")

  category <- match.arg(category)
  kind <- match.arg(kind)

  reserved <- c("Freq", "Prob", "Value", "Cost", "Utility", "Counts", "Lambda")
  if(is.element(name, reserved))
    stop("invalid name: ", dQuote(name), " is a reserved word in RHugin")

  if(!missing(subtype))
    subtype <- match.arg(subtype,
                         c("labeled", "boolean", "numbered", "interval"))
  else
    subtype <- NULL

  node.ptr <- .Call("RHugin_domain_new_node", domain, category, kind,
                     PACKAGE = "RHugin")

  .Call("RHugin_node_set_name", node.ptr, name, PACKAGE = "RHugin")

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


