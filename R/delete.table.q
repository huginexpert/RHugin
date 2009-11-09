delete.table <- function(domain, node, type = c("experience", "fading"))
{
  RHugin.check.args(domain, node, character(0), "delete.table")
  type <- match.arg(type)

  node.ptr <- .Call("RHugin_domain_get_node_by_name", domain, node,
                     PACKAGE = "RHugin")
  RHugin.handle.error()

  status <- switch(type,
    experience = {
      has.expr.table <- .Call("RHugin_node_has_experience_table", node.ptr,
                               PACKAGE = "RHugin")
      RHugin.handle.error()

      if(has.expr.table) {
        table.ptr <- .Call("RHugin_node_get_experience_table", node.ptr,
                            PACKAGE = "RHugin")
        RHugin.handle.error()
        status <- .Call("RHugin_table_delete", table.ptr, PACKAGE = "RHugin")
        RHugin.handle.error(status)
      }
      else {
        warning(dQuote(node), " does not have an experience table",
                call. = FALSE)
        status <- -1
      }
      status
    },
    fading = {
      has.fading.table <- .Call("RHugin_node_has_fading_table", node.ptr,
                                 PACKAGE = "RHugin")
      RHugin.handle.error()

      if(has.fading.table) {
        table.ptr <- .Call("RHugin_node_get_fading_table", node.ptr,
                            PACKAGE = "RHugin")
        RHugin.handle.error()
        status <- .Call("RHugin_table_delete", table.ptr, PACKAGE = "RHugin")
        RHugin.handle.error(status)
      }
      else {
        warning(dQuote(node), " does not have a fading table", call. = FALSE)
        status <- -1
      }
      status
    }
  )

  invisible(NULL)
}


