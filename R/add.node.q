add.node <- function(domain, name,
                     category = c("chance", "decision", "utility"),
                     kind = c("discrete", "continuous"),
                     subtype, states)
{
  RHugin.check.args(domain, character(0), name, "add.node")

  status <- numeric(3)
  category <- match.arg(category)
  kind <- match.arg(kind)

  if(is.element(name, c("Freq", "Value", "Cost", "Utility")))
    stop("invalid name: ", dQuote(name), " is an RHugin reserved word")

  if(!missing(subtype))
    subtype <- match.arg(subtype,
                         c("labeled", "boolean", "numbered", "interval"))
  else
    subtype <- NULL

  new.node <- .Call("RHugin_domain_new_node", domain, as.character(category),
                     as.character(kind), PACKAGE = "RHugin")
  status[1] <- error.code()
  status[2] <- .Call("RHugin_node_set_name", new.node, name, PACKAGE = "RHugin")

  if((category == "chance" && kind == "discrete") || category == "decision") {
    if(!is.null(subtype) && !missing(states))
      set.states(domain, node = name, states = states, subtype = subtype)
    else if(!is.null(subtype))
      set.states(domain, node = name, subtype = subtype)
    else if(!missing(states))
      set.states(domain, node = name, states = states)
  }

  invisible(status)
}


