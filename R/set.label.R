set.label <- function(node, label) {
    .Call(RHugin_node_set_label, node, label)
    invisible()
}