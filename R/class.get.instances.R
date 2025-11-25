class.get.instances <- function(class) {
  instance.ptrs <- .Call(RHugin_class_get_instances, class)
  instances <- list()

  for (i in seq_len(length(instance.ptrs))) {
    instance.name <- .Call(RHugin_node_get_name, list(instance.ptrs[[i]]))
    home.class <- .Call(RHugin_node_get_home_class, list(instance.ptrs[[i]]))
    home.name <- get.class.name(home.class)
    combined_name <- paste(home.name, ".", instance.name, sep = "")
    instances[[combined_name]] <- instance.ptrs[[i]]
  }

  instances
}
