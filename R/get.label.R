get.label <- function(domainOrClass, node) {
    node.ptrs <- nodePointersFromNames(domainOrClass, node)
    .Call(RHugin_node_get_label, node.ptrs[node])
}