add.node <- function(domain, name,
                     category = c("chance", "decision", "utility"),
                     kind = c("discrete", "continuous"),
                     subtype, states)
{
  RHugin.check.args(domain, character(0), name, "add.node")

  category <- match.arg(category)
  kind <- match.arg(kind)

  if(is.element(name, c("Freq", "Value", "Cost", "Utility")))
    stop("invalid name: ", dQuote(name), " is a reserved word in RHugin")

  if(!missing(subtype))
    subtype <- match.arg(subtype,
                         c("labeled", "boolean", "numbered", "interval"))
  else
    subtype <- NULL

  new.node <- .Call("RHugin_domain_new_node", domain, as.character(category),
                     as.character(kind), PACKAGE = "RHugin")
  RHugin.handle.error()
  status <- .Call("RHugin_node_set_name", new.node, name, PACKAGE = "RHugin")
  RHugin.handle.error(status)

  if((category == "chance" && kind == "discrete") || category == "decision") {
    if(!is.null(subtype) && !missing(states))
      status <- set.states(domain, node = name, states = states,
                           subtype = subtype)
    else if(!is.null(subtype))
      status <- set.states(domain, node = name, subtype = subtype)
    else if(!missing(states))
      status <- set.states(domain, node = name, states = states)
    
    RHugin.handle.error(status)
  }

  invisible(NULL)
}


