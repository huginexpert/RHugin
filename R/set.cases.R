set.cases <- function(domain, data, Freq)
{
  n <- nrow(data)
  data.names <- names(data)
  nodes <- intersect(get.nodes(domain), data.names)

  node.ptrs <- nodePointersFromNames(domain, nodes)
  kinds <- .Call(RHugin_node_get_kind, node.ptrs)
  subtypes <- .Call(RHugin_node_get_subtype, node.ptrs)

  .Call(RHugin_domain_set_number_of_cases, domain, 0)
  .Call(RHugin_domain_set_number_of_cases, domain, n)

  for(node in nodes) {
    switch(kinds[node],
      "discrete" = {
        if(is.element(subtypes[node], c("labeled", "boolean"))) {
          states <- get.states(domain, node)
          state.indices <- match(data[[node]], states, nomatch = NA) - 1
        }
        else {
          state.indices <- .Call(RHugin_node_get_state_index_from_value,
                                 node.ptrs[node], data[[node]])
          state.indices[state.indices == -1] <- NA
        }

        index.set <- which(!is.na(state.indices))
        state.indices <- state.indices[index.set]

        .Call(RHugin_node_set_case_state, node.ptrs[node], index.set - 1,
              state.indices)
      },

      "continuous" = {
        index.set <- which(is.finite(data[[node]]))
        .Call(RHugin_node_set_case_value, node.ptrs[node], index.set - 1,
              data[[node]][index.set])
      }
    )
  }

  if(!missing(Freq)) {
    if(is.character(Freq) && !is.null(data[[Freq]]))
      Freq <- data[[Freq]]

    if(length(Freq) != n) {
      .Call(RHugin_domain_set_number_of_cases, domain, as.integer(0))
      stop(sQuote("Freq"), " is not the correct length")
    }

    .Call(RHugin_domain_set_case_count, domain, 0:(n - 1), Freq)
  }

  invisible()
}


