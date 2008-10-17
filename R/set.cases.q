set.cases <- function(domain, data, Freq)
{
  RHugin.check.args(domain, character(0), character(0), "set.cases")

  n <- nrow(data)
  data.names <- names(data)
  nodes <- intersect(get.nodes(domain), data.names)
  node.summary <- summary(domain, nodes = nodes)

  status <- .Call("RHugin_domain_set_number_of_cases", domain,
                   as.integer(0), PACKAGE = "RHugin")
  RHugin.handle.error(status)
  status <- .Call("RHugin_domain_set_number_of_cases", domain,
                   as.integer(n), PACKAGE = "RHugin")
  RHugin.handle.error(status)

  for(node in nodes) {
    node.ptr <- .Call("RHugin_domain_get_node_by_name", domain, node,
                       PACKAGE = "RHugin")
    RHugin.handle.error()

    status <- switch(node.summary[[node]]$kind,
      "discrete" = {
        states <- get.states(domain, node)
        state.indices <- match(data[[node]], states, nomatch = NA)
        index.set <- which(!is.na(state.indices))
        state.indices <- state.indices[index.set]

        .Call("RHugin_node_set_case_state", node.ptr,
               as.integer(index.set - 1), as.integer(state.indices - 1),
               PACKAGE = "RHugin")
      },

      "continuous" = .Call("RHugin_node_set_case_value", node.ptr,
                            as.integer(index.set), as.numeric(data[[node]]),
                            PACKAGE = "RHugin")
    )

    RHugin.handle.error(status)
  }

  if(!missing(Freq)) {
    if(is.character(Freq) && !is.null(data[[Freq]]))
      Freq <- data[[Freq]]

    if(length(Freq) != n) {
      .Call("RHugin_domain_set_number_of_cases", domain, as.integer(0),
             PACKAGE = "RHugin")
      stop(sQuote("Freq"), " is not the correct length")
    }

    status <- .Call("RHugin_domain_set_case_count", domain,
                     as.integer(0:(n - 1)), as.numeric(Freq),
                     PACKAGE = "RHugin")
    RHugin.handle.error(status)
  }

  invisible(NULL)
}


