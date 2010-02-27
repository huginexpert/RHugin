add.node <- function(domain, name,
                     category = c("chance", "decision", "utility"),
                     kind = c("discrete", "continuous"),
                     subtype, states)
{
  RHugin.check.args(domain, character(0), name, "add.node")

  category <- match.arg(category)
  kind <- match.arg(kind)

  if(is.element(name, c("Freq","Value","Cost","Utility","Counts","Lambda")))
    stop("invalid name: ", dQuote(name), " is an RHugin reserved word")

  if(!missing(subtype))
    subtype <- match.arg(subtype,
                         c("labeled", "boolean", "numbered", "interval"))
  else
    subtype <- NULL

  node.ptr <- .Call("RHugin_domain_new_node", domain, category, kind,
                     PACKAGE = "RHugin")

  status <- .Call("RHugin_node_set_name", node.ptr, name, PACKAGE = "RHugin")

  if(status != 0) {
    .Call("RHugin_node_delete", node.ptr, PACKAGE = "RHugin")
    stop(error.description(status)$description)
  }

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


