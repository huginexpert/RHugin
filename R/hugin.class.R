hugin.class <- function(cc, name = NULL) {
  if (!is.null(name[1])) {
    class_names <- names(class.collection.get.members(cc))
    if (any(name == class_names)) {
      stop("Class ", dQuote(name[1]), " is already in class collection")
    }
  }

  class <- .Call(RHugin_cc_new_class, cc)
  oldClass(class) <- "RHuginClass"

  if (!is.null(name[1])) {
    .Call(RHugin_class_set_name, class, name)
  }

  class
}
