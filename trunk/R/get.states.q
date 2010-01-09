get.states <- function(domain, node, values = FALSE)
{
  RHugin.check.args(domain, node, character(0), "get.states")

  node.ptr <- .Call("RHugin_domain_get_node_by_name", domain, node,
                     PACKAGE = "RHugin")

  if(!is.null(node.ptr)) {
    n.states <- .Call("RHugin_node_get_number_of_states", node.ptr,
                       PACKAGE = "RHugin")
    RHugin.handle.error()

    subtype <- .Call("RHugin_node_get_subtype", node.ptr, PACKAGE = "RHugin")
    states <- switch(subtype,
      "labeled" = .Call("RHugin_node_get_state_label", node.ptr,
                         as.integer(0:(n.states - 1)), PACKAGE = "RHugin"),

      "boolean" = c(FALSE, TRUE),

      "numbered" = .Call("RHugin_node_get_state_value", node.ptr,
                          as.integer(0:(n.states - 1)), PACKAGE = "RHugin"),

      "interval" = {
        pts <- .Call("RHugin_node_get_state_value", node.ptr,
                      as.integer(0:(n.states)), PACKAGE = "RHugin")

        if(!values) {
          infinite <- is.infinite(c(pts[1], pts[length(pts)]))
          pts <- format(pts, trim = TRUE, digits = 3, justify = "none")
          pts <- paste(pts[-length(pts)], pts[-1], sep = ",")
          l.pts <- length(pts)
          if(l.pts == 1)
            pts <- paste(ifelse(infinite[1], "(", "["), pts,
                         ifelse(infinite[2], ")", "]"), sep = "")
          else {
            pts[1] <- paste(ifelse(infinite[1], "(", "["), pts[1], ")",
                            sep = "")
            pts[l.pts] <- paste("[", pts[l.pts], ifelse(infinite[2], ")", "]"),
                                sep = "")
            if(l.pts > 2)
              pts[2:(l.pts - 1)] <- paste("[", pts[2:(l.pts - 1)], ")",
                                          sep = "")
          }
        }

        pts
      }
    )
    RHugin.handle.error()
  }

  else
    states <- NULL

  states
}


