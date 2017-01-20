get.states <- function(domain, node, values = FALSE)
{
  node.ptr <- nodePointersFromNames(domain, node[1])
  n.states <- .Call(RHugin_node_get_number_of_states, node.ptr)
  subtype <- .Call(RHugin_node_get_subtype, node.ptr)

  switch(subtype,
    "labeled" = .Call(RHugin_node_get_state_label, node.ptr, 0:(n.states - 1)),

    "boolean" = c(FALSE, TRUE),

    "numbered" = .Call(RHugin_node_get_state_value, node.ptr, 0:(n.states - 1)),

    "interval" = {
      pts <- .Call(RHugin_node_get_state_value, node.ptr, 0:(n.states))

      if(!values) {
        infinite <- is.infinite(c(pts[1], pts[length(pts)]))
        pts <- format(pts, trim = TRUE, digits = 3, justify = "none")
        pts <- paste(pts[-length(pts)], pts[-1], sep = ",")
        l.pts <- length(pts)
        if(l.pts == 1)
          pts <- paste(ifelse(infinite[1], "(", "["), pts,
                       ifelse(infinite[2], ")", "]"), sep = "")
        else {
          pts[1] <- paste(ifelse(infinite[1], "(", "["), pts[1], ")", sep = "")
          pts[l.pts] <- paste("[", pts[l.pts], ifelse(infinite[2], ")", "]"),
                              sep = "")
          if(l.pts > 2)
            pts[2:(l.pts - 1)] <- paste("[", pts[2:(l.pts - 1)], ")", sep = "")
        }
      }

      pts
    }
  )
}


