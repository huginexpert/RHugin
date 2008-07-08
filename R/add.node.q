add.node <- function(domain, name,
                     category = c("chance", "decision", "utility", "instance"),
                     kind = c("discrete", "continuous"),
                     subtype = c("labeled", "boolean", "numbered", "interval"),
                     states)
{
  RHugin.check.args(domain, character(0), name, "add.node")

  category <- match.arg(category)
  kind <- match.arg(kind)
  subtype <- match.arg(subtype)

  new.node <- .Call("RHugin_domain_new_node", domain$pointer, category, kind,
                     PACKAGE = "RHugin")
  RHugin.handle.error()
  status <- .Call("RHugin_node_set_name", new.node, name, PACKAGE = "RHugin")
  RHugin.handle.error(status)

  if(kind == "discrete") {
    status <- .Call("RHugin_node_set_subtype", new.node, as.character(subtype),
                     PACKAGE = "RHugin")
    RHugin.handle.error(status)
  }

  if(kind == "discrete" && !missing(states)) {
    status <- set.states(domain, name, states)
    RHugin.handle.error(status)
  }

  invisible(NULL)
}


