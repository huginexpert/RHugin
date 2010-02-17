triangulate.RHuginDomain <- function(object, method = "fill.in.weight", order,
                                     max.separators = 1e5L, ...)
{
  RHugin.check.args(object, character(0), character(0), "triangulate")
  method <- match.arg(method, choices = c("clique.size", "clique.weight",
                                          "fill.in.size", "fill.in.weight",
                                          "total.weight"))

  if(.Call("RHugin_domain_is_triangulated", object, PACKAGE = "RHugin"))
    stop(deparse(substitute(object)), " is aleady triangulated")

  if(!missing(order)) {
    node.ptrs <- .Call("RHugin_domain_get_node_by_name", object,
                        as.character(order), PACKAGE = "RHugin")
    status <- .Call("RHugin_domain_triangulate_with_order", object, node.ptrs,
                     PACKAGE = "RHugin")
  }

  else {
    if(method == "total.weight") {
      status <- .Call("RHugin_domain_set_max_number_of_separators", object,
                       as.integer(max.separators), PACKAGE = "RHugin")
      RHugin.handle.error(status)
    }

    status <- .Call("RHugin_domain_triangulate", object, as.character(method),
                     PACKAGE = "RHugin")
  }

  RHugin.handle.error(status)

  names(.Call("RHugin_domain_get_elimination_order", object,
               PACKAGE = "RHugin"))
}


