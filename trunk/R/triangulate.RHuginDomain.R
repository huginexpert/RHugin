triangulate <- function(object, ...)
  UseMethod("triangulate")


TRIANGULATION.METHODS <- c("clique.size", "clique.weight", "fill.in.size",
                           "fill.in.weight", "best.greedy", "total.weight")


triangulate.RHuginDomain <- function(object, method = "best.greedy", order,
                                     start, max.separators = 0,
                                     max.separator.size = 0, ...)
{
  method <- match.arg(method, choices = TRIANGULATION.METHODS)

  if(.Call(RHugin_domain_is_triangulated, object))
    stop(deparse(substitute(object)), " is aleady triangulated")

  if(!missing(order)) {
    node.ptrs <- nodePointersFromNames(object, order)
    .Call(RHugin_domain_triangulate_with_order, object, node.ptrs)
  }

  else {
    if(method == "total.weight") {
      .Call(RHugin_domain_set_max_number_of_separators, object, max.separators)

      if(!missing(start)) {
        node.ptrs <- nodePointersFromNames(object, start)
        .Call(RHugin_domain_set_initial_triangulation, object, node.ptrs)
        .Call(RHugin_domain_set_max_separator_size, object, max.separator.size)
      }
    }

    .Call(RHugin_domain_triangulate, object, method)
  }

  order <- .Call(RHugin_domain_get_elimination_order, object)
  names(order)
}


