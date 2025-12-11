set.class.size <- function(class, width, height) {
    .Call(RHugin_class_set_node_size, class, c(width, height))
    invisible()
}