set.label <- function(domainOrClass, node, label) {
    node.ptrs <- nodePointersFromNames(domainOrClass, node)
    .Call(RHugin_node_set_label, node.ptrs[node], label)
    invisible()
}