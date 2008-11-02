summary.RHuginDomain <- function(object, nodes = FALSE, ...)
{
  if(is.logical(nodes)) {
    if(nodes)
      nodes <- get.nodes(object)
    else
      nodes <- character(0)
  }

  else
    RHugin.check.args(object, nodes, character(0), "summary.RHuginDomain")


  compiled <- .Call("RHugin_domain_is_compiled", object, PACKAGE = "RHugin")

  equilibrium <- ifelse(.Call("RHugin_domain_equilibrium_is", object,
                              "max", PACKAGE = "RHugin"),
                        "max", "sum")

  evidence.mode <- ifelse(.Call("RHugin_domain_evidence_mode_is", object,
                                "fast", PACKAGE = "RHugin"),
                          "fast", "normal")

  evidence.propagated <- .Call("RHugin_domain_evidence_is_propagated", object,
                                PACKAGE = "RHugin")

  L.evidence.propagated <- .Call("RHugin_domain_likelihood_is_propagated",
                                  object, PACKAGE = "RHugin")

  GC.evidence.propagated <- .Call("RHugin_domain_cg_evidence_is_propagated",
                                   object, PACKAGE = "RHugin")

  evidence.to.propagate <- .Call("RHugin_domain_evidence_to_propagate",
                                  object, PACKAGE = "RHugin")

  tables.to.propagate <- .Call("RHugin_domain_tables_to_propagate", object,
                                PACKAGE = "RHugin")

  domain.summary <- list(compiled = compiled,
                         equilibrium = equilibrium,
                         evidence.mode = evidence.mode,
                         evidence.propagated = evidence.propagated,
                         L.evidence.propagated = L.evidence.propagated,
                         GC.evidence.propagated = GC.evidence.propagated,
                         evidence.to.propagate = evidence.to.propagate,
                         tables.to.propagate = tables.to.propagate)


  node.summary <- list()

  for(node in nodes) {
    node.ptr <- .Call("RHugin_domain_get_node_by_name", object, node,
                       PACKAGE = "RHugin")
    RHugin.handle.error()
    node.category <- .Call("RHugin_node_get_category", node.ptr,
                            PACKAGE = "RHugin")
    RHugin.handle.error()
    node.kind <- .Call("RHugin_node_get_kind", node.ptr, PACKAGE = "RHugin")
    RHugin.handle.error()

    if(node.kind == "discrete") {
      node.subtype <- .Call("RHugin_node_get_subtype", node.ptr,
                             PACKAGE = "RHugin")
      RHugin.handle.error()
      states <- get.states(object, node)
    }

    else {
      node.subtype <- NULL
      states <- NULL
    }

    node.summary[[node]] <- list(category = node.category, kind = node.kind,
                                 subtype = node.subtype, states = states)
  }

  ans <- list(node.names = get.nodes(object), edge.list = get.edges(object),
              domain = domain.summary, nodes = node.summary)
  oldClass(ans) <- "summary.RHuginDomain"
  ans
}


