add.node <- function(domain, name,
                     category = c("chance", "decision", "utility"),
                     kind = c("discrete", "continuous"),
                     states)
{
  RHugin.check.args(domain, character(0), name, "add.node")

  category <- match.arg(category)
  kind <- match.arg(kind)
  #subtype <- match.arg(subtype)

  new.node <- .Call("RHugin_domain_new_node", domain, as.character(category),
                     as.character(kind), PACKAGE = "RHugin")
  RHugin.handle.error()
  status <- .Call("RHugin_node_set_name", new.node, name, PACKAGE = "RHugin")
  RHugin.handle.error(status)

  if(((category == "chance" && kind == "discrete") || category == "decision") &&
      !missing(states)) {
    status <- set.states(domain, name, states)
    RHugin.handle.error(status)
  }

  invisible(NULL)
}


