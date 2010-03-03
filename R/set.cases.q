set.cases <- function(domain, data, Freq)
{
  RHugin.check.args(domain, character(0), character(0), "set.cases")

  n <- nrow(data)
  data.names <- names(data)
  nodes <- intersect(get.nodes(domain), data.names)

  node.ptrs <- .Call("RHugin_domain_get_node_by_name", domain, nodes,
                      PACKAGE = "RHugin")
  kinds <- .Call("RHugin_node_get_kind", node.ptrs, PACKAGE = "RHugin")
  subtypes <- .Call("RHugin_node_get_subtype", node.ptrs, PACKAGE = "RHugin")

  .Call("RHugin_domain_set_number_of_cases", domain, 0, PACKAGE = "RHugin")
  .Call("RHugin_domain_set_number_of_cases", domain, n, PACKAGE = "RHugin")

  for(node in nodes) {
    switch(kinds[node],
      "discrete" = {
        if(is.element(subtypes[node], c("labeled", "boolean"))) {
          states <- get.states(domain, node)
          state.indices <- match(data[[node]], states, nomatch = NA) - 1
        }
        else {
          state.indices <- .Call("RHugin_node_get_state_index_from_value",
                                  node.ptrs[node], data[[node]],
                                  PACKAGE = "RHugin")
          state.indices[state.indices == -1] <- NA
        }

        index.set <- which(!is.na(state.indices))
        state.indices <- state.indices[index.set]

        .Call("RHugin_node_set_case_state", node.ptrs[node], index.set - 1,
               state.indices, PACKAGE = "RHugin")
      },

      "continuous" = {
        index.set <- which(is.finite(data[[node]]))
        .Call("RHugin_node_set_case_value", node.ptrs[node], index.set - 1,
               data[[node]][index.set], PACKAGE = "RHugin")
      }
    )
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
                     as.integer(0:(n - 1)), as.double(Freq),
                     PACKAGE = "RHugin")
    RHugin.handle.error(status)
  }

  invisible(NULL)
}


