substitute.instance <- function(node, new_class) {
    .Call(RHugin_node_substitute_class, node, new_class)
    invisible()
}